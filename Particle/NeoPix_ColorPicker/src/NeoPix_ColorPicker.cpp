/* 
 * Neopixel Color Picker - get hex codes for color combos
 * Author: Daniel Stromberg
 * Date: 8/23/24
*/

#include "Particle.h"
#include <neopixel.h>
#include "Button.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

const int PIXEL_COUNT = 2000;
const int BUTTON_PIN = D10;
const int RED_POT_PIN = A5;
const int GREEN_POT_PIN = A0;
const int BLUE_POT_PIN = A1;
const int MAX_BRIGHTNESS = 150;

int colorSplit1 = 40;
int colorSplit2 = 100;
int redVal = 0;
int greenVal = 0;
int blueVal = 0;
int rgbVal = 0;

int potMode = 0;
int currentColor = 0;

unsigned int currentMillis;
int lastMillis = -9999;

Adafruit_NeoPixel pixel(PIXEL_COUNT, SPI1, WS2812);
Button modeSwitch(BUTTON_PIN);

void setup() {
  // Serial.begin(9600);
  // while(!Serial.isConnected()){
  //   //wait....
  // }
  // Serial.printf("Serial Connected!\n\n");
  pixel.begin();
  pixel.setBrightness(MAX_BRIGHTNESS);

    for(int i=0; i<PIXEL_COUNT; i++){
        pixel.setPixelColor(i, 0x00FF00);
        pixel.show();
        // Serial.printf("Lighting LED #%i\n", i);
    }
    
    delay(2000);
    pixel.clear();
    pixel.show();
}

void loop() {
  int redPotReading;
  int greenPotReading;
  int bluePotReading;

  currentMillis = millis();
  int timeSincePrint = currentMillis - lastMillis;

  // pixel.clear();

  redPotReading = analogRead(RED_POT_PIN);
  // redVal = map(redPotReading, 0, 4096, 0, 255);
  greenPotReading = analogRead(GREEN_POT_PIN);
  // greenVal = map(greenPotReading, 0, 4096, 0, 255);
  bluePotReading = analogRead(BLUE_POT_PIN);
  // blueVal = map(bluePotReading, 0, 4096, 0, 255);

  if(modeSwitch.isClicked()){
    currentColor++;
    if(currentColor >2){
      currentColor = 0;
    }
    // Serial.printf("Colormode: %i\n\n", currentColor);
    delay(50);  //delay for a bit of debouncing.
  }

// if there is only one pot
  if(currentColor == 0){
    redVal = map(redPotReading, 0, 4096, 0, 255);
  }else if (currentColor == 1){
    greenVal = map(redPotReading, 0, 4096, 0, 255);
  } else{
    blueVal = map(redPotReading, 0, 4096, 0, 255);
  }

  rgbVal = (redVal<<16) | (greenVal<<8) | blueVal;
  
  for(int i=0; i<PIXEL_COUNT; i++){
    pixel.setPixelColor(i, rgbVal);
  }
  pixel.show();


  if(timeSincePrint > 1000){  
    // Serial.printf("rgbVal: %06X\n\n", rgbVal);
    lastMillis = currentMillis;
  }
}
