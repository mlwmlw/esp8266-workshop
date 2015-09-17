#include <ESP8266WiFi.h>
#include <aREST.h>

aREST rest = aREST();
const char* ssid = "TP-LINK";
const char* password = "1234567890";
#define LISTEN_PORT 80
WiFiServer server(LISTEN_PORT);
void setup() {
  Serial.begin(9600);
  rest.function("led", ledControl);
  rest.set_id("1");
  rest.set_name("esp8266");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

int ledControl(String command) {
  // Get state from command
  int state = command.toInt();
  Serial.println("LED = " + state);
  digitalWrite(5, state);
  return 1;
}
