/*
	Libreria per utilizzare il sensore a ultrasuoni HC-SR04
	Utilizzo:
		Includere la libreria:
			#include <hc-sr04.ino>
		Richiamare dentro a setup() prepareHC-SR04()
		Richiamare quando si desidera una misurazione getHC-SR04Measure()
*/

/*
	Configurazione:
		PinTRIG: il pin di Arduino connesso a TRIG
		PinECHO: il pin di Arduino connesso a ECHO
*/
#define PinTRIG 1
#define PinECHO 2

void prepareHC-SR04() {
	//se chiamata imposta i pin definiti nella configurazione
	
	pinMode(PinTRIG, OUTPUT);
	pinMode(PinECHO, INPUT);
}

int getHC-SR04Measure() {
	//se chiamata ritorna la distanza in CENTIMETRI o -1 se il valore è fuori dal range
	long tempo;
	long distanza;
	
	digitalWrite(PinTRIG, LOW);
	delayMicroseconds(2);
	digitalWrite(PinTRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(PinTRIG, LOW);
	
	tempo=pulseIn(PinECHO, HIGH);
	distanza=(tempo/2)/29.1;
	if (distanza >= 300 || distanza <= 5) {
		return -1;
	}
	else
	{
		return distanza;
	}
}