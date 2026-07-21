#include <LiquidCrystal.h>
#include <SR04.h>
#include <Servo.h>

// Create variable so can wait by getting current time and not using delays

unsigned long lastBeep = 0;
int beepInterval;

unsigned long lastMove = 0;
int moveInterval = 10;

unsigned long lastButtonCheck = 0;
int buttonCheckInterval = 150;

Servo myServo;
int angle = 0;
int dir = -1;

int buzzer = 10;
int buzzerState = 0;

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

LiquidCrystal lcd(13, 8, A2, A3, A4, A5);

int threshold;

bool detected;

void setScreen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("State: ");
  if (setting == 0){
    lcd.print("Unarmed");
  }else{
    lcd.print("Armed");
  }
  lcd.setCursor(0, 1);
  lcd.print("Threshold: ");
  lcd.print(threshold);
  lcd.print("cm");
}

void measure(){
  if (millis() - lastButtonCheck >= buttonCheckInterval){
    lastButtonCheck = millis();
    if (digitalRead(button) == LOW){
      setting = 1 - setting;
    }
  }
  a = sr04.Distance();
  threshold = map(analogRead(pot), 0, 1023, 5, 60);
  setScreen();
  if (setting == 1){
    if (a <= threshold){
      beepInterval = map(a, 0, threshold, 1, 500);
      alarm();
    }else{
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      digitalWrite(buzzer, LOW);
      buzzerState = 0;
      detected = false;
    }

  }else{
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(buzzer, LOW);
    buzzerState = 0;
    detected = false;
  }
}

void alarm(){
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, LOW);
  detected = true;

  if (millis() - lastBeep >= beepInterval){
    lastBeep = millis();
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
  Serial.begin(9600);
  while (!Serial); // Waits for serial port to connect

  myServo.attach(9);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  lcd.begin(16, 2);
  setScreen();
}

void loop() {
  // put your main code here, to run repeatedly:

  // Run all hardware functions
  if (millis() - lastMove >= moveInterval){
    lastMove = millis();
    myServo.write(angle);
    measure();
    if (angle <= 0 || angle >= 180){
      dir *= -1;
    }
    angle += dir;

    // Send data to python
    Serial.print(angle);
    Serial.print(",");
    Serial.print(a);
    Serial.print(",");
    Serial.print(detected);
    Serial.print("\n");
    Serial.flush();
  }
}
