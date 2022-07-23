/*
   1.express 객체 있는 메소드들을 이용해 서버 구동
   2.clinet가 server에 요청하면 회원 data를 생성하여 db에 저장 
*/
const express = require("express");
const mongoose = require("mongoose");
const server = express();
const User = require("./models/User"); 
require("dotenv").config({ path : "variables.env"});

//클라이언트로 부터 get방식 요청이 오면 
server.get("/", (req, res) => { 
    const newUser = new User();
    newUser.email = "jaewonahn1234@gmail.com";
    newUser.name = "jaewon Ahn";
    newUser.age = 18;

    newUser
        .save() //저장
        .then((data) => {
            console.log(data);
            res.json({                                      // res = response 
                message : "User Create Successfully"
            }); 
        })
        .catch((err) => {
            if(err)
            {
                res.json({                                         //save가 잘못되었을 경우에 에러메세지 
                    message : "User was not Successfully created"
                }); 
                console.log(err.name);
            }
            
    }); 
});


server.listen(3000, (err) => { // 서버를 listen
    if (err)
    {
        return console.log(err);
    }
    else //서버 구동 성공시 
    {
        //mongodb를 connection
        mongoose.connect(process.env.MONGODB_URL, (err) => {  
            if (err)
            {
                console.log(err);
            }
            else
            {
                console.log("Connected to database successfully");
            }
        
         });
    }
});
// const MONGODB_URL =
//  "mongodb+srv://root:1234@education.mee76.mongodb.net/mydb?retryWrites=true&w=majority"; 





 /*
 dotenv => Node.js 서버를 만들 때, github이나 공유되어서는 안되는 중요한 정보들을 사용할 때가 있는데
           env를 사용하면 기존의 기능을 유지하면서 정보를 공유하지 않도록 할 수 있다 
           설치방법: 터미널에 npm install dotenv 입력
 */

           