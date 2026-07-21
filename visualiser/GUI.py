from tkinter import *
from math import *
from data_fetcher import getData

cmPixelFactor = 10

def drawLine():
    global line
    reading = getData()
    if reading is not None:
        angle, distance, detected = reading
    canvas.delete(line)
    phi = radians(angle)
    x = cos(phi) * distance * cmPixelFactor
    y = sin(phi) * distance * cmPixelFactor
    if detected == 0:
        line = canvas.create_line(int(canvasWidth) / 2, int(canvasHeight) / 2 + 200, int(canvasWidth) / 2 - x, int(canvasHeight) / 2 + 200 - y, fill = "green", width = 5)
    else:
        line = canvas.create_line(int(canvasWidth) / 2, int(canvasHeight) / 2 + 200, int(canvasWidth) / 2 - x, int(canvasHeight) / 2 + 200 - y, fill = "red", width = 5)
    root.after(10, drawLine)

root = Tk() # Make a window

# Set window properties
root.title("Arduino Radar")
root.configure(background = "gray")
root.minsize(200, 200)
root.maxsize(3000, 2000)
root.geometry("1000x1000") #  "300x300+50+50" Takes width and height and x and y coordinates (window in top left if not specified)

# Labels
Label(root, text = "Arduino Radar Alarm").pack()

canvasHeight = "1000"
canvasWidth = "2000"
canvas = Canvas(root, width = canvasWidth, height = canvasHeight, background = "black")
canvas.pack()
line = canvas.create_line(0, 0, 0, 0)

drawLine()
root.mainloop()
