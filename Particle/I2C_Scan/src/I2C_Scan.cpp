/* 
 * I2C Scan - courtesy of Brian Rashan & CNM IoT Bootcamp
 * Author: Brian Rashap
 * Date: 
 */

#include "Particle.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

byte status, address, nDevices;


void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 10000);
  delay(500);
  Wire.begin();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  nDevices = 0;
  for (address=0; address<128; address++){
    Wire.beginTransmission(address);
    status = Wire.endTransmission();
    if(status==0){
      nDevices++;
      Serial.printf("I2C device found at address 0x%02X (%i)\n", address, address);
    }
  }
  Serial.printf("%i devices found.\n", nDevices);
  delay(5000);
}
