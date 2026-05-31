#include <Arduino.h>
#include <WiFiS3.h>
#include <ArduinoHttpClient.h>
#include "credentials.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* token = BOT_TOKEN;
const char* chatId = CHAT_ID;

const int sensorPin = A0;
const int threshold = 2000;
bool alertSent = false;

void sendTelegram(String message) {
  WiFiSSLClient wifi;
  HttpClient client = HttpClient(wifi, "api.telegram.org", 443);

  String path = "/bot" + String(token) + "/sendMessage";
  String body = "chat_id=" + String(chatId) + "&text=" + message;

  client.post(path, "application/x-www-form-urlencoded", body);

  Serial.println(client.responseStatusCode());
  Serial.println(client.responseBody());
}

void setup() {
  Serial.begin(9600);
  delay(3000);
  analogReadResolution(12);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED || WiFi.localIP() == IPAddress(0,0,0,0)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  // Serial.println(sensorValue);

  if (sensorValue < threshold && !alertSent) {
    sendTelegram("ALERT!!");
    alertSent = true;
  } else if (sensorValue >= threshold) {
    alertSent = false;
  }
}