#ifndef LIB_MOTORI_H
#define LIB_MOTORI_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <inttypes.h>

#include "Motore.h"

class Motori
{
public:
    Motore *dx, *sx;
    int pos;//Posizione attuale
    int stoppos;//Positione dove fermarsi

    Motori(Motore* dx, Motore* sx);

    void loop();
    void avanti(int vel, int space);
    void indietro(int vel, int space);
    void muovi(int vel, int space);
    void stop();
};

#endif //LIB_MOTORI_H
