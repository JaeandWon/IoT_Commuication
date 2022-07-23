const express = require("express"); //express라는 변수에 express 모듈을 불러옴
const server = express(); //server라는 변수에 express라는 객체를 생성

server.get("/", (req, res) => {
    res.sendFile(__dirname+"/index.html");
});

server.get("/about", (req, res) => {
    res.sendFile(__dirname+"/about.html");
});

server.listen(3000, (err) => {
    if (err) //에러가 발생하면(3000번 포트가 이미 사용 중)
        return console.log(err);
    else //에러 발생 X
        console.log("The server is listening on port 3000");
 })