void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
}

byte incomingByte1, incomingByte2;
void serialEvent(){
  while (Serial.available()){
    incomingByte1 = Serial.read();
    Serial.println(incomingByte1);
    Serial.println("---");
    for (int i=8; i >= 0; i--){
      Serial.print(bitRead(incomingByte1, i));
      Serial.print(" ");
    }
    Serial.println("\n---");
  }
}


