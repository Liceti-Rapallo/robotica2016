#ifndef LIB_MOTORE_H
#define LIB_MOTORE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <inttypes.h>

#include "tools.h"

class Motore
{
public:
 	float x[5];
	float v[4];
	float a[3];

  int pIN1;
  int pIN2;
	int pPWM;
  int pENC1;
  int pENC2;

  int pot;

  int pENC1Last;

	Motore(int pIN1, int pIN2, int pPWM, int pENC1, int pENC2);

    void loop();
    void muovi(int pot);
    void stop();
    void regola();
    void letturaEncoder();

private:
    int nextPos(int pos);
};

#endif //LIB_MOTORE_H
