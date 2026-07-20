# Build Notes

## Day 1
- Started by gathering parts from Super Starter Kit
- Wired everything together
- Got a mini breadboard to attach ultrasonic sensor to servo and used elastic bands as I didn't want to attach anything permenantly
- Coded the servo to turn 180 degrees in one direction and then turn back using help from the servo tutorial given with the kit
- Set up the button, potentiometer, ultrasonic sensor, RGB LED and active buzzer in code
- Got readings from ultrasonic sensor and got button and RGB LED to work
- Used claude to understand how to get reading from a potentiometer since it wasn't included in tutorials
- Learnt syntax for map() function and used to only detect when objects were in a certain range of the sensor
- Got buzzer to beep but a fixed speed
- Learnt how to write functions in c++ with [w3 schools](https://www.w3schools.com/cpp/cpp_functions.asp) and rewrote my code to be more efficient and use them
- Got stuck on how to time the buzzers without causing other components (such as servo motor) to also have a delay. Claude gave an example of using millis() and a servo to get the current time and check that against the last time the servo moved and I adapted this to work for the buzzer. I also added code using the map() function to make the buzzer beep faster depending on how close the object is but this wasn't working. I tested removing the delay(10); when updating the servo and it worked
- Issues left are: since delay(10): was removed in the for loop, I can't as easily control the speed of the servo; and the whole thing works fine when attached to my mac but when i unplug it and power it with a battery instead, the servo becomes jumpy and doesn't always turn correctly
- Added LCD1602 Module (screen) and used the tutorial and claude to help connect the pins. Had to use pins A2-A5 since I ran out of other pins ( only 4 and 7 left)
- I only have 1 potentiometer and the tutorials used it to control the contrast but since i didn't have a spare I decided to use resisitors. I attached V0 to 5V and used 2 1k ohm resistors but te screen was just bright blue so I used a 100k ohm resistor instead. However, it stayed bright blue. I found out from claude that the contrast uses high (5V) as low contrast and low (ground) as high contrast which was the opposite of what I thought. I attached V0 to ground instead of 5V with no resistors and the screen worked so I added a 1k ohm resistor to get a desired contrast

## Day 2
- Added a function to output the correct data (current state and threshold distance) to the LCD screen and refreshed the screen every time it checks if either thing is changed
- Changed 1k ohm resistor on contrast to 2k ohm resisitor to look better
- Readded the delay(10); to the servo for loop and everything worked as intended including the buzzer but I don't now why it works now and didn't before
