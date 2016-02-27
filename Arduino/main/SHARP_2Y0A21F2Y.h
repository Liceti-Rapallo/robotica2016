/*
  Libreria per utilizzare il sensore SHARP 2Y0A21F2Y
  Utilizzo:
    Includere con:
      #include "SHARP_2Y0A21F2Y"
    Richiamare quando si desidera una misurazione getSHARP2Y0A21F2Ymeasure()
    Richiamare quando si desidera una misurazione mediata getSHARP2Y0A21F2Ymeasure_smooth()
*/
int getSHARP2Y0A21F2Ymeasure(){
  //Ottiene una misurazione
  float ArduinoVoltageResolution = 0.0048828125;       //analogRead ritorna voltaggio di input/1024, questa è la minima variazione misurabile
  float voltaggio = analogRead(IR_ANALOG_IN) * ArduinoVoltageResolution;
  if (voltaggio < 0.50) { return 999; }
  int cm = int(27.728 * pow(voltaggio, -1.2045));
  if (cm > IR_MaxRange) {
    return -1;
  } else if (cm > IR_MaxRange) {
    return 999;
  } else {
    return cm;
  }
}

int getSHARP2Y0A21F2Ymeasure_smooth(){
  //Ottiene una misurazione mediata tra le ultime x definite nel file di configurazione
  int tooHigh=0;
  int tooLow=0;
  
  long sum=0;
  
  int measures[IR_Smoothing];  //predispone un array di misurazioni
  int ValidSamples=0;           //numero di sample validi
  
  for (int i=0; i < IR_Smoothing; i++){
    measures[i] = getSHARP2Y0A21F2Ymeasure();
    if (measures[i] == -1) {
      tooLow++;
    } else if (measures[i] == 999) {
      tooHigh++;
    } else {
      ValidSamples++;
      sum = sum + measures[i];
    }
  }

  if ( ValidSamples > (IR_Smoothing % IR_ValidRatio)) {
    return sum / ValidSamples;  
  } else if (tooLow > tooHigh) {
    return -1;
  } else {
    return 999;
  }
}
