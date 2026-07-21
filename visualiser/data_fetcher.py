import serial
import time

arduino = serial.Serial(port = "/dev/cu.usbmodem14301", baudrate = 9600, timeout = 0.1)
time.sleep(2)

def getData():
    line = arduino.readline().decode('utf-8').strip()
    if line == "":
        return None
    angleStr, distanceStr, detectedStr = line.split(",")
    return int(angleStr), int(distanceStr), int(detectedStr)
