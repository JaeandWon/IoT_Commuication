const http = require('http'); // 웹서버용
const fs = require('fs'); // HTML파일읽기용
const PORT = 3000; // 접속포트주소

const serverbody = (request, response) => {
    fs.readFile('sample.html', 'utf8', (err, data) => { //data param은 html tag 정보들이 들어감
        response.writeHead(200, { 'Content-Type': 'text/html;charset=utf8' }); 
        
        response.end(data);
        console.log("웹페이지에 접속하였습니다");
    }); 
};

const server = http.createServer(serverbody); 

server.listen(PORT, ()=>{
    console.log("The server is lislgslgjslgjs");
});