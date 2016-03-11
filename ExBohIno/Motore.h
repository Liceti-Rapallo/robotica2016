#ifndef Motore_h
#define Motore_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <inttypes.h>


class Motore
{
  public:
    int x[5];
    int v[4];
    int a[3];
    int pPWM;
    Motore(int pIN1, int pIN2, int pPWM, int pENC1, int pENC2);
};

#endif