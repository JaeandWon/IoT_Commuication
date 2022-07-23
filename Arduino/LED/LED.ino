/*
WIFI를 이용한 LED 제어
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char ssid[] = "jwip";
const char pw[] = "01027628569";

ESP8266WebServer server(80);

const int led = 14;
String s, s_head;

void handleRoot();
void handleNotFound();
void setupWifi();

void setup()
{
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    Serial.begin(115200);

    setupWifi();

    // 스마트폰에 맟게 크기 조정, html에서 한글 출력하게 설정
    s_head = "<meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
    // s=s+"<meta http-equiv='refresh' content='5'/>";
    s_head = s_head + "<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />";

    server.on("/", handleRoot); // /이입력되면 handleRoot 함수 실행
    server.on("/inline", []()
              {
        digitalWrite(led, LOW);
        s = s_head+"<h1>꺼짐</h1><br>"; 
        server.send(200, "text/html", s); }); // 200 == 성공, text/html형식으로 s를 전달

    server.onNotFound(handleNotFound); //존재하지 않는 주소로 접속하였을 때 handleNotFound를 요청

    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    server.handleClient();
}

void setupWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pw);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void handleRoot()
{
    digitalWrite(led, HIGH);
    s = s_head + "<h1>켜짐</h1><br>";
    server.send(200, "text/html", s);
}
void handleNotFound()
{
    digitalWrite(led, 1);
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
    digitalWrite(led, 0);
}
