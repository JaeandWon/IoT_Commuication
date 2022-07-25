# IoT_Commuication

## Goal
Studied basic concept of mqtt protocol in order to utilize it into IoT project later 

## Tech stack
* Node Js
* Arduino
* MongoDB
* MQTT
* Andriod Studio 

## URL

[URL][url]

[url]: https://www.inflearn.com/course/%EC%82%AC%EB%AC%BC%EC%9D%B8%ED%84%B0%EB%84%B7-%ED%86%B5%EC%8B%A0/dashboard
---

## Mqtt connection refused
2022 07. 20: Found out mqtt connection problem 


```C
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
const char *ssid = ""; // wifi id 
const char *password = ""; // wifi pw 

// mosquitto server address, clientname
const char *mqtt_server = ""; // write your ip, you may find your own ip by command "ipconfig" on cmd
const char *clientName = "D1miniClientA";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

int value = 0;

void setup_wifi()
{
    delay(1000);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Check the WiFi connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1')
    {
        digitalWrite(14, HIGH);
    }
    else
    {
        digitalWrite(14, LOW);
    }
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(clientName))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("outTopic", "hello world");
            // ... and resubscribe
            client.subscribe("inTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
///////////////////////////////////////////////////////////////////////
void setup()
{
    pinMode(14, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000)
    {
        lastMsg = now;
        ++value;
        snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("outTopic", msg);
    }
}
```
```