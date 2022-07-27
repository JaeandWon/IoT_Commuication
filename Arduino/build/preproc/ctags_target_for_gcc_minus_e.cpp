# 1 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT_LED\\MQTT_LED.ino"
# 2 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT_LED\\MQTT_LED.ino" 2
# 3 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT_LED\\MQTT_LED.ino" 2

const char *ssid = "jwip"; // wifi name
const char *password = "01027628569"; // wifi pw
const char mqtt_server[] = "192.168.0.3"; // mqtt broker server
const char clientName[] = "010830Client"; // 다름 이름이랑 중복되지 않도록 함

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

int led = 14;
int timeln = 1000;

void setup_wifi();
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();

void setup()
{
    pinMode(led, 0x01);
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

    digitalWrite(led, 0x1);
    delay(timeln);
    digitalWrite(led, 0x0);
    delay(timeln);
}
//
//
//
//
//
void setup_wifi()
{
    delay(100);
    Serial.println("MQTT_LED");
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address:");
    Serial.println(WiFi.localIP());
}

//통신에서 문자가 들어오면 이 함수의 payload 배열에 저장된다.
void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.println("]");

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();

    /*payload로 들어온 문자를 정수로 바꾸기 위해 String inString에 저장 후

    tolnt() 함수를 사용해 정수로 바꾸어 timeln에 저장한다 */
# 86 "c:\\Users\\jaewo\\Desktop\\IoT_Commuication\\Arduino\\MQTT_LED\\MQTT_LED.ino"
    String inString = "";
    for (int i = 0; i < length; i++)
    {
        inString += (char)payload[i];
    }
    timeln = inString.toInt();
}

// mqtt 통신에 지속적으로 접속
void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        // Atempt to connect
        if (client.connect(clientName))
        {
            Serial.println("connected");
            // Once connectedm publish an announcement...
            client.publish("inTopic", "Reconnected");
            // and resubscribe
            client.subscribe("outTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}
