#include "Motori.h"

Motori::Motori(Motore dx, Motore sx)
{
    this->dx = dx;
    this->sx = sx;
};

//Eseguire qui i controlli periodici
void Motori::loop()
{
    if(stoppos != -1)
        if(pos > stoppos)
        {
            stop();
        }

    dx->loop();
    sx->loop();
}

//vel = velocita', space = spazio in cm(-1 = infinito)
void Motori::avanti(int vel, int space)
{
    muovi(vel, space);
}

//vel = velocita', space = spazio in cm(-1 = infinito)
void Motori::indietro(int vel, int space)
{
    muovi(-vel, space);
}

//vel = velocita'(positiva = avanti, negativa = indietro, 0 = stop), space = spazio in cm(-1 = infinito)
void Motori::muovi(int vel, int space)
{
    if(space == -1)
        stoppos = -1;
    else
        stoppos = pos + space;

    dx->mouvi(vel);
    sx->mouvi(vel);
}

//Arresta i motori
void Motori::stop()
{
    dx->stop();
    sx->stop();
    stoppos = -1;
}