#include "Motore.h"

Motore::Motore(int pIN1, int pIN2, int pPWM, int pENC1, int pENC2)
{

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
        int oldPos = x[0];
        shiftArray(x);
        shiftArray(t);
        shiftArray(v);
        shiftArray(a);
        if (digitalRead(pENC2) == LOW) {
            x[0] = oldPos - 1;
        } else {
            x[0] = oldPos + 1;
        }
        t[0] = millis();
        v[0] = (x[1]-x[0])/(t[1]-t[0]);
        a[0] = (v[1]-v[0])/(t[1]-t[0]);
    }
    pENC1Last = n;
}
