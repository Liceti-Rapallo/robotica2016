import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import matplotlib.mlab as mlab
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import random
import time
import threading

class coordinate:
    def __init__(self, x=0, y=0, v=0):
        self.x=x
        self.y=y
        self.v=v

coords = [];
def fakeMeasure():
    coords.append(coordinate(random.randrange(0,10),random.randrange(0,10),random.uniform(0.0, 1.0)))

x=[]
y=[]
v=[]
def reDraw():
    while True:
        fakeMeasure()
        x=[]
        y=[]
        v=[]
        for item in coords:
            x.append(float(item.x))
            y.append(float(item.y))
            v.append(float(item.v))
        plt.axis([0, 10, 0, 10])
        plt.hexbin(x, y, v, cmap=plt.get_cmap('Greys'), gridsize=50)
        plt.draw()
        time.sleep(0.5)


plt.title("Esp. Boh. Ino")

t = threading.Thread(target=reDraw)
t.start()

plt.show()

t=None
