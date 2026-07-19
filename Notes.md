# Build Notes

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
