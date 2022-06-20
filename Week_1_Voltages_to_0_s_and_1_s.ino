/*******************************************************************************************************************************
 This is the Week 1 test script for running the light sensor only. It allows for students to work through the activity
 of how light is detected by the sensor and then turned into a voltage signal that then represents a particular value in
 in terms of a binary value conistsing of 0's and 1's. For information regarding the activity in conjunction with the script
 and the instructor notes, email judi@judisandrock.com.
 
 For questions regarding this script or the SDG STEM program, contact cody@maxiq.space For questions or troubleshooting info,
 contact dlee@mtsd.us
 
*******************************************************************************************************************************/
 
#include <SSD1306Ascii.h> //These libraries are for the generic OLED display screen attached
#include <SSD1306AsciiWire.h>  //These libraries are for the generic OLED display screen attached
#include <SSD1306init.h>  //These libraries are for the generic OLED display screen attached
#include <xOD01.h>  //These libraries are for the generic OLED display screen attached
#include <xCore.h>  //This library allows the ESP32 to function properly
#include <xVersion.h>  //This library tells the script how to work with the ESP32 chipset
#include <Wire.h>  //This library provides the pinreadouts
#include <LTR390.h>  //This library allows the light sensor to be used

#define OLED_I2C 0x3c  //This tells the ESP32 what kind of OLED screen is attached
#define I2C_ADDRESS 0x53  //This tells the ESP32 where the light sensor information is coming from

xOD01 OD01;

const int DELAY_TIME = 1000;
const int DELAY_TIME_LUX = 750;
 
LTR390 ltr390(I2C_ADDRESS);
  
void setup() {
   Serial.begin(115200);
  Wire.begin();
  OD01.begin();
  OD01.set2X();
  OD01.print("OD01 TEST");
  delay(DELAY_TIME);
  OD01.clear();
  
  if(!ltr390.init()){
    Serial.println("LTR390 not connected!");
  }

  ltr390.setMode(LTR390_MODE_ALS);

  ltr390.setGain(LTR390_GAIN_3);
  Serial.print("Gain : ");
  switch (ltr390.getGain()) {
    case LTR390_GAIN_1: Serial.println(1); break;
    case LTR390_GAIN_3: Serial.println(3); break;
    case LTR390_GAIN_6: Serial.println(6); break;
    case LTR390_GAIN_9: Serial.println(9); break;
    case LTR390_GAIN_18: Serial.println(18); break;
  }
  
  ltr390.setResolution(LTR390_RESOLUTION_18BIT);
  Serial.print("Resolution : ");
  switch (ltr390.getResolution()) {
    case LTR390_RESOLUTION_13BIT: Serial.println(13); break;
    case LTR390_RESOLUTION_16BIT: Serial.println(16); break;
    case LTR390_RESOLUTION_17BIT: Serial.println(17); break;
    case LTR390_RESOLUTION_18BIT: Serial.println(18); break;
    case LTR390_RESOLUTION_19BIT: Serial.println(19); break;
    case LTR390_RESOLUTION_20BIT: Serial.println(20); break;
  }

  //ltr390.setThresholds(100, 1000);
  //ltr390.configInterrupt(true, LTR390_MODE_UVS);

}

void loop() {

  OD01.set1X();
  
  if (ltr390.newDataAvailable()) {
      if (ltr390.getMode() == LTR390_MODE_ALS) {
         Serial.print("Ambient Light Lux: "); 
         Serial.println(ltr390.getLux());
         ltr390.setGain(LTR390_GAIN_18);                  //Recommended for UVI - x18
         ltr390.setResolution(LTR390_RESOLUTION_20BIT);   //Recommended for UVI - 20-bit
         ltr390.setMode(LTR390_MODE_UVS);             
      } else if (ltr390.getMode() == LTR390_MODE_UVS) {
         Serial.print("UV Index: "); 
         Serial.println(ltr390.readUVS());
         ltr390.setGain(LTR390_GAIN_3);                   //Recommended for Lux - x3
         ltr390.setResolution(LTR390_RESOLUTION_18BIT);   //Recommended for Lux - 18-bit
         ltr390.setMode(LTR390_MODE_ALS);

      }

  }

OD01.set2X();

 OD01.println("MAXIQ_SPACE");
 OD01.println("Week 1:");

OD01.set1X();
 OD01.println("Light (lux):");
 OD01.println(ltr390.getLux());
 OD01.print("UV Index: "); 
 OD01.println(ltr390.readUVS());

delay(DELAY_TIME_LUX);
OD01.clear();

}
