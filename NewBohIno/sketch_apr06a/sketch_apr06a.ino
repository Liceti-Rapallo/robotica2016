#include <Motore.h>
#include <Motori.h>
#include <tools.h>

Motore* dx = new Motore(52,53,3,49,48);
Motore* sx = new Motore(50,51,10,46,47);
Motori* m = new Motori(dx, sx, 45);

void setup() {
  Serial.begin(9600);
  dx->corr = 10;
  sx->corr = 10;
}

void loop() {
  while(Serial.available()){
    String cmd = Serial.readString();
    switch(cmd.charAt(0)){
      case 'F':
        m->stop();
        break;
      case 'A':
        m->avanti(cmd.substring(1).toInt(), -1);
        break;
      case 'I':
        m->indietro(cmd.substring(1).toInt(), -1);
        break;
      case 'R':
        if(cmd.substring(1).toInt() > 0){
          m->attiva();
          dx->muovi(-cmd.substring(1).toInt());
          sx->muovi(cmd.substring(1).toInt());
        }
        break;
    }
  }
}
