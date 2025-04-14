#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
Servo servo1, servo2;

const int buttonPin = 13;
bool currentServo = false; // false = servo1, true = servo2
bool lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  servo1.attach(A1);
  servo2.attach(A2);

  lcd.begin(16, 2);
  lcd.print("Servo 1 is Active");
}

void loop() {
  bool reading = digitalRead(buttonPin);
  int k=analogRead(A0); //k reads the analog value from the potentiometer
  int angle=map(k,0,1023,0,180);   //k used for angle 0to180

  // Detect button press 
  if (lastState == HIGH && reading == LOW) {
    currentServo = !currentServo;  // change the servo
    lcd.clear();
    lcd.print(currentServo ? "Servo 2 Active" : "Servo 1 Active");
  }

  lastState = reading;
  lcd.setCursor(0,1); // cursor set to second row
  lcd.print("Angle:");
  lcd.print(angle);

  // Move only the active servo
  if (currentServo) {
    servo1.write(0);
    servo2.write(angle);
  } else {
    servo1.write(angle);
    servo2.write(0);
  }

  delay(50);
}
