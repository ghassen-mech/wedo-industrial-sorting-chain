var mongoose=require('mongoose');
var Schema=mongoose.Schema;
var carval = new Schema(
    {
        Matriqule : String,
        rpm : Number,
        Speed : Number,
        Temp : Number,
        CodeDef : String,
        Date : Date
    }
);
module.exports = mongoose.model("mqttcar1",carval);
