int QEM [16] = {0,-1,1,2,1,0,2,-1,-1,2,0,1,2,1,-1,0};
int inputA = 2;
int inputB = 3;
int Old = 0;
int New = 0;
int Out = 0;
 
void setup()
{
   Serial.begin( 9600 );
   Serial.println( "Start" );
 
   pinMode( inputA, INPUT );
   pinMode( inputB, INPUT );
}
 
void loop() {
   Old = New;
   New = digitalRead (inputA) * 2 + digitalRead (inputB);
 
   Out = QEM [Old * 4 + New];
   Serial.print( "XOR: " );
   Serial.println( Out );}
