// Generale
#define SerialRate 57600 	// baud rate su seriale (57600 baud = 7,20 KB/s)

// Sensore HC-SR04
#define HC_PinTRIG 3	        //Pin sul quale è attaccato Trig
#define HC_PinECHO 5	        //Pin sul quale è attaccato Echo
#define HC_ValidRatio 3       //Rapporto misurazioni scartate / misurazioni valide oltre il quale la misurazione viene approssimata verso + o - infinito            [DEFAULT: 3]
#define HC_Smoothing 30       //Numero di misurazioni conteggiate nel calcolo della media                                                                           [MIN: 1 | MAX: 50]
#define HC_MaxRange 150       //Numero di centimetri sopra al quale verrà ritornato il valore di default                                                            [MIN: 50| MAX:250 | DEFAULT:150]
#define HC_MinRange 10        //Numero di centimetri sotto ai quali verrà ritornato il valore di default                                                            [MIN: 5 | MAX: 30 | DEFAULT: 10]

// Sensore SHARP 2Y0A21F2Y
#define IR_ANALOG_IN 0        //Pin analogico sul quale è connesso il sensore
#define IR_ValidRatio 3       //Rapporto misurazioni scartate / misurazioni valide oltre il quale la misurazione viene approssimata verso + o - infinito            [DEFAULT: 3]
#define IR_Smoothing 30       //Numero di misurazioni conteggiate nel calcolo della media      
#define IR_MaxRange 40        //Numero di centimetri sopra al quale verrà ritornato il valore di default                                                            [MIN: 20| MAX: 80 | DEFAULT: 40]
#define IR_MinRange 8         //Numero di centimetri sotto ai quali verrà ritornato il valore di default                                                            [MIN: 5 | MAX: 20 | DEFAULT:  8]

