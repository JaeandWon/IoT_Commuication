#include <ESP8266WiFi.h>

const char wifi_id[] = "";
const char pw[] = "";

WiFiServer server(80);

void Wifi_Setup();

void setup()
{
    Serial.begin(9600);
    pinMode(4, OUTPUT);
}

void loop()
{
    Wifi_Setup();
    digitalWrite(4, HIGH);

    delay(10000);
}

void Wifi_Setup()
{
    Serial.println("WiFi disconnected");
    digitalWrite(4, HIGH);
    delay(300);
    digitalWrite(4, LOW);
    delay(300);
    digitalWrite(4, HIGH);
    delay(300);
    digitalWrite(4, LOW);

    delay(500);
    Serial.print("\n\nConnecting to ");
    Serial.print(wifi_id);

    WiFi.begin(wifi_id, pw);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("\n\nWiFi connected");
}
