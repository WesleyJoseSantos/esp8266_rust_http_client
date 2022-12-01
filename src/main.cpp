#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define CONFIG_WIFI_SSID "CABO CANAVERAL 4"
#define CONFIG_WIFI_PASS "16192020"
#define CONFIG_SERVER_URI "http://192.168.27.182:7878"
#define CONFIG_PIN_LED D4

#define MSG_LED_ON "on"
#define MSG_LED_OFF "off"
#define MSG_LED_BLINK "blink"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74400);
  WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);
  pinMode(CONFIG_PIN_LED, OUTPUT);
  digitalWrite(CONFIG_PIN_LED, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.isConnected())
  {
    WiFiClient wifiClient;
    HTTPClient httpClient;

    httpClient.begin(wifiClient, CONFIG_SERVER_URI);
    httpClient.GET();
     
    String result = httpClient.getString();
    Serial.printf("Msg received: %s\n", result.c_str());

    if(result == MSG_LED_ON)
    {
      digitalWrite(CONFIG_PIN_LED, LOW);
    }

    if(result == MSG_LED_OFF)
    {
      digitalWrite(CONFIG_PIN_LED, HIGH);
    }

    if(result == MSG_LED_BLINK)
    {
      digitalWrite(CONFIG_PIN_LED, !digitalRead(CONFIG_PIN_LED));
    }

    delay(500);
  }
}