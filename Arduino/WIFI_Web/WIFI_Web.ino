/*
WIFI 연결 및 웹서버 구축 Exmaple
*/
#include <ESP8266WiFi.h>

const char ssid[] = "jwip";            //와이파이 이름
const char password[] = "01027628569"; //와이파이 비밀번호

WiFiServer server(80); // ESP8266.h에는 WiFiServer라는 객체가 있음, 객체를 생성하는 코드 80포트를 open

void setup()
{
    Serial.begin(9600); //디버깅용 시리얼 통신
    delay(1000);

    Serial.print("\n\nConnecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); // wifi 연결 시도

    while (WiFi.status() != WL_CONNECTED) //연결될 때 까지 계속 실행, WiFi.status는 연결시 WL_CONNECTED를 return
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");

    server.begin(); //서버 실행
    Serial.println("Server started");

    Serial.println(WiFi.localIP()); // WiFi.localIP(): 실드의 IP 주소를 리턴
}

void loop()
{
    WiFiClient client = server.available(); //클라이언트 접속이 들어오는지 체크

    if (!client) // client가 데이터를 보낼때까지 기다림
    {
        return;
    }

    Serial.println("new client");

    String req = client.readStringUntil('\n'); //엔터를 칠때까지의(\n이 입력될때까지) url 정보(http://~) req에 저장
    Serial.println(req);                       //어떤 요청인지 출력 ex) GET, POST..
    client.flush();                            //초기화

    String s = "<html>";                                                               // html tag를 string으로 생성
    s = s + "<meta name='viewport' content='width=device-width, initial-scale=1.0'/>"; //글자 크기 설정
    // s=s+"<meta http-equiv='refresh' content='5'/>";
    s = s + "<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />"; //한글 인코딩 utf-8
    s = s + "<head></head><body>안녕하세요!</body></html>";

    client.print(s); //클라이언트에게 응답 전달
    delay(1);
    Serial.println("Client disconnected");
}