//Unicorn HAT HD Test

#include <SPI.h>
#include <FastLED.h>

//Unicorn stuff
const int _SOF = 0x72;
SPISettings unicornhd(12000000, MSBFIRST, SPI_MODE0); 

//FastLED stuff
#define NUM_LEDS 256
CRGB leds[NUM_LEDS];

//matrix and anim stuff
const int w = 16;
const int h = 16;
int f = 0;

void setup() {
  
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  
  SPI.begin();

  clearLEDs();

}

void loop() {

  //200us
  for (int i = 0; i < 256; i++) {
    leds[i] = CHSV(i+f, 255, 255);
  }
  
  //860us
  outputLEDs();

  f++;
  delay(10);

}

void setPixelRGB(int x, int y, CRGB col) {
  leds[x+y*w] = col;
}

void setPixelHSV(int x, int y, CHSV col) {
  leds[x+y*w] = col;
}

CRGB getPixelRGB(int x, int y) {
  return leds[x+y*w];
}

int getPixel(int x, int y) {
  return x+y*w;
}

void outputLEDs() {

  SPI.beginTransaction(unicornhd);
  
    digitalWriteFast(10, LOW);
  
    SPI.transfer(_SOF);
  
    for (int i = 0; i < 256; i++) {
      SPI.transfer(leds[i][0]);
      SPI.transfer(leds[i][1]);
      SPI.transfer(leds[i][2]);   
    }
  
    digitalWriteFast(10, HIGH);

  SPI.endTransaction();


}

void clearLEDs() {
  
  digitalWrite(10, LOW);

  SPI.transfer(_SOF);

  for (int i = 0; i < 768; i++) {
    SPI.transfer(0);
  }

  digitalWrite(10, HIGH);

}
