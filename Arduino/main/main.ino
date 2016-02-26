/*
	File primario
*/

//HEADERS
#include "_cfg.h"
#include "hc-sr04.h"
//FINE HEADERS

//GLOBALI
char serialStream[3];
/*
	A = Automatica
	D = Drone
	I = Idle
*/
char robotMode = 'A';				

void setup()
{
  Serial.begin(SerialRate); 
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
			break;
		case 'I':
			//Modalità idle
			break;
	}
	delay(50);
}

void goAuto(){
  Serial.println(getHC_SR04Measure_smooth());         // TEST HC-SR04
}

void goDrone(){
  
}

void getIdle(){
  
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
  }
}
