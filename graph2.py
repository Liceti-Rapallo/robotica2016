import numpy as np
import matplotlib.pyplot as plt
import threading
import time
import random
import math


######### MISURA #####
#aggiunge una nuova misura (da x,y=posizione,v=misura)
def measurement():
    randX = random.randrange(0, 256)
    randY = random.randrange(0, 256)
    randV = random.uniform(0, 256)
    coords[randX, randY]=randV
    print("X: "+str(randX)+" Y: "+str(randY)+" V: "+str(randV))

######### reDraw ###########
def reDraw():
    while True:
        measurement()
        plt.imshow(psf, cmap="hot")
        plt.show()
        time.sleep(0.2)

############## MAIN #############
coords = np.empty([256, 256])
coords=np.zeros([256, 256])
psf = np.empty([256, 256])
psf = np.zeros([256, 256])
for r in range(0,255):
    for c in range(0,255):
        #psf[r,c] = math.exp(-((r-127)^2)/2)
        psf[r,c] = 255*math.exp( ( -((r-127)**2+(c-127)**2) / 10 ))
        if ((r > 120 and r < 130)and(c > 120 and c < 130)):
            print("X: "+ str(r) +" Y: "+ str(c) +" V: "+str(psf[r,c]))
'''
for r in range(0,255):
    for c in range(0,255):
        psf[r,c]= abs(127.5-c) + abs(127.5-r)
'''
# print (psf[128,128])
plt.title("Esp. Boh. Ino")
coords=psf
shim=plt.imshow(psf, cmap="afmhot")

i=0
while i < 50:
    measurement()
    shim.set_data(psf)
    plt.draw()
    #time.sleep(0.1)
    i+=1
f_coords=np.fft.fft2(coords)
f_psf=np.fft.fft2(psf)
f_insieme=f_psf*f_coords
insieme=np.fft.ifft2(f_insieme)

plt.imshow(psf, cmap="afmhot")
plt.show()


#t = threading.Thread(target=reDraw)
#t.start()
