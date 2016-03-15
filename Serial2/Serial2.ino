boolean debug=true;
byte serialStream[4];
boolean flags[24];
#define INFRAROSSI 11
#define X 2
#define Y 8
#define VX 3
#define VY 4

float sensorVal[24];
unsigned int sensorName[24];
unsigned int sensorPin[24];
int maxx=100;
int maxy=100;
int dirx=2;
int diry=2;


void setup() {
  // put your setup code here, to run once:
  sensorPin[0]=A0;
  sensorName[INFRAROSSI]=INFRAROSSI;
  sensorName[X]=X;
  sensorName[Y]=Y;
  sensorVal[X]=0;
  sensorVal[Y]=0;
  
  
  Serial.begin(57600);

  pinMode(sensorPin[INFRAROSSI], INPUT);
}

void measure(){
  if(sensorVal[X]>99 || sensorVal[X]<0) {
      sensorVal[Y]+=diry;
      dirx=-dirx;
      }
  if(sensorVal[Y]>99 || sensorVal[Y]<0) {
      diry=-diry;
      }
  sensorVal[X]+=dirx;
  sensorVal[INFRAROSSI]=analogRead(sensorPin[INFRAROSSI]);
}

void loop() {
  // put your main code here, to run repeatedly:
  measure();
  delay(10);
}

void setCommand(){
  int f_idx=0;
  for (int x=1; x < 4; x++){
    for (int i=8; i >= 0; i--){
      flags[f_idx]=bitRead(serialStream[x], i);
      f_idx++;
    }
  }

  if (debug){
    for (int i=0; i < 25; i++){
      if (flags[i]){Serial.print("Sensore "); Serial.print(i); Serial.print(" richiesto"); Serial.println();}
      else {Serial.print("Sensore "); Serial.print(i); Serial.print(" non richiesto"); Serial.println();}
    }
  }
}

void getCommand(){
  for(int x=0; x < 25; x++){
    if (flags[x]){
      Serial.print(sensorVal[x]);
      if (!(x==24)){
        Serial.print(":"); 
      }
    }
  }
  Serial.println();
}

void serialEvent(){
  // CHAR BYTE BYTE BYTE
  if (Serial.available() > 0) {
    serialStream[0]='\0';
    serialStream[1]='\0';
    serialStream[2]='\0';
    serialStream[3]='\0';
    Serial.readBytes(serialStream, 4);
    if (debug){
      Serial.print(char(serialStream[0]));
      Serial.print(" ");
      Serial.print(serialStream[1]);
      Serial.print(" ");
      Serial.print(serialStream[2]);
      Serial.print(" ");
      Serial.print(serialStream[3]);
      Serial.print(" ");
      Serial.println();
    }

    switch (serialStream[0]){
      case 'S':
        setCommand();
        break;
      case 'G':
        getCommand();
        break;
      case 'D':
        debug = !debug;
        Serial.print("DEBUG is "); Serial.println(debug);
        break;
      default:
        Serial.println("Comando sconosciuto");
        break;
    }
  }
}
