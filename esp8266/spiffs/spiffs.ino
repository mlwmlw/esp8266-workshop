#include "FS.h"

bool loadConfig() {
  File file = SPIFFS.open("/config.txt", "r");
  if(file) {
    Serial.println("file exists: ");
    Serial.println(file.readStringUntil('\n'));
    return true;
  }
  return false;
}

bool saveConfig(String input) {
  File file = SPIFFS.open("/config.txt", "w");
  if (!file) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  file.println(input);
  return true;
}

void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("Mounting FS...");

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  if (!loadConfig()) {
    Serial.println("Failed to load config");
  } 
}
String input = "";
void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    input += c;
    if (c == '\n') {
      Serial.println(input);
      if(saveConfig(input)) {
        Serial.println("writing config ");
      }
      input = "";

    }
  }
}
