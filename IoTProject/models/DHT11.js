const mongoose = require("mongoose");
const DHT11Schema = mongoose.Schema(
    {
        tmp : 
        {
            type : String,
            required : true
        },
        hum :
        {
            type : String,
            required : true
        },
        created_at :
        {
            type : Date,
            default : Date.now
        }
    }
);

//model이라는 함수를 이용해 DHT11Schema정보를 DHT11이라는 테이블에 저장 
module.exports = mongoose.model('DHT11', DHT11Schema);

