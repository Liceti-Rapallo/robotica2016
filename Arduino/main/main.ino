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
  //prepareHC_SR04();					//prepara sensore HC-SR04
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
}
void follow(char what){
  while (continueFollowing){
    if (what=='S') {
      Serial.println("Seguendo suoni");
    } else {
      Serial.println("Seguendo immagini");
    }
    if (Serial.available() > 0) {
      if (Serial.readString()=="FN"){
        continueFollowing = false;
        Serial.println("Interrotto inseguimento");
      } else {
        Serial.println("Comando non accettato");
        Serial.println("Provare con FN per interrompere l'inseguimento");
      }
    }
    delay(1000);
  }
}

void serialEvent(){
  //CHIAMATA QUANDO ARDUINO RICEVE DATI SU SERIALE
  if (Serial.available() > 0) {
    serialStream[0]='\0';
    serialStream[1]='\0';
    serialStream[2]='\0';
    
    Serial.readString().toCharArray(serialStream, 4);
    Serial.print("\ncarattere 1:");
    Serial.print(serialStream[0]);
    Serial.print(" carattere 2:");
    Serial.print(serialStream[1]);
    Serial.print(" carattere 3:");
    Serial.print(serialStream[2]);
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
        break;
      case 'P':
        break;
      case 'T':
        break;
    }
  }
}


