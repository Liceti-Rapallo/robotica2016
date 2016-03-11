#include "Motore.h"

Motore::Motore(int pIN1, int pIN2, int pPWM, int pENC1, int pENC2)
{
  this->pPWM = pPWM;
  return;
};

Motore::avanti(int vel)
{
  analogWrite(this->pPWM, vel);
}

Motore::calcola()
{
  
}