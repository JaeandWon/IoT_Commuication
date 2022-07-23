const express = require("express"); //express라는 변수에 express 모듈을 불러옴
const server = express(); //server라는 변수에 express라는 객체를 생성



/*
middleware의 목적: 다른 요청을 실행하기 전에 공통적인 작업을 하고싶을 때 사용 
ex) A폴더 안에 있는 파일들 (B C D)에 접근하고 싶을 때, middleware로 A 경로만 지정해주면
    B C D를 참조할 때 B C D만 참조하면 됨 
*/

//express.static: 특정 파일의 경로를 공통으로 사용할 수 있게 함 
server.use(express.static(__dirname + "/public"));

// server.use((req, res, next) => { //Client의 모든 요청은 use를 통함 (get, post 상관 x)
//     console.log("This is Middleware");
//     req.user = {bit: "1234"};
//     next(); //다음 작업으로 이동 
// });

server.get("/", (req, res) => { 
    console.log(req.user)
    res.sendFile(__dirname+"/index.html");
});

server.get("/about", (req, res) => {
    res.sendFile(__dirname+"/about.html");
});

server.use((req, res) => { 
    res.sendFile(__dirname + "/404.html");
});

server.listen(3000, (err) => {
    if (err) //에러가 발생하면(3000번 포트가 이미 사용 중)
        return console.log(err);
    else //에러 발생 X
        console.log("The server is listening on port 3000");
 })
