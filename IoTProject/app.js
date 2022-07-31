/*mosquitto server dht11 topic으로부터 온습도 데이터 읽어오기*/

//mqtt 모듈 불러오기 
const mqtt = require("mqtt");
//nodejs에서 mqtt server와 connect하기 위해 client 객체 생성

const DHT11 = require("./models/DHT11");
const express = require("express");
const app = express();
const http = require("http");
const mongoose = require("mongoose");
const devicesRouter = require("./routes/devices");
const bodyParser = require("body-parser");
require('dotenv/config');

app.use(express.static(__dirname + "/public"));

// 라우터 만들기
app.use(bodyParser.urlencoded({ extended: false }));
app.use("/devices", devicesRouter);           // 이 코드가 위에보다 밑에 있어야 함.. 
app.use(bodyParser.json());


// MQTT 접속
const client = mqtt.connect("mqtt://192.168.0.3"); 
client.on("connect", ()=> 
{
    console.log("mqtt connect");
    client.subscribe("dht11");
});

client.on("message", async(topic, message)=>
{
    var obj = JSON.parse(message);
    
    var date = new Date();
    var year = date.getFullYear();
    var month = date.getMonth();
    var today = date.getDate();
    var hours = date.getHours();
    var minutes = date.getMinutes();
    var seconds = date.getSeconds();
    obj.creadte_at = new Date(Date.UTC(year, month, today, hours, minutes, seconds))
    console.log(obj);

    const dht11 = new DHT11(
        {
            tmp : obj.tmp,
            hum : obj.hum,
            created_at: obj.created_at
        }
    )
    
    try{
        const saveDHT11 = dht11.save();
        console.log("insert OK");
    }catch(err)
    {
        console.log({message : err });
    }
    
    
});

// web server 만들기 : express
app.set("port", "3000");
var server = http.createServer(app);

// 소켓 만들기
var io = require("socket.io")(server);
io.on("connection", (socket) => 
{
    // 웹에서 소켓을 이용한 DHT11 센서데이터 모니터링 
    socket.on("socket_evt_mqtt", (data) => 
    {
        DHT11.find({}).sort({_id : -1}).limit(1).then(obj => 
            { 
                socket.emit("socket_evt_mqtt", JSON.stringify(obj[0]));
            });
    });

    socket.on("socket_evt_led", (data) => 
    {
        var obj = JSON.parse(data);
        client.publish("led", obj.led+""); // "1", "2"
    });
});

server.listen(3000, (err) => 
{ 
    if(err)
    {
        return console.log(err);
    }
    else
    {
        console.log("server ready");
        // Coonection to DB
        mongoose.connect(process.env.MONGODB_URL,
            { useNewUrlParser: true,useUnifiedTopology: true }, 
            () => console.log('connected to DB!')
            );
    }
});

