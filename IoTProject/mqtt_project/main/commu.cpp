#include "commu.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>


void setup_wifi(char *ssid, char* pw)
{
    delay(100);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pw);

    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("Local Ip: ");
    Serial.println(WiFi.localIP());

}