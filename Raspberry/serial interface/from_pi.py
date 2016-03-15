#readfrompi.py
import serial as s
import time
ser = s.Serial("/dev/ttyACM0", 57600)
time.sleep(1)
ser.setDTR(level=0)
time.sleep(1)
print ser.write("D")
print ser.readline()
print ser.readline()
print ser.write("SAAA")
while True:
    ser.write("G")
    print ser.readline()
