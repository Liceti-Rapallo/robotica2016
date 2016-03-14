/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include "hc-sr04.h"
#include "_cfg.h"

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int cm;
int mes[360];

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  prepareHC_SR04();
  myservo.write(0);
}

void loop() {
  
  for (int i=0; i <= 360; i+=10){              
    myservo.write(abs(180-i));
    delay(100);
    cm=getHC_SR04Measure();
    if (!(cm==999)){
      //mes[i]+=cm;
      Serial.println(cm);
    }
    //Serial.println(cm);
    delay(100);  
  }
}



