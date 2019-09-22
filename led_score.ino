    #include <Adafruit_NeoPixel.h>
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <time.h>
  
    //Define LED Pins:
    #define LED_PIN 8 //LED PIN
    #define UP_LED_PIN 12 //LED PIN 2


    //Define Fans:
    #define FAN_START 3
    #define FAN_DOWN 5
    #define FAN_LEFT 11
    #define FAN_RIGHT 6
    
    // How many NeoPixels are attached to the Arduino?
    #define N_LEDS 25

    // ____initialize Servo tool____
    #include <Servo.h>
    Servo myservo;  // create servo object to control a servo
    int potpin = 0;  // analog pin used to connect the potentiometer
    int valpin;    // variable to read the value from the analog pin

    
    int currentMillis = 0;
    int oldMillisLeft = 0;
    int oldMillisRight = 0;


//------------------------------------------------------------------------------
    int fanVersion = 1;

//------------------------------------------------------------------------------    
    int score = 0;

    //Define Lichtschranken:
    int badSensorPin = 2; 
    int leftSensorPin = 4;
    int upSensorPin = 10;
   
    int badSensor = HIGH;
    int leftSensor = HIGH;
    int upSensor = HIGH;

    //micro sensors:
    int micLeft_pin = A5;
    int micRight_pin = A4;
    
    int sensorValueLeft = 0;
    int sensorValueRight = 0;
    
     
    // Declare our NeoPixel strip object:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel strip_up = Adafruit_NeoPixel(N_LEDS, UP_LED_PIN, NEO_GRB + NEO_KHZ800);

    void setup() {

      //Set up Strip 1:
      strip.begin();
      strip.clear();
      strip.show();

      //Set up Strip 2:
      strip_up.begin();
      strip_up.clear();
      strip_up.show();

      myservo.attach(9);  // attaches the servo on pin 9 to the servo object
      
      pinMode(badSensorPin, INPUT);
      pinMode(leftSensorPin, INPUT);
      pinMode(upSensorPin, INPUT);
      
      Serial.begin(9600);
    }

  
    void loop(){
      //run the servo:
      runServo(0,50);
      
      //Serial.print(sensorValue);
      currentMillis = millis();
      sensorValueLeft = analogRead(micLeft_pin);
      sensorValueRight = analogRead(micRight_pin);

      updateLeftFan();
      updateRightFan();
      analogWrite(FAN_DOWN, 100);
      analogWrite(FAN_START, 255);
      //analogWrite(FAN_RIGHT, 255);
      
      int badSensor = digitalRead(badSensorPin);
      int leftSensor = digitalRead(leftSensorPin);
      int upSensor = digitalRead(upSensorPin);

      if(upSensor == LOW && fanVersion==0){
        Serial.println("Sensor up!\n");
        score = score + 2;
        setScore(score, 0);
      }

      if(leftSensor == LOW&&fanVersion==0){
        Serial.println("Sensor left!\n");
        score = score + 3;
        setScore(score, 0);
      }
      //Check if badObstacle was triggered:
      if (badSensor == LOW&&fanVersion==0) {
        Serial.println("Bad Sensor!\n");
        if(score == 0){
          //setScore(score, 1);
          strip.clear();
          return;
        }
        score = score - 1;
        Serial.println(score);
        Serial.println("COLORWIPE\n");
        setScore(score, 1);
        colorWipe(strip.Color(  255, 0,   0), 10);
        strip.clear();

      }
      
    }

    void updateLeftFan()
    {
      //Serial.println(sensorValue);
      if (sensorValueLeft > 150)
      {
        oldMillisLeft = millis();
        delay(20);
      }
      if ((millis()-oldMillisLeft)<2000)
      {
        //Serial.println("FAST LEFT\n");
        analogWrite(FAN_LEFT, 255);
        return;
      }
        analogWrite(FAN_LEFT, 0);
      
    }

    void updateRightFan()
    {
      Serial.println(sensorValueRight);
      //Serial.println(sensorValue);
      if (sensorValueRight > 150)
      {
        oldMillisRight = millis();
        delay(20);
      }
      if ((millis()-oldMillisRight)<2000)
      {
        //Serial.println("FAST RIGHT\n");
        analogWrite(FAN_RIGHT, 255);
        return;
      }
        analogWrite(FAN_RIGHT, 0);
      
    }
    
    void setScore(int theScore, int badSensor)
    {
      strip_up.clear();
      if(theScore == 24){
        theaterChaseRainbow(50);
        strip_up.clear();
        score=0;
        return;
      }
      for(int i=0; i<theScore; i++)
      {
        strip_up.setPixelColor(i, 0, 255, 0);
        strip_up.show();
        //tone(3, 1000, 1000);
      }   
      if(badSensor == 0){
          delay(700);
      }
      
  }


  void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip_up.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip_up.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip_up.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<=strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
  strip.clear();
}

void runServo(int startAngle,int endAngle){
  valpin = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  valpin = map(valpin, 0, 1023, startAngle, endAngle);     // scale it to use it with the servo (value between startAngle and endAngle)
  myservo.write(valpin);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
