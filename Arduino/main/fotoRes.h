/*
  Libreria per utilizzare la fotoresistenza
  Utilizzo:
    Includere con:
      #include "fotoRes.h"
    Richiamare quando si desidera una misurazione getLight()
*/

double getLight(){
  float ArduinoVoltageResolution = 0.0048828125;       //analogRead ritorna voltaggio di input/1024, questa è la minima variazione misurabile
  float voltaggio = analogRead(LHT_pin) * ArduinoVoltageResolution;
  return voltaggio;
}

