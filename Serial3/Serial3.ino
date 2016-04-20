#include <Motore.h>
#include <Motori.h>
#include <tools.h>

#include <Servo.h>

boolean debug=true;
byte serialStream[4];
boolean flags[24];

#define HC_SR04_ECHO 4
#define HC_SR04_TRIG 5
#define HC_MaxRange 350
#define HC_MinRange 5

Motore* dx = new Motore(52,53,3,49,48);
Motore* sx = new Motore(50,51,10,46,47);
Motori* m = new Motori(dx, sx);
#define enginePower 100

#define SERVO 7
#define INFRAROSSI 11
#define INFRAROSS2 12

#define IR_SENSIBILITA 550
#define IR_SENSIBILITA2 700

float sensorVal[24];
unsigned int sensorName[24];
unsigned int sensorPin[24];

Servo servo_testa;
int cm;
int mes[360];

void setup() {
  // put your setup code here, to run once:
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  
  sensorPin[INFRAROSSI]=A0;
  sensorName[INFRAROSSI]=INFRAROSSI;

  sensorPin[INFRAROSS2]=A5;
  sensorName[INFRAROSS2]=INFRAROSS2;
  
  
  Serial.begin(57600);

  pinMode(HC_SR04_TRIG, OUTPUT);
  pinMode(HC_SR04_ECHO, INPUT);

  servo_testa.attach(SERVO);
  servo_testa.write(90);

  pinMode(sensorPin[INFRAROSSI], INPUT);

  dx->corr = 10;
  sx->corr = 10;
}

int getHC_SR04Measure() {
  //se chiamata ritorna la distanza in CENTIMETRI, -1 se il valore è fuori dal range in negativo e 999 se il valore è fuori range in positivo
  digitalWrite(HC_SR04_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(HC_SR04_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_SR04_TRIG, LOW);
  
  unsigned long tempo = pulseIn(HC_SR04_ECHO, HIGH, (HC_MaxRange*58.2));
  if (tempo==0) {
    return int(999);    //Il codice è andato in timeout e la distanza è eccessiva
  }
  
  long distanza = ( tempo / 58.2 );
  if ( distanza < HC_MinRange ) {
    return int(-1);    //Troppo corto raggio
  }
  else
  {
    return int(distanza);
  }
}

void head_sweep(){
  for (int i=0; i <= 360; i+=10){              
    servo_testa.write(abs(180-i));
    delay(15);
    //cm = getHC_SR04Measure();
  }
}

void head_sweep_panic(){
  servo_testa.write(0);
  cm = getHC_SR04Measure();
  delay(25);
  servo_testa.write(90);
  cm = getHC_SR04Measure();
  delay(25);
  servo_testa.write(180);
  cm = getHC_SR04Measure();
  delay(25);
  servo_testa.write(90);
  cm = getHC_SR04Measure();
}

void measure(){
  sensorVal[INFRAROSSI] = analogRead(sensorPin[INFRAROSSI]);
  sensorVal[INFRAROSS2] = analogRead(sensorPin[INFRAROSS2]);
  if (debug){
    Serial.print("IR SOPRA: ");
    Serial.print(sensorVal[INFRAROSSI]);
    Serial.print(" IR SOTTO: ");
    Serial.print(sensorVal[INFRAROSS2]);
    Serial.println();
  }
  //head_sweep();
}

void loop() {
  // put your main code here, to run repeatedly:
  measure();
  if (sensorVal[INFRAROSSI] > IR_SENSIBILITA || sensorVal[INFRAROSS2] > IR_SENSIBILITA2 ){
    //head_sweep_panic();
    
    m->indietro(enginePower, -1);
    delay(750);
    m->stop();
    dx->muovi(enginePower);
    sx->muovi(-enginePower);
    delay(1500);
    m->stop();
    //indietro
    //gira
  } else {
    m->avanti(enginePower*2.00, -1);
  }
}

void setCommand(){
  int f_idx=0;
  for (int x=1; x < 4; x++){
    for (int i=8; i >= 0; i--){
      flags[f_idx]=bitRead(serialStream[x], i);
      f_idx++;
    }
  }

  if (debug){
    for (int i=0; i < 25; i++){
      if (flags[i]){Serial.print("Sensore "); Serial.print(i); Serial.print(" richiesto"); Serial.println();}
      else {Serial.print("Sensore "); Serial.print(i); Serial.print(" non richiesto"); Serial.println();}
    }
  }
}

void getCommand(){
  for(int x=0; x < 25; x++){
    if (flags[x]){
      Serial.print(sensorVal[x]);
      if (!(x==24)){
        Serial.print(":"); 
      }
    }
  }
  Serial.println();
}

void serialEvent(){
  // CHAR BYTE BYTE BYTE
  if (Serial.available() > 0) {
    serialStream[0]='\0';
    serialStream[1]='\0';
    serialStream[2]='\0';
    serialStream[3]='\0';
    Serial.readBytes(serialStream, 4);
    if (debug){
      Serial.print(char(serialStream[0]));
      Serial.print(" ");
      Serial.print(serialStream[1]);
      Serial.print(" ");
      Serial.print(serialStream[2]);
      Serial.print(" ");
      Serial.print(serialStream[3]);
      Serial.print(" ");
      Serial.println();
    }

    switch (serialStream[0]){
      case 'S':
        setCommand();
        break;
      case 'G':
        getCommand();
        break;
      case 'D':
        debug = !debug;
        Serial.print("DEBUG is "); Serial.println(debug);
        break;
      default:
        Serial.println("Comando sconosciuto");
        break;
    }
  }
}

unsigned long ultimoTempo;			//Serve per calcolare il DeltaT
double inPID, outPID, targetPID;	//Valore da correggere, valore da applicare, obiettivo
double sommaErr, ultimoErr;			//Errore accumulato, ultimo errore registrato
double kP, kI, kD;					//Intervento proporzionale, integrale, derivativo
int campionamento = 1000; 			//Ogni quanto svolgere il calcolo in millisecondi

void calcolaPid()
{
	//Questa funzione salva in outPID il risultato del controllo PID per il setpoint targetPID di inPID
	unsigned long adesso = millis();			//Seleziona adesso
	int deltaTempo = (adesso - ultimoTempo);	//Fa la differenza tra campionamenti successivi
	if(deltaTempo >= campionamento)		//Controlla se calcolare l'errore o no in base al sampling rate scelto
	{
		//Calcolo variabili di lavoro per il PID
		double errore = targetPID - inPID;		//calcolo errore sul valore istantaneo
		sommaErr += errore;						//calcolo errore accumulato
		double deltaErr = (errore - ultimoErr);	//calcolo errore 
		//Calcolo del PID
		outPID = kP * errore + kI * sommaErr + kD * deltaErr;	//Calcolo PID
		//Salvataggio per il prossimo calcolo
		ultimoErr = errore;
		ultimoTempo = adesso;
	}
}
 
void impostaCostanti(double nuovokP, double nuovokI, double nuovokD)
{
	//Se chiamata permette di cambiare le costanti kP, kI e kD senza reinizializzare il PID
	double campionamentoInSecondi = ((double)campionamento) / 1000;	//Conversione easy
	kP = nuovokP;							//L'intervento proporzionale resta invariato rispetto al tempo
	kI = nuovokI * campionamentoInSecondi;	//L'intervento integrale dipende direttamente dai secondi
	kD = nuovokD / campionamentoInSecondi;	//L'intervento derivativo dipende inversamente dai secondi
}
 
void nuovoSampling(int nuovoSamplingRate)
{
	//Assegna un nuovo sampling rate al PID senza reinizializzarlo
	if (nuovoSamplingRate > 0)
	{
		double rapporto  = (double)nuovoSamplingRate / (double)campionamento;
		
		kI *= rapporto;
		kD /= rapporto;
		campionamento = (unsigned long)nuovoSamplingRate;
	}
}
