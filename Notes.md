# Build Notes

## Day 1
- Started by gathering parts from Super Starter Kit
- Wired everything together
- Got a mini breadboard to attach ultrasonic sensor to servo and used elastic bands as I didn't want to attach anything permanently
- Coded the servo to turn 180 degrees in one direction and then turn back using help from the servo tutorial given with the kit
- Set up the button, potentiometer, ultrasonic sensor, RGB LED and active buzzer in code
- Got readings from ultrasonic sensor and got button and RGB LED to work
- Used claude to understand how to get reading from a potentiometer since it wasn't included in tutorials
- Learnt syntax for map() function and used to only detect when objects were in a certain range of the sensor
- Got buzzer to beep but a fixed speed
- Learnt how to write functions in c++ with [w3 schools](https://www.w3schools.com/cpp/cpp_functions.asp) and rewrote my code to be more efficient and use them
- Got stuck on how to time the buzzers without causing other components (such as servo motor) to also have a delay. Claude gave an example of using millis() and a servo to get the current time and check that against the last time the servo moved and I adapted this to work for the buzzer. I also added code using the map() function to make the buzzer beep faster depending on how close the object is but this wasn't working. I tested removing the delay(10); when updating the servo and it worked
- Issues left are: since delay(10): was removed in the for loop, I can't as easily control the speed of the servo; and the whole thing works fine when attached to my mac but when i unplug it and power it with a battery instead, the servo becomes jumpy and doesn't always turn correctly
- Added LCD1602 Module (screen) as I wanted a way to see the settings without having to rely on a computer or other monitor. I used the tutorial given with the super starter kit and claude to help connect the pins. Had to use pins A2-A5 since I ran out of other pins ( only 4 and 7 left)
- I only have 1 potentiometer and the tutorials used it to control the contrast but since i didn't have a spare I decided to use resistors. I attached V0 to 5V and used 2 1k ohm resistors but the screen was just bright blue so I used a 100k ohm resistor instead. However, it stayed bright blue. I found out from claude that the contrast uses high (5V) as low contrast and low (ground) as high contrast which was the opposite of what I thought. I attached V0 to ground instead of 5V with no resistors and the screen worked so I added a 1k ohm resistor to get a desired contrast

## Day 2
- Added a function to output the correct data (current state and threshold distance) to the LCD screen and refreshed the screen every time it checks if either thing is changed
- Changed 1k ohm resistor on contrast to 2k ohm resistor to look better
- Readded the delay(10); to the servo for loop and everything worked as intended including the buzzer but I don't know why it works now and didn't before
- Updated servo moving loop to also use millis() so no longer has delays and only delay is used on the button so everything stops wen modes are switched
- Looked into how to have [arduino communicate with  a python file over serial](https://38-3d.co.uk/blogs/blog/how-to-use-python-to-communicate-with-an-arduino-uno-over-serial) and installed pyserial library
- Tried to get python file to read from arduino serial with help from [arduino project hub](https://projecthub.arduino.cc/ansh2919/serial-communication-between-python-and-arduino-663756), [pyserial documentation](https://pyserial.readthedocs.io/en/latest/shortintro.html#opening-serial-ports) and [arduino forum](https://forum.arduino.cc/t/cannot-send-serial-data-from-python-to-arduino-uno/1137529) However, I kept getting an error saying port was busy. Eventually figured out it was because the serial was open and got the python file to read data correctly
- Got python script correctly detecting distance from object and whether it set off the alarm or not

## Day 3
- Remade python file structure to have a file for getting data from arduino and a file responsible for the GUI
- Learnt how to make a window using python with tkinter using [pythonguis.com](https://www.pythonguis.com/tutorials/create-gui-tkinter/)
- Got a visual of a line sweeping back and forth like a radar working with help from claude and [tutorialspoint.com](https://www.tutorialspoint.com/article/tkinter-how-to-create-colored-lines-based-on-length#:~:text=To%20create%20lines%20on%20a,the%20length%20of%20the%20line.)
- Changed data_fetcher.py to have a function to get data instead of continuously fetching it and gave that function to GUI.py
- Connected the python scripts together and it all worked perfectly until I switched mode where I got an error saying angle didn't have a value so there was an issue sending it from the arduino serial to the python file
- This was due to the delay(200); when checking if the button was pressed as it would pause sending the data but the python doesn't pause so I replaced that to use millis() and it now works
