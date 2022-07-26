#include <Arduino.h>
#line 1 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT\\mqtt.ino"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// Update these with values suitable for your network.
const char *ssid = "jwip";           //
const char *password = "01027628569"; // 00001245a

//?��?��?�� mosquitto server address, clientname
const char *mqtt_server = "192.168.0.3"; // ip  172.16.101.62
const char *clientName = "D1miniClientA";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

int value = 0;

#line 22 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT\\mqtt.ino"
void setup_wifi();
#line 49 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT\\mqtt.ino"
void callback(char *topic, byte *payload, unsigned int length);
#line 71 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT\\mqtt.ino"
void reconnect();
#line 96 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT\\mqtt.ino"
void setup();
#line 105 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT\\mqtt.ino"
void loop();
#line 22 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT\\mqtt.ino"
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
    delay(500);
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

