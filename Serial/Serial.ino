void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
}

byte incomingByte;
void serialEvent(){
  while (Serial.available()){
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    Serial.println("---");
    for (int i=8; i >= 0; i--){
      
      Serial.print(bitRead(incomingByte, i));
      Serial.print(" ");
      
    }
    Serial.println("\n---");
  }
}


