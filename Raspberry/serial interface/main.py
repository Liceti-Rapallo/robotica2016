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

g.ser = serial.Serial("COM1 Perche' a noi piace Windows", 9600)

x = y = NP.linspace(-5, 5, 50)
X, Y = NP.meshgrid(x, y)
Z1 = ML.bivariate_normal(X, Y, 2, 2, 0, 0)
Z2 = ML.bivariate_normal(X, Y, 4, 1, 1, 1)
ZD = Z2 - Z1
x = X.ravel()
y = Y.ravel()
z = ZD.ravel()
print z
# x = []
# y = []
# z = []
vals = []
gridsize = 30
PLT.title("Temperatura Ex.Boh.Ino")
PLT.subplot(111)

import random


def loop():
    global z
    # while True:
    # send("s" + str(0b1100))
    # out = ping("g").split("-")
    # for X in range(50):
    # vals.append([])
    # for Y in range(50):
    # vals[X].append([])
    # z.append(random.uniform(1,0))
    # vals[X][Y] = randint(0 ,9)
    # time.sleep(g.cfg["arduino"]["pooling_dealy"])


loop()

print "ciao"
print z

PLT.hexbin(x, y, C=z, gridsize=gridsize, cmap=CM.jet, bins=50)
PLT.axis([x.min(), x.max(), y.min(), y.max()])

cb = PLT.colorbar()
cb.set_label('Temperatura')
PLT.show()

print os.path.join(os.path.dirname(os.path.realpath(__file__)), "config.json")


def ping(text):
    g.ser.write(text)

    return g.ser.readall()


def send(text):
    g.ser.write(text)

# threading.Thread(target=loop).start()
