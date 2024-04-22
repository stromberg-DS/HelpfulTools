/* 
 * Neopixel Basic Example (aka WS2812, WS2812B, WS2811)
 * Author: Daniel Stromberg
 * Date: 4/22/24
 **********************
 *  Neopixels Hookup
 *    LEDs  >   Photon 2
 *      -----------
 *    +5V   >   VUSB (or external power)
 *    GND  >   GND
 *    Din   >   D2 (MUST be D2 on Photon 2)
 * ********************
 * Must install neopixel library
 *  CTRL + SHIFT + P
 *  type "install," click on "Particle: Install Library"
 *  type "neopixel" and press enter
 *  neopixel library is installed
*/

// Include Particle Device OS APIs
#include "Particle.h"
#include <neopixel.h>   //Make sure to include neopixel library


SYSTEM_MODE(SEMI_AUTOMATIC);   
SYSTEM_THREAD(ENABLED);   //not really necessary, doesn't hurt

//Constants
const int LED_PIN = 2;
const int PIXEL_COUNT = 144;   //set to your number of pixels

//Variables
int brightness = 30;    //max is 255, usually that's too bright

//Create pixel object
//  Make sure to swap what kind you have (WS2812, WS2811, etc.)
Adafruit_NeoPixel pixel(PIXEL_COUNT, SPI1, WS2812B);  

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600);

  pixel.begin();
  pixel.setBrightness(brightness);
  pixel.clear();
  pixel.show();
  
  //Quick test of all LEDs to make sure the strip works. 
  for (int i=0; i < PIXEL_COUNT; i++){
    pixel.setPixelColor(i, 0xFF0000);   //Light up Red
    pixel.show();
    delay(20);
  }
  
  for (int j=0; j < PIXEL_COUNT; j++){
    pixel.setPixelColor(j, 0x00FF00);   //Light up green
    pixel.show();
    delay(20);
  }

  for (int k=0; k < PIXEL_COUNT; k++){
    pixel.setPixelColor(k, 0x000FF);    //Light up blue
    pixel.show();
    delay(20);
  }
  delay(1000);

  pixel.clear();
  pixel.show();

  //Normally don't include this
  delay(500); //wait half a second to slow down random fill. 
  
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
//To light up a pixel, you need 2 things:
//  pixel.setPixelColor(number_of_pixel, color_you_want);
//  pixel.show();

int randomPixelNumber;
int randomPixelColor;

randomPixelNumber = random(PIXEL_COUNT);  //pick a random number between 0 and total number of pixels
randomPixelColor = random(0xFFFFFF);      //pick a random color between 0x000000 and 0xFFFFFF

pixel.setPixelColor(randomPixelNumber, randomPixelColor);   //pick the pixel and set the color we want
pixel.show();    //actually update the LED strip by showing the new color

//NOTES:
//
//COLOR is a combination of Red, Green, and Blue in 1 hex value
//for 0x00FF44,
//  0x          *just tells the computer we are using a hex number
//  Red = 00    *There is no red
//  Green=FF    *Green is fully on
//  Blue=88     *Blue is halfway on
//
//
//pixel.show() is what actually updates the leds on the strip
//  usually, you don't need to call this very often.
//  You can do all your calculations, set all of your pixel colors
//  and at the very end, write pixel.show() to actually output your colors
//  pixel.show() is even necessary after using pixel.clear() to turn them all off.
}
