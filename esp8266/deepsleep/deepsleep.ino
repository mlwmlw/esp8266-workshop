#include "ESP8266WiFi.h"
void setup() {
  Serial.begin(9600);
  delay(10000);
}

void loop() {
  Serial.println("sleep");
  ESP.deepSleep(1000000 * 10);
}
