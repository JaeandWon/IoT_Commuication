#include "commu.h"

#define LED 14

const char *ssid = "";
const char *pw = "";

void setup()
{
    Serial.begin(115200);
    setup_wifi(ssid, pw);
}

void loop()
{

}