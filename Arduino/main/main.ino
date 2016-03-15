/*
	File primario
*/

//HEADERS
#include "_cfg.h"
#include "hc-sr04.h"
#include "SHARP_2Y0A21F2Y.h"
#include "TDC310.h"
#include "fotoRes.h"
//FINE HEADERS

//GLOBALI
char serialStream[3];
/*
	A = Automatica
	D = Drone
	I = Idle
*/
char robotMode = 'A';
bool continueFollowing = false;   //Indica al ciclo all'interno di follow se proseguire o no

void setup()
{
  Serial.begin(SerialRate);
  Serial.println("SERIAL: " + String(SerialRate)); 
  prepareHC_SR04();					//prepara sensore HC-SR04
}

void loop()
{
	//LOGICA
	switch (robotMode) {
		case 'A':
			//Modalità autonoma
      goAuto();
			break;
		case 'D':
			//Modalità drone
      goDrone();
			break;
		case 'I':
			//Modalità idle
      getIdle();
			break;
	}
	delay(100);
}

void goAuto(){
  //Serial.println(getHC_SR04Measure_smooth());         // TEST HC-SR04
  //Serial.println(getSHARP2Y0A21F2Ymeasure_smooth());    // TEST SHARP
  //Serial.println(getTDC310temp());                    // TEST TDC310
  //Serial.println(getLight());                         // TEST FOTORESISTENZA
}

void goDrone(){
  
}

void getIdle(){
  continueFollowing = false;                //Blocca l'eventuale inseguimento
  stopEngines();
}

/*
 * Le funzioni di azionamento cingoli prendono come parametri di input una velocita' target oppure una distanza da percorrere target,
 * viene passata come array la velocita' obiettivo
 */
void advance(float requiredSpeed[2], char type = 'S'){
  Serial.println("DEBUGM: Richiesta configurazione motori " + String(requiredSpeed[0]) + " " + String(requiredSpeed[1]));
  if (type == 'S')  { Serial.println("DEBUGM: Modo a velocita' fissata"); } else
                    { Serial.println("DEBUGM: Modo a distanza fissata"); }
}  //Azionamento cingoli
void stopEngines(){
  Serial.println("DEBUGM: Fermati i motori");
}  //Stop motori

void follow(char what){
  while (continueFollowing){
    if (what == 'S') {
      Serial.println("DEBUGM: Seguendo suoni");
    } else {
      Serial.println("DEBUGM: Seguendo immagini");
    }
    if (Serial.available() > 0) {
      if (Serial.readString() == "FN"){
        continueFollowing = false;
        Serial.println("DEBUGM: Interrotto inseguimento");
      } else {
        Serial.println("DEBUGM: Comando non accettato");
        Serial.println("DEBUGM: Provare con FN per interrompere l'inseguimento");
      }
    }
    delay(1000);
  }
}

void moveForX(char movDirection, char movDuration) {
  int remainingMov;
  if (movDuration == '\0') { movDuration = '1'; }
  remainingMov = movDuration-48;  //Da tabella ASCII a int (lol)
  String msg = "DEBUGM: Avvio movimento verso ";
  float reqSpeed[] = { 0, 0 };
  switch (movDirection) {
    case 'F':
      msg+="avanti ";
      
      reqSpeed[0] = 1;
      reqSpeed[1] = 1;
      advance(reqSpeed);
      
      break;
    case 'B':
      msg+="indietro ";

      reqSpeed[0] = -1;
      reqSpeed[1] = -1;
      advance(reqSpeed);
      
      break;
    case 'L':
      msg+="sinistra ";

      reqSpeed[0] = 0;
      reqSpeed[1] = 1;
      advance(reqSpeed);
      
      break;
    case 'R':
      msg+="destra ";

      reqSpeed[0] = 1;
      reqSpeed[1] = 0;
      advance(reqSpeed);
      
      break;
  }
  msg += "per " + String(remainingMov) + " secondi";
  Serial.println(msg);
  delay(remainingMov * 1000);
  stopEngines();
  Serial.println("DEBUGM: Movimento terminato");
}

void rotateForX(char rotDirection, char howMuch){
  String msg = "DEBUGM: Rotazione verso ";
  int forceLeft, forceRight;
  switch(rotDirection) {
    case 'L':
      msg += "sinistra ";
      forceLeft = -1;
      forceRight = 1;
      break;
    case 'R':
      msg += "destra ";
      forceLeft = 1;
      forceRight = -1;
      break;    
  }
  int angles[] = { 5, 10, 20, 30, 40, 50, 60, 70, 80, 90};
  float desiredAngle = angles[howMuch - 48];
  msg += "di " + String(desiredAngle) + " gradi";
  Serial.println(msg);
  //Calcolo dei gradi e azionamento cingoli
  delay(3000);
  Serial.println("DEBUGM: Ruotato");
}

void serialEvent(){
  //CHIAMATA QUANDO ARDUINO RICEVE DATI SU SERIALE
  if (Serial.available() > 0) {
    serialStream[0]='\0';
    serialStream[1]='\0';
    serialStream[2]='\0';
    
    Serial.readString().toCharArray(serialStream, 4);
    Serial.print("\nDEBUGM: carattere 1:");
    Serial.print(serialStream[0]);
    Serial.print(" carattere 2:");
    Serial.print(serialStream[1]);
    Serial.print(" carattere 3:");
    Serial.print(serialStream[2]);
    Serial.println();
    //SWITCH PRIMO CARATTERE
    switch (serialStream[0]) {
      case 'C':
        robotMode = serialStream[1];
        break;
      case 'F':
        continueFollowing = true;
        follow(serialStream[1]);
        break;
      case 'M':
        moveForX(serialStream[1], serialStream[2]);
        break;
      case 'P':
        rotateForX(serialStream[1], serialStream[2]);
        break;
    }
  }
}


