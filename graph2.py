import numpy as np
import matplotlib.pyplot as plt
import threading
import time
import random

coords = np.empty([256, 256])

def measurement():
    randX = random.randrange(0, 10000)
    randY = random.randrange(0, 10000)
    randV = random.uniform(0.0, 1.0)
    coords[int((256/10000)*randX), int((256/10000)*randY)]=randV
    print("X: "+str(int((256/10000)*randX))+" Y: "+str(int((256/10000)*randY))+" V: "+str(randV))

def reDraw():
    while True:
        measurement()
        x=[]
        y=[]
        v=[]
        for r in range(0,255):
            for c in range(0,255):
                x.append(r)
                y.append(c)
                v.append(coords[r,c])
        plt.axis([0, 256, 0, 256])
        plt.hexbin(x, y, v, cmap=plt.get_cmap('Greys'), gridsize=50)
        plt.draw()
        time.sleep(0.5)


plt.title("Esp. Boh. Ino")

t = threading.Thread(target=reDraw)
t.start()
plt.show()

# t=None
