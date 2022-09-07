var mongoose=require('mongoose');
var Schema=mongoose.Schema;
var chaindata = new Schema(
    {
        Matriqule : String,
        Choix1 : Number,
        Choix2 : Number,
        Choix3 : Number,
        Totale : Number,
        Date : Date
    }
);
module.exports = mongoose.model("wedochain",chaindata);
