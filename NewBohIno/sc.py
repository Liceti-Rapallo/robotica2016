#!/usr/bin/env python

import sys
import serial

from steamcontroller import SteamController, SCButtons
from steamcontroller.events import EventMapper, Pos
from steamcontroller.uinput import Keys

ser = None

def button_pressed_callback(evm, btn, pressed):
    print "Button {} was {}.".format(btn, 'pressed' if pressed else 'released')

    if btn == SCButtons.STEAM and not pressed:
        print "pressing the STEAM button terminates the programm"
        sys.exit()

def stick_axes_callback(evm, x, y):
    if x == 0:
        print "F"
    else:
        print "R" + str(int(float(x)/32768*255))
    # ser.write("R" + str(x/32768*255))

def tigger_axes_callback(evm, pos, value):
    if value == 0:
        print "F"
    else:
        print ("A" if pos == 0 else "I") + str(value)

def evminit():
    evm = EventMapper()
    evm.setButtonCallback(SCButtons.STEAM, button_pressed_callback)
    evm.setStickAxesCallback(stick_axes_callback)
    evm.setTrigAxesCallback(Pos.RIGHT, tigger_axes_callback)
    evm.setTrigAxesCallback(Pos.LEFT, tigger_axes_callback)
    return evm


if __name__ == '__main__':
    # ser = serial.Serial(sys.argv[1])
    evm = evminit()
    sc = SteamController(callback=evm.process)
    print "Controller Initialized"
    sc.run()
