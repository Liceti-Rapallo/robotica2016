import serial
import threading
import json
import os
import time
from matplotlib import pyplot as PLT
from matplotlib import cm as CM
from matplotlib import mlab as ML
import numpy as NP

import globals as g

g.cfg = json.loads(open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "config.json")).read())

g.ser = serial.Serial("COM4", 9600)

time.sleep(1)
g.ser.setDTR(False)
time.sleep(1)

x = y = NP.linspace(-5, 5, 50)
X, Y = NP.meshgrid(x, y)
Z1 = ML.bivariate_normal(X, Y, 2, 2, 0, 0)
Z2 = ML.bivariate_normal(X, Y, 4, 1, 1, 1)
ZD = Z2 - Z1
x = X.ravel()
y = Y.ravel()
z = ZD.ravel()
print z
x = []
y = []
z = []

vals = []
gridsize = 30
PLT.title("Temperatura Ex.Boh.Ino")
PLT.subplot(111)

import random

def ping(text):
    g.ser.write(text)

    return g.ser.readall()


def send(text):
    g.ser.write(text)

def loop():
    global z
    g.ser.write("D")
    g.ser.readline()
    g.ser.readline()
    send("SAAA");
    for i in range(5):
        g.ser.write("G")
        out = g.ser.readline().split(":")

        x.append(out[0])
        y.append(out[1])
        z.append(out[2])
        print i

    # for X in range(50):
    # vals.append([])
    # for Y in range(50):
    # vals[X].append([])
    # z.append(random.uniform(1,0))
    # vals[X][Y] = randint(0 ,9)
    # time.sleep(g.cfg["arduino"]["pooling_dealy"])


loop()

x = NP.array(x).astype(NP.float)
y = NP.array(y).astype(NP.float)
z = NP.array(z).astype(NP.float)

print "ciao"
print z

PLT.hexbin(x, y, C=z, gridsize=gridsize, cmap=CM.jet, bins=50)
PLT.axis([x.min(), x.max(), y.min(), y.max()])

cb = PLT.colorbar()
cb.set_label('Temperatura')
PLT.show()

print os.path.join(os.path.dirname(os.path.realpath(__file__)), "config.json")


# threading.Thread(target=loop).start()
