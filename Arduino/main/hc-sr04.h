/*
	Libreria per utilizzare il sensore a ultrasuoni HC-SR04
	Utilizzo:
    Includere con:
      #include "hc-sr04.h"
		Richiamare dentro a setup() prepareHC_SR04()
		Richiamare quando si desidera una misurazione getHC_SR04Measure()
		Richiamare quando si desidera ottenere una misurazione mediata getHC_SR04Measure_smooth()
*/
void prepareHC_SR04() {
	//se chiamata imposta i pin definiti nella configurazione
	
	pinMode(HC_PinTRIG, OUTPUT);
	pinMode(HC_PinECHO, INPUT);
}

int getHC_SR04Measure() {
	//se chiamata ritorna la distanza in CENTIMETRI, -1 se il valore è fuori dal range in negativo e 999 se il valore è fuori range in positivo
	digitalWrite(HC_PinTRIG, LOW);
	delayMicroseconds(2);
	digitalWrite(HC_PinTRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(HC_PinTRIG, LOW);
	
	unsigned long tempo=pulseIn(HC_PinECHO, HIGH, (HC_MaxRange*58.2));
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

int getHC_SR04Measure_smooth() {
	//passandogli un parametro effettua la media delle ultime misurazioni specificate nella configurazione
  int tooHigh=0;
  int tooLow=0;
	
	long sum=0;
	
	int measures[HC_Smoothing];  //predispone un array di misurazioni
  int ValidSamples=0;           //numero di sample validi
  
	for (int i=0; i < HC_Smoothing; i++){
		measures[i] = getHC_SR04Measure();
    if (measures[i] == -1) {
      tooLow++;
    } else if (measures[i] == 999) {
      tooHigh++;
    } else {
      ValidSamples++;
      sum = sum + measures[i];
    }
	}

	if ( ValidSamples > (HC_Smoothing % HC_ValidRatio)) {
		return sum / ValidSamples;	
	} else if (tooLow > tooHigh) {
		return -1;
	} else {
    return 999;
	}
}
