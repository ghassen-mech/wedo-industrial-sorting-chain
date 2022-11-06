
var express = require('express');
var router = express.Router();
//var carval = require('../models/carval');
var chainclass = require('../models/chaindata');
var mqtt = require('mqtt');
const app = express();

//wedo
let chaindata = 0;
let chainState = 0;
let lastchoise1=0;
let lastchoise2=0;
let lastchoise3=0;
let lasttotale=0;



var cors = require('cors');

router.use(cors());


//connetct to adafruit platform
//tessssssss
var client = mqtt.connect('mqtt://io.adafruit.com', {
    username: '****',
    password: '************'
});

//feeds a utiliser
var wedochain = `${client.options.username}/feeds/wedochain`;
var wedochainState = `${client.options.username}/feeds/wedochainState`;
//subscribe to weedochain feed
client.on('connect', function() {
  console.log('connected');
  client.subscribe(wedochain, function(err) {
      if(! err) {
          console.log('subscribed');
          //client.publish(espcar, 'Hello from NodeJS');
          client.publish(wedochain, 0);
         // client.publish(wedochainState, 0);

      }
  });

});

//subscribe to weedostate feed
client.subscribe(wedochainState, function(err) {
  if(! err) {
      console.log('subscribed');
      //client.publish(espcar, 'Hello from NodeJS');
      client.publish(wedochainState, 'hello stateee');
     // client.publish(wedochainState, 0);

  }
});

//receive message from adafruit platform
client.on('message', function(topic, message,packet) {

  console.log(message.toString());
 
  
  if (topic === 'ghass/feeds/wedochain') {
    chaindata = message.toString();
  }
 
  if(chaindata ){

   addwedodata(chaindata);

  }
  //state
  if (topic === 'ghass/feeds/wedochainState') {
    chainState = message.toString();
  }
  

});

//add data to mongodb
function addwedodata(chaindata1){
  

  new chainclass({
    Matriqule : "jklnum123",
    Choix1 : between2(chaindata1.toString(),"A","B") ,
    Choix2 : between2(chaindata1.toString(),"B","C"),
    Choix3 : between2(chaindata1.toString(),"C","T"),
    Totale : between2(chaindata1.toString(),"T","F"),
    
    Date : new Date()
  }).save();

}
//
/* wedo-state  from react project*/

router.get("/state/:state", (req, res) => {
  let  state= req.params.state;
  console.log(state)
  // console.log(State);
  if(state == 'start'){
  console.log("wedochain is ON");
  client.publish(wedochainState, 'startW');
  res.send('helllo ghassen ON');
  return;
  }
  if(state == 'stop'){
    console.log("wedochain is OFF ");
    client.publish(wedochainState, 'stopW');
    res.send('helllo ghassen OFF');
    return;
  } 


  res.send('Error ')

});


router.get('/wedochain', function(req, res, next) {

  chainclass.find(function(error,data){
    console.log(data);
    res.json(data);
    
  }).limit(1).sort({$natural:-1}); 

});




function afterT(str){
  return str.substring(str.indexOf('-') + 1);
}

function between2(str,ch1,ch2){
  return str.slice(str.indexOf(ch1) + 1,str.lastIndexOf(ch2));
}




module.exports = router;

