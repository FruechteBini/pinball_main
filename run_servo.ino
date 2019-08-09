// ____initialize Servo tool____
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int potpin = 0;  // analog pin used to connect the potentiometer
int valpin;    // variable to read the value from the analog pin
// ____initialize Servo tool____

// ____Servo tool function____
void runServo(int startAngle,int endAngle){
  valpin = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  valpin = map(valpin, 0, 1023, startAngle, endAngle);     // scale it to use it with the servo (value between startAngle and endAngle)
  myservo.write(valpin);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
// ____Servo tool function____

void setup() {
  // ____setup Servo tool____
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // ____setup Servo tool____
}

void loop() {
  runServo(0,50);
}
