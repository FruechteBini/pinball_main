    #include <Adafruit_NeoPixel.h>
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <time.h>
  
    // Which pin on the Arduino is connected to the NeoPixels?
    // On a Trinket or Gemma we suggest changing this to 1:
    #define PIN 6 //LED PIN
     
    // How many NeoPixels are attached to the Arduino?
    #define N_LEDS 60
    int score = 0;

    int isObstaclePin = 7; // This is our input pin
    int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE
     
    // Declare our NeoPixel strip object:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

    void setup() {
      srand(time(NULL));
      strip.begin();
      strip.clear();
      strip.show();
      pinMode(isObstaclePin, INPUT);
      Serial.begin(9600);   
    }

  
    void loop(){
      isObstacle = digitalRead(isObstaclePin);
      if (isObstacle == LOW) {
        Serial.println("OBSTACLE!!, OBSTACLE!!");
        score = score + 1;
        setScore(score);
      }
    }
    
    void setScore(int score)
    {
      for(int i=0; i<score; i++)
      {
        strip.setPixelColor(i, 255, 0, 0);
        strip.show();
      }     
      delay(500);
  }
