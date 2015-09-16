#include <SoftwareSerial.h>
#include "ESP8266.h"

#define SSID        "TP-LINK"
#define PASSWORD    "1234567890"

SoftwareSerial mySerial(3, 2);
ESP8266 wifi(mySerial);


void setup(void)
{
    Serial.begin(9600);
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    }
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");
        Serial.println(wifi.getLocalIP().c_str());    
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }
    
    if (wifi.startTCPServer(80)) {
        Serial.print("start tcp server ok\r\n");
    } else {
        Serial.print("start tcp server err\r\n");
    }
    
    if (wifi.setTCPServerTimeout(10)) { 
        Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
    }
    
    Serial.print("setup end\r\n");
}
 
void loop(void)
{
    uint8_t buffer[128] = {0};
    uint8_t mux_id;
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Received from :");
        Serial.print(mux_id);
        Serial.print("[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
        
        uint8_t header[] = "HTTP/1.1 200 OK\r\n"
        "Content-Length: 24\r\n"
        "Server: ESP8266\r\n"
        "Content-Type: text/html\r\n"
        "Connection: keep-alive\r\n\r\n";
        uint8_t hello[] = "<h1>Hello ESP8266!!</h1>";
        wifi.send(mux_id, header, sizeof(header));
        wifi.send(mux_id, hello, sizeof(hello));
       
        if (wifi.releaseTCP(mux_id)) {
            Serial.print("release tcp ");
            Serial.print(mux_id);
            Serial.println(" ok");
        } else {
            Serial.print("release tcp");
            Serial.print(mux_id);
            Serial.println(" err");
        }
        
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
    }
}

