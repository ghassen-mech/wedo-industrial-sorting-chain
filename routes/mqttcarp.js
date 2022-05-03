var express = require('express');
var router = express.Router();
var carval = require('../models/carval');
var mqtt = require('mqtt');
let rpmandOther = 0;
let Speed = 0;


var cors = require('cors');

router.use(cors());



//tessssssss
var client = mqtt.connect('mqtt://io.adafruit.com', {
    username: 'ghass',
    password: 'aio_jhBi21r4rB5Bb2YNIwR5cJVFuYUc'
});

var espcar = `${client.options.username}/feeds/espcar`;
var speed = `${client.options.username}/feeds/speed`;
//send
client.on('connect', function() {
  console.log('connected');


  client.subscribe(espcar, function(err) {
      if(! err) {
          console.log('subscribed');
          //client.publish(espcar, 'Hello from NodeJS');
          client.publish(espcar, 0);

      }
  });

});
//receive
client.on('message', function(topic, message,packet) {

  console.log(message.toString());
 
  
  if (topic === 'ghass/feeds/espcar') {
    rpmandOther = message.toString();
  }
 
  if(rpmandOther ){
    addcardata(rpmandOther);//you must add id or serie number

  }
  

});
//////////////
//console.log(beforeT("222,ggg"));
function beforeT(str){
  return str.substring(0,str.indexOf('-'));
  
}
function afterT(str){
  return str.substring(str.indexOf('-') + 1);
}

function between2(str,ch1,ch2){
  return str.slice(str.indexOf(ch1) + 1,str.lastIndexOf(ch2));
}




function addcardata(rpmandOther1){

  new carval({
    Matriqule : afterT(rpmandOther1),
    rpm : between2(rpmandOther1.toString(),"m","t") ,
    Speed : between2(rpmandOther1.toString(),"s","-") ,
    Temp : between2(rpmandOther1.toString(),"e","d") ,
    CodeDef : between2(rpmandOther1.toString(),"f","s") ,
    Date : new Date()
  }).save();

}
////////////////



/* GET users listing. */

router.get('/carval', function(req, res, next) {

  carval.find(function(error,data){
    console.log(data);
    res.json( data);
    
  });

});
////find by matriqule
router.get('/carval/:matriqe', function(req, res, next) {
  let matriq = req.params.matriqe;
  carval.find({Matriqule : matriq } ,function(error,data){
    res.json( data);
  });
});
////current data
router.get('/carval/current/:matriqe', function(req, res, next) {
  let matriq = req.params.matriqe;
  console.log(matriq);
  if(matriq === afterT(rpmandOther.toString())){
    res.json( [{  id : 222 ,Matriqule : afterT(rpmandOther),
     rpm : between2(rpmandOther.toString(),"m","t"),Speed : between2(rpmandOther.toString(),"s","-"),
     Temp : between2(rpmandOther.toString(),"e","d"),CodeDef : between2(rpmandOther.toString(),"f","s") , Date : Date }]);
  }
  else
  res.json( [{ Speed : 999 }]);

  
});




////
router.get("/ajout",function(req,res,next){
  new carval({
    Matriqule : 22,
    rpm : 222 ,
    Speed : 222 ,
    Date : new Date()
  }).save(res.end("ok"));
});

module.exports = router;

