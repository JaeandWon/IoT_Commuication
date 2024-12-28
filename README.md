# esp32_mqttprotocol

## Dev Environment
MCU : esp32 (used in Arduino IDE)

MQTT API : [Pubsubclient.h](https://github.com/knolleary/pubsubclient)

MQTT broker : Mosquitto

## Goal
Studied basic concept of mqtt protocol in order to utilize it into IoT project later 

## Tech stack used in this project
* Node JS
* MongoDB
* MQTT

## Reference
[사물인터넷 통신은 내 손에 ](https://www.inflearn.com/course/%EC%82%AC%EB%AC%BC%EC%9D%B8%ED%84%B0%EB%84%B7-%ED%86%B5%EC%8B%A0/dashboard)


## Mqtt connection refused
2022 07. 20: Found out mqtt connection problem

  1) Windows 방화벽 제거 후 재연결  →  실패

  2) Inbound rules로 1883 port를 open  →  실패

2022 07. 25: window 방화벽 문제로 예상했으나 mac os에서도 같은 오류 발생 

2022 07. 25: mac에서 연결 성공 (19시 25분)

2022 07. 26: [Solved](https://jaewonahn1234.tistory.com/36)
