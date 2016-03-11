#define PWMA 3
#define PWMB 9
#define AIN1 4
#define AIN2 7
#define BIN1 8
#define BIN2 12
#define STBY 2
 
#define SENSIBILITA 200
 
int SHIR = A5;
 
void setup()
{
  pinMode( STBY,OUTPUT );
  pinMode( PWMA,OUTPUT );
  pinMode( PWMB,OUTPUT );
  pinMode( AIN1,OUTPUT );
  pinMode( AIN2,OUTPUT );
  pinMode( BIN1,OUTPUT );
  pinMode( BIN2,OUTPUT );
 
  pinMode( SHIR,INPUT );
 
  digitalWrite( STBY,HIGH );
}
 
void loop()
{
  int dist = analogRead(SHIR);
  if ( dist > SENSIBILITA ) { gira(); }
  else                      { avanti(); }
}
 
void avanti()
{
    digitalWrite( AIN1,HIGH );
    digitalWrite( AIN2,LOW );
    digitalWrite( BIN1,HIGH );
    digitalWrite( BIN2,LOW );
 
    analogWrite( PWMA,100 );
    analogWrite( PWMB,100 );
}
 
void indietro()
{
    digitalWrite( AIN1,LOW );
    digitalWrite( AIN2,HIGH );
    digitalWrite( BIN1,LOW );
    digitalWrite( BIN2,HIGH );
 
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
