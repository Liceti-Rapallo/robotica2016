#readfrompi.py
import serial as s
import time
ser = s.Serial("COM4", 9600)
time.sleep(1)
ser.setDTR(False)
time.sleep(1)
print ser.write("D")
print ser.readline()
print ser.readline()
print ser.write("SAAA")
while True:
    ser.write("G")
    print ser.readline()
