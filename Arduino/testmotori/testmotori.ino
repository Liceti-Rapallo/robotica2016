#include <Motore.h>
#include <Motori.h>
#include <tools.h>

Motori m;

void setup(){
  Motore dx = Motore();
  Motore sx = Motore();

  dx->corr = 10;
  sx->corr = 10;

  m = Motori(dx, sx);

  m->avanti(100);
}

void loop(){

}
