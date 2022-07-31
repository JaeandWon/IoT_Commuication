var express = require("express");
var router = express.Router();
const mqtt = require("mqtt");

// MQTT Server(mosquitto)에 접속 
const client = mqtt.connect("mqtt://192.168.0.3"); 


// Web에서 rest-full 요청받는 부분(POST 방식으로)
router.post("/led", function(req, res, next)
{
    res.set("Content-Type", "text/json");
    if (req.body.flag == "on")
    {
        client.publish("led", "1");
        res.send(JSON.stringify({ led: "on" }))
    }
    else
    {
        client.publish("led", "2");
        res.send(JSON.stringify({"led" : "off"}));
    }
});

//module.exports를 해야 app.js에서 여기로 경로 접근 가능 
module.exports = router;