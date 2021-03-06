//sketch motore ed encoder
#define PWMA 3
#define PWMB 9
#define AIN1 53
#define AIN2 52
#define BIN1 50
#define BIN2 51
#define STBY 45
 
#define SENSIBILITA 200
 
 int SHIR = A0;
 int val; 
 
 int encoder0PinA = 46;
 int encoder0PinB = 47;
 int encoder0Pos = 0;
 int encoder0PinALast = LOW;
 
 
 int encoder1PinA = 48;
 int encoder1PinB = 49;
 int encoder1Pos = 0;
 int encoder1PinALast = LOW;
 
 int n = LOW;
 int m = LOW;
 
void setup()
{
  pinMode ( STBY,OUTPUT );
  pinMode ( PWMA,OUTPUT );
  pinMode ( PWMB,OUTPUT );
  pinMode ( AIN1,OUTPUT );
  pinMode ( AIN2,OUTPUT );
  pinMode ( BIN1,OUTPUT );
  pinMode ( BIN2,OUTPUT );
  pinMode (encoder0PinA,INPUT);
  pinMode (encoder0PinB,INPUT);
  pinMode (encoder1PinA,INPUT);
  pinMode (encoder1PinB,INPUT);
  pinMode( SHIR,INPUT );
  Serial.begin (9600);
  digitalWrite( STBY,HIGH );
}
 
void loop()

{/*
  int dist = analogRead(SHIR);
  if ( dist > SENSIBILITA ) { gira();}
  else                      { avanti();}
  */
  enccount();
}
 
void avanti()
{
    digitalWrite( AIN1,HIGH );
    digitalWrite( AIN2,LOW );
    digitalWrite( BIN1,HIGH );
    digitalWrite( BIN2,LOW );
    enccount();
    analogWrite( PWMA,100 );
    analogWrite( PWMB,100 );
}
 
void indietro()
{
    digitalWrite( AIN1,LOW );
    digitalWrite( AIN2,HIGH );
    digitalWrite( BIN1,LOW );
    digitalWrite( BIN2,HIGH );
    enccount();
    analogWrite( PWMA,100 );
    analogWrite( PWMB,100 );
}
 
void alt()
{
    analogWrite( PWMA,50 );
    analogWrite( PWMB,50 );
 
    digitalWrite( AIN1,LOW );
    digitalWrite( AIN2,LOW );
    digitalWrite( BIN1,LOW );
    digitalWrite( BIN2,LOW );
}
 
void gira()
{
  // STOP x 1/2 sec
  alt();
  delay( 500 );
 
  // INDIETRO x 1/2 secondo
  indietro();
  delay( 500 );
 
  // STOP x 1/2 sec
  alt();
  delay( 500 );
 
  // Gira
  digitalWrite( AIN1,LOW );
  digitalWrite( AIN2,HIGH );
  digitalWrite( BIN1,HIGH );
  digitalWrite( BIN2,LOW );
 
  analogWrite( PWMA,100 );
  analogWrite( PWMB,100 );
 
  delay( 200 );
}
void enccount()
{
  boolean a=false;
  n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
     } else {
       encoder0Pos++;
     }
     a=true;
   } 
   encoder0PinALast = n;
   
   n = digitalRead(encoder1PinA);
   if ((encoder1PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder1PinB) == LOW) {
       encoder1Pos--;
     } else {
       encoder1Pos++;
     }
     a=true;
   } 
   encoder1PinALast = n;
   
   if(a)
   {
   Serial.print ("L: ");
   Serial.print (encoder0Pos);
   Serial.print ("/ R: ");
   Serial.print (encoder1Pos);
   Serial.println();
   }
 }
/*
int val; 
 int encoder0PinA = 11;//8
 int encoder0PinB = 13;//12
 int encoder0Pos = 0;
 int encoder0PinALast = LOW;
 int n = LOW;

 void setup() { 
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   Serial.begin (9600);
 } 

 void loop() { 
   n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
     } else {
       encoder0Pos++;
     }
     Serial.print (encoder0Pos);
     Serial.print ("/");
   } 
   encoder0PinALast = n;
 } */
 
