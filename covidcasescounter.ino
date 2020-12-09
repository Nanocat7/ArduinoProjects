#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>


#define SCREEN_HEIGHT  32;
#define SCREEN_WIDTH 128;
#define OLED_RESET = -1;

Adafruit_SSD1306 display(128, 32, &Wire, -1);
//SoftwareSerial Wifi(0, 1);

const char* ssid = "Prettyboy";
const char* pass = "1827052300";
WiFiClient client;

const char* host = "api.thingspeak.com";
const int httpPortRead = 80;
const char* url = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=5S9GSSSI2M94NXT2";
const char* url2 = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=S6WZLRT2C6IEYP2L";
const char* url3 = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=TJLBLR0GNBNCU867";
HTTPClient http;

Servo myServo;

void setup() {
  // put your setup code here, to run once:
//  Wifi.begin(9600);
  Serial.begin(9600);
  display.display();
  myServo.attach(9);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  if (WiFi.status() == WL_CONNECTED) {
    display.setCursor(50, 7);
    display.println(F("WiFi is Connected"));
  }
  else {
    display.setCursor(50, 7);
    display.println(F("WiFi is coneecting..."));
  }
  myServo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (http.begin(host, httpPortRead, url)) {
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = http.getString();
        Serial.print("Confirmed Cases: ");
        Serial.println(payload);
        display.setCursor(0, 10);
        display.println("Cases:");
        display.setCursor(90, 10);
        display.println(payload);
      }
    }
  }
  if (http.begin(host, httpPortRead, url2))
  {
    int httpCode = http.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = http.getString();
        Serial.print("Recovered: ");
        Serial.println(payload);
        display.setCursor(0, 20);
        display.println("Recovered:");
        display.setCursor(90, 20);
        display.println(payload);
      }
    }
  }
  if ( http.begin(host, httpPortRead, url3)) {
    int httpCode = http.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = http.getString();
        Serial.print("Deaths: ");
        Serial.println(payload);
        display.setCursor(0, 54);
        display.println("Deaths:");
        display.setCursor(90, 54);
        display.println(payload);
        display.display();
      }
    }
  }
  
}
