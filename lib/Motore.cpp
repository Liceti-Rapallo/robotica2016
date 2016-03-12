#include "Motore.h"

Motore::Motore(int pIN1, int pIN2, int pPWM, int pENC1, int pENC2)
{
    Xindex = 0;
    Vindex = 0;
    Aindex = 0;

    pENC1Last = LOW;

    this->pIN1 = pIN1;
    this->pIN2 = pIN2;
    this->pPWM = pPWM;
    this->pENC1 = pENC1;
    this->pENC2 = pENC2;
};

//Eseguire qui i controlli periodici
void Motore::loop()
{
    if(vel != 0)//Non regola i mototi se e' formo
    {
        letturaEncoder();
        regola();
    }
}

//vel = velocita'(positiva = avanti, negativa = indietro, 0 = stop)
void Motore::muovi(int vel)
{
    if(vel == 0)
    {
        digitalWrite(pIN1, LOW);
        digitalWrite(pIN2, LOW);
    }
    if(vel > 0)
    {
        digitalWrite(pIN1, HIGH);
        digitalWrite(pIN2, LOW);
    }
    else
    {
        digitalWrite(pIN1, LOW);
        digitalWrite(pIN2, HIGH);
    }

    analogWrite(pPWM, vel);
}

//Arresta i motori
void Motore::stop()
{
    muovi(0);
}

void Motore::regola()
{
    //TODO: Algoritmo per aggiustare i motori
}

void Motore::letturaEncoder()
{
    n = digitalRead(pENC1);
    if ((pENC1Last == LOW) && (n == HIGH)) {
        int oldPos = x[Xindex];
        if (digitalRead(pENC2) == LOW) {
            x[nextPos(&Xindex, x)] = oldPos - 1;
        } else {
            x[nextPos(&Xindex, x)] = oldPos + 1;
        }
    }
    pENC1Last = n;
}