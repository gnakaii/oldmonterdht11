/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);


#define OLED_RESET 3
Adafruit_SSD1306 display(OLED_RESET);
#include <Vnh2sp30.h>

//              ENA A   B   PWM   CS    inv
Vnh2sp30  mtrL( A0, 7,  8,  5,    A2,   0);             // Left side straight
Vnh2sp30  mtrR( A1, 4,  9,  6,    A3,   1);             // Right side reversed
boolean running = false;
boolean wait = false;



#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  }


void loop() {  
  display.display(); //I love Adafruit :D
  delay(1000);
  
  display.clearDisplay();   // Clear the buffer.

  float h = dht.readHumidity();  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) { // Check if any reads failed and exit early (to try again).
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t\n");
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("tmp");
  display.setCursor(40,0);
  display.println((int)t);
  display.setTextSize(1);
  display.setCursor(70,0);
  display.println("o");
  display.setTextSize(2);
  display.setCursor(80,0);
  display.println("C");
  display.setCursor(100,0);
display.println(running);
  display.setTextSize(2);
  display.setCursor(0,18);
  display.println("ham%");
  display.setCursor(70,18);
  display.println((int)h);
 display.setCursor(100,18);
display.println(wait);
  display.display();
  delay(1000);
//  display.clearDisplay();
  // LEDを点灯 ( HIGHは電圧レベル )
   // LEDを点灯 ( HIGHは電圧レベル )
  if (t >= 35 && running == 0) {
    mtrL.run(1023);                      // Full speed forward
    delay(240000UL);
    mtrL.stop();
    delay(3000);
  }
   if (t >= 35 && running == 0) {
    mtrR.run(1023);
    delay(240000UL);
    mtrR.stop();
    running = !running;
    delay(3000);
  }

  if (t >= 39 && wait == 0) {
    mtrL.run(1023);                      // Full speed forward
    delay(240000UL);
    mtrL.stop();
    delay(3000);
  }
  if (t >= 39 && wait == 0) {
    mtrR.run(1023);
    delay(240000UL);
    mtrR.stop();
    wait = !wait;
    delay(3000); 
  }

  if (t < 37 && wait == 1) {

    mtrR.run(-600);
    delay(240000UL);
    mtrR.stop();
    delay(3000);
  }
   if (t < 37 && wait == 1) {
    mtrL.run(-600);                      // Full speed forward
    delay(240000UL);
    mtrL.stop();
    wait = !wait;
    delay(3000);
  }

  if (t < 33 && running == 1) {
    mtrR.run(-600);
    delay(240000UL);
    mtrR.stop();
    delay(3000);
  }
 if (t < 33 && running == 1) { 
    mtrL.run(-600);                      // Full speed forward
    delay(240000UL);
    mtrL.stop();
    running = !running;
    delay(3000);

  }

}



