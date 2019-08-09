#define FAN 9

int soundPin = A0;
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
  if(sensorValue < 150)
  {
    analogWrite(FAN, 50);
  }
  if(sensorValue > 150)
  {
    analogWrite(FAN, 255);
    delay(2000);
  }
  
}
