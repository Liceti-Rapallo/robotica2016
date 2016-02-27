/*
  Libreria per utilizzare il termistore TDC310
  Utilizzo:
    Includere con:
      #include "TDC310.h"
    Richiamare quando si desidera una misurazione getTDC310temp()
*/

float getTDC310temp() {
  //Ottiene la temperatura dal termistore
  double Temp;
  Temp = log(((10240000/analogRead(IR_ANALOG_IN)) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;           // C°
  return Temp;
}

