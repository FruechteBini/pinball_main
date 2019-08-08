    #include <Adafruit_NeoPixel.h>
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <time.h>
  
    // Which pin on the Arduino is connected to the NeoPixels?
    // On a Trinket or Gemma we suggest changing this to 1:
    #define PIN 6
     
    // How many NeoPixels are attached to the Arduino?
    #define N_LEDS 60
    int rand_score = 0;
     
    // Declare our NeoPixel strip object:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
    // Argument 1 = Number of pixels in NeoPixel strip
    // Argument 2 = Arduino pin number (most are valid)
    // Argument 3 = Pixel type flags, add together as needed:
    //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
    //   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

    void setup() {
      srand(time(NULL));
      strip.begin();      
    }

  
    void loop(){
      strip.clear();
      rand_score = rand()%(10-1)+1;
      setScore(rand_score);
    }
    
    void setScore(int score)
    {
      for(int i=0; i<score; i++)
      {
        strip.setPixelColor(i, 255, 0, 255);
        strip.show();
      }     
      delay(500);
    }
