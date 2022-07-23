const http = require("http"); //require ~= #include 
const fs = require("fs");
const { response } = require("express");

const server = http.createServer((req, res) => { //req: 클라이언트에 요청을 받음  res: 클라이언트에 data를 전달
    if (req.url === "/") 
    {
        res.write("<h1>Hello from nodejs</h1>")
        console.log("웹페이지에 접속하였습니다");
    }
    else 
    {
        res.write(`<h1>You have entered this url : ${req.url}</h1>`);
    }
    res.end();
});

server.listen(3000, () => { //3000번 포트를 염  () => {} 익명함수
    console.log("The server is listening on port 3000"); 
}); 