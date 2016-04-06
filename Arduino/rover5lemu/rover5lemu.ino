#include <Motore.h>
#include <Motori.h>
#include <tools.h>

Motore* dx = new Motore(52,53,3,49,48);
Motore* sx = new Motore(50,51,10,46,47);
Motori* m = new Motori(dx, sx, 45);

void setup(){
  dx->corr = 10;
  sx->corr = 10;

  m->avanti(100, -1);
}

void loop(){

}
