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
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

wl_status_t prevWifiStatus = WL_IDLE_STATUS;
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DHTTYPE DHT11
#define DHTPIN D2

DHT dht(DHTPIN, DHTTYPE);
int leftP   = 11;
int rightP  = 12;
//t nRainDigitalIn = 13;
//#define RELAY_ON  LOW
//#define RELAY_OFF HIGH

//#define CCW    LOW
//#define CW     HIGH

//#define BRAKE  HIGH
//#define RUN    LOW

//int RELAY1 = 7;
//int RELAY2 = 6;
LiquidCrystal_I2C lcd(0x3F, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define OLED_RESET 3
Adafruit_SSD1306 display(OLED_RESET);
//#include <Vnh2sp30.h>

//              ENA A   B   PWM   CS    inv
//V//nh2sp30  mtrL( A0, 7,  8,  5,    A2,   0);
//V//nh2sp30  mtrR( A1, 4,  9,  6,    A3,   1);
boolean running = false;
boolean wait = false;

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

void setup()   {
 Serial.begin(9600);  // 起動時に合わせて74880bpsにする
  delay(10);

  wifiMulti.addAP("0024A5B5A70A", "kkvkbs07ds9fh");
  wifiMulti.addAP("TP-Link_E11B", "01707359");
wifiMulti.addAP("Buffalo-G-D010","7untkcyrj333y");

  Serial.println("");
  Serial.println("boot");
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();

  lcd.init();
  lcd.init();
  // Print a message to the LCD.
 pinMode(leftP, OUTPUT);
  pinMode(rightP, OUTPUT);
  //digitalWrite(RELAY1, RELAY_OFF);
 // digitalWrite(RELAY2, RELAY_OFF);

  //pinMode(RELAY1, OUTPUT);
  //pinMode(RELAY2, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
}

void loop() {
wl_status_t wifiStatus = wifiMulti.run();
  if ( prevWifiStatus != wifiStatus ) {
    prevWifiStatus = wifiStatus;
    if ( wifiStatus == WL_CONNECTED) {
      Serial.println("WiFi connected");
      Serial.println("SSID: ");
      Serial.println(WiFi.SSID());
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    }
    else {
      // ステータス毎にメッセージ変えたほうがいいかも（各自宿題）
      Serial.println("WiFi error?");
      Serial.println(wifiStatus);
    }
  }

  display.display();
  delay(1000);

  display.clearDisplay();   // Clear the buffer.

  float h = dht.readHumidity();  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {

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
  display.setCursor(0, 0);
  display.println("tmp");
  display.setCursor(40, 0);
  display.println((int)t);
  display.setTextSize(1);
  display.setCursor(70, 0);
  display.println("o");
  display.setTextSize(2);
  display.setCursor(80, 0);
  display.println("C");
  display.setCursor(100, 0);
  display.println(running);
  display.setTextSize(2);
  display.setCursor(0, 18);
  display.println("ham%");
  display.setCursor(70, 18);
  display.println((int)h);
  display.setCursor(100, 18);
  display.println(wait);
  display.display();
  delay(1000);

 // if (t >= 1 && running == 0) {
 //   digitalWrite(RELAY1, CW  );
  //  digitalWrite(RELAY2, RUN );
 //   delay(3000);

  //  digitalWrite(RELAY1, CW  );
  //  digitalWrite(RELAY2, BRAKE);
  //  running = !running;
  //  delay(3000);
 // }
  //gitalWrite(RELAY1, CW  );
  //igitalWrite(RELAY2, RUN );
  // delay(1000);
  //mtrL.run(1023);
  // delay(240000UL);
  //  mtrL.stop();
  //  delay(1000);
  // mtrR.run(1023);
  //  delay(24000UL);
  // mtrR.stop();
  // running = !running;
  //  delay(1000);
 // if (t < 4 && running == 1) {
  //  digitalWrite(RELAY1, CW  );
   // digitalWrite(RELAY2, RUN );
  //  delay(3000);

 //   digitalWrite(RELAY1, CW  );
 //   digitalWrite(RELAY2, BRAKE);
 //   running = !running;
  //  delay(3000);



  }
