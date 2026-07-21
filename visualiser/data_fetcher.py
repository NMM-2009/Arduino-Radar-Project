import serial
import time

arduino = serial.Serial(port = "/dev/cu.usbmodem14301", baudrate = 9600, timeout = 0.1)
time.sleep(2)

# Continuously read from serial on arduino until a keyboard interruption (Ctrl + C) is used then it stops
try:
    while True:
        raw = arduino.readline() # b'16\n'
        decoded = raw.decode('utf-8') # '16\'
        cleaned = decoded.strip() # '16'
        if cleaned == "":
            continue
        print(int(cleaned))
except KeyboardInterrupt:
    print("Stopping")
finally:
    arduino.close()
