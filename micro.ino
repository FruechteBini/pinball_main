/*
//dummy comment

#define FAN 9

int soundPin = A5;
int sensorValue = 0;
 
void setup ()
{
Serial.begin (9600);
pinMode(FAN, OUTPUT);
}
 
void loop ()
{
  
  sensorValue = analogRead (soundPin);
  Serial.println (sensorValue, DEC);
  analogWrite(FAN, 255);
  if(sensorValue > 150)
  {
    analogWrite(FAN, 50);
  }
  if(sensorValue > 150)
  {
    analogWrite(FAN, 255);
    tone(3, 1000, 1000);
    delay(2000);
  }
  
}
*/
