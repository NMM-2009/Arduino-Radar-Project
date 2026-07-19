#include <SR04.h>
#include <Servo.h>

unsigned long lastBeep = 0; // Used to have delays with buzzer without delaying the rest of the system
int beepInterval;

Servo myServo;
int pos = 0;

int buzzer = 10;
int buzzerState = 0; // 0 means buzzer is off and 1 means buzzer is on

int button = 2;
int setting = 0; // 0 means system is off, 1 means system is on

#define RED 6
#define GREEN 5
#define BLUE 3

#define TRIG 12
#define ECHO 11
SR04 sr04 = SR04(ECHO, TRIG);
long a;

int pot = A0;

void measure(){
  // Check if button is pressed and switch to arm/disarm
  if (digitalRead(button) == LOW){
      setting = 1 - setting;
      delay(200);
    }

  // Get distance from ultrasonic sensor and check if an object is within a certain distance
  a = sr04.Distance();
  int threshold = map(analogRead(pot), 0, 1023, 5, 60);
  if (setting == 1){
    if (a <= threshold){
      beepInterval = map(a, 0, threshold, 1, 500);
      alarm();
    }else{
      digitalWrite(GREEN, 125);
      digitalWrite(RED, 125);
      digitalWrite(BLUE, LOW);
      digitalWrite(buzzer, LOW);
      buzzerState = 0;
    }

  }else{
    digitalWrite(GREEN, 125);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(buzzer, LOW);
    buzzerState = 0;
  }
}
// Turn LED to red and have buzzer beep increasingly quickly as object gets closer
void alarm(){
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, 125);
  digitalWrite(BLUE, LOW);

  unsigned long now = millis();
  if (now - lastBeep >= beepInterval){
    lastBeep = now;
    if (buzzerState == 1){
      digitalWrite(buzzer, LOW);
      buzzerState = 0;
    }else{
      digitalWrite(buzzer, HIGH);
      buzzerState = 1;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Servo sweeps back and forth continuously with 180 degrees range
  for (pos = 0; pos <= 180; pos ++){
    myServo.write(pos);
    measure();
    delay(10);
  }
  for (pos = 180; pos >= 0; pos --){
    myServo.write(pos);
    measure();

  }
}
