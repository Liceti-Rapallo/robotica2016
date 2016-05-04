import numpy
import os
import time
import random

AREA = numpy.zeros((20, 20))
maxBoredom = 50

xPos=0
yPos=0
boringCount=0
direction=1

def printMatrix():
        os.system('cls' if os.name == 'nt' else 'clear')
        for r in range(0 , AREA.shape[0]-1):
                rowTxt = ''
                for c in range(0 , AREA.shape[1]-1):
                        if r == yPos and c == xPos:
                                rowTxt = rowTxt + '@ '
                        elif AREA[c,r]== -1:
                                rowTxt = rowTxt + 'X '
                        else:
                                rowTxt = rowTxt + str( AREA[c,r].astype(int) ) + ' '
                print(rowTxt)
        print()
        print('X: '+ str(xPos) +' Y:' + str(yPos))

def stateUpdater():
        AREA[xPos , yPos] += 1
        global direction
        if not(AREA[xPos+direction,yPos] == -1) and (xPos+direction) <  (AREA.shape[0]-1) and not (xPos+direction) < 0 and boringCount < maxBoredom:
                moveMe(direction ,0)
                global boringCount
                boringCount += 1
        else:
                pathFind()

def pathFind():
        global direction
        global boringCount
        if (xPos+direction) <  (AREA.shape[0]-1):
                if not (AREA[xPos, yPos-1] == -1) and not (yPos+1) > (AREA.shape[1]-1):
                        moveMe(0,  1)
                elif not (AREA[xPos, yPos+1] == -1):
                        moveMe(0, -1)
        boringCount = 0
        direction *= -1
        stateUpdater()
def moveMe(x , y):
        global xPos
        xPos = xPos + x
        global yPos
        yPos = yPos + y

for i in range(0, random.randint(0,15)):
        obstacleX=random.randint(0, (AREA.shape[0]-1))
        obstacleY=random.randint(0, (AREA.shape[1]-1))
        AREA[obstacleX, obstacleY] = -1
while True:
        printMatrix()
        stateUpdater()
        time.sleep(0.2)
