#!/usr/bin/env python

import logging
import time

import serial
import subprocess

log = logging.getLogger()

from subprocess import Popen, PIPE

seq = '''keydown %s
usleep 2000
keyup %s
'''

def keypress(key):
    p = Popen(['xte'], stdin=PIPE)
    p.communicate(input=seq % (key, key))

BINDING = {
  "0": "Return", # Start
  "1": "W", # B
  "2": "X", # A
  "3": "Up",
  "4": "Down",
  "5": "Left",
  "6": "Right",
}

def standalone():
    while True:
        try:
            log.info("Opening serial port")
            ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=10)
            log.info("Serial port open")

            while True:
                b = ser.read()
                log.debug("Read %r", b)
                if b and ord(b) > 0: 
                    keypress(BINDING[b])
        except Exception:
            log.exception("Exception")
            time.sleep(20)


if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    standalone()
