#include <ESP8266WiFi.h> // wifi연결
#include <PubSubClient.h> // mqtt pub, sub 구동
#include "DHTesp.h" 

const char *ssid = "";
const char *password = "";
const char *mqtt_server = "";
const char *clientName = "010830Client";

DHTesp dht;
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();
void callback(char *topic, byte* payload, unsigned int uLen);
void reconnect();

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

    float hum = dht.getHumidity();
    float tmp = dht.getTemperature();
    char message[64] = "", pTmpBuf[50], pHumBuf[50];
    dtostrf(tmp, 5, 2, pTmpBuf);
    dtostrf(hum, 5, 2, pHumBuf);

    sprintf(message, "{\"tmp\":%s,\"hum\":%s}", pTmpBuf, pHumBuf); // message에다가 json형식인 tep, hum을 copy
    Serial.print("Publish message: ");
    Serial.println(message);
    client.publish("dht11", message); // dht11이라는 토픽으로 message를 전송 

    delay(3000);
}
//
//
//
//
//
void setup_wifi()
{
    delay(100);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    dht.setup(D4, DHTesp::DHT11);
    }

void callback(char *topic, byte* payload, unsigned int uLen)
{
    char pBuffer[uLen + 1]; // 문자열의 끝을 의미하는 null값을 위해 들어오는 길이보다 1크게 할당
    int i;
    for (i = 0; i < uLen; i++)
    {
        pBuffer[i] = payload[i];
    }

    pBuffer[i] = '\0';
    Serial.println(pBuffer);

    if(pBuffer[0] == '1')
        digitalWrite(14, HIGH);
    else if (pBuffer[0] == '2')
        digitalWrite(14, LOW);
}

void reconnect()
{
    while(!client.connected())
    {
        Serial.print("Ateempting MQTT connection...");

        if(client.connect(clientName))
        {
            Serial.println("connected");
            client.subscribe("led"); // led라는 mqtt server에서 데이터를 읽음 
        }
        else
        {
            Serial.print("failed, rc =");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds"); 
            delay(5000);   
        }  
    }
}
