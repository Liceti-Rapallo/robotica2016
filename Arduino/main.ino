/*
	File primario
*/

//HEADERS
#include <hc-sr04.ino>
//FINE HEADERS

//COSTANTI
#define SerialRate		19200		//19200 = c.a. 2 kBps
//FINE COSTANTI

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
  prepareHC-SR04();					//prepara sensore HC-SR04
}

void loop()
{
	//INPUT
	if (Serial.available() > 0) {
		serialStream = Serial.read();
	}
	//LOGICA
	switch (robotMode) {
		case A:
			//Modalit� autonoma
			break;
		case D:
			//Modalit� drone
			break;
		case I:
			//Modalit� idle
			break;
	}
	
}