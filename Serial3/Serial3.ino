#include <Servo.h>

boolean debug=true;
byte serialStream[4];
boolean flags[24];

#define HC_SR04_ECHO 4
#define HC_SR04_TRIG 5
#define HC_MaxRange 350
#define HC_MinRange 5

#define SERVO 9
#define INFRAROSSI 11
#define INFRAROSS2 12

#define IR_SENSIBILITA 500

float sensorVal[24];
unsigned int sensorName[24];
unsigned int sensorPin[24];

Servo servo_testa;
int cm;
int mes[360];

void setup() {
  // put your setup code here, to run once:
  sensorPin[INFRAROSSI]=A0;
  sensorName[INFRAROSSI]=INFRAROSSI;

  sensorPin[INFRAROSS2]=A1;
  sensorName[INFRAROSS2]=INFRAROSS2;
  
  
  Serial.begin(57600);

  pinMode(HC_SR04_TRIG, OUTPUT);
  pinMode(HC_SR04_ECHO, INPUT);

  servo_testa.attach(SERVO);
  servo_testa.write(0);

  pinMode(sensorPin[INFRAROSSI], INPUT);
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
    cm = getHC_SR04Measure();
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
}

void loop() {
  // put your main code here, to run repeatedly:
  measure();
  if (sensorVal[INFRAROSSI] > IR_SENSIBILITA || sensorVal[INFRAROSS2] > IR_SENSIBILITA){
    //indietro
    //gira
  } else {
    //avanti
  }
  delay(100);
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
