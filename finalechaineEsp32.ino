#include <ESP8266WiFi.h>
#include <Servo.h>
//chain state
boolean chainstate = false ;
int motor1Pin1 = 9; 
//ir1
#define IR1 16
bool ir1;
int count1 = 0;
boolean security1 = true;
boolean state = true;
//ir2
#define IR2 5
bool ir2;
int count2 = 0;
boolean security2 = true;
boolean state2 = true;
//ir3
#define IR3 4
bool ir3;
int count3 = 0;
boolean security3 = true;
boolean state3 = true;
//ir4
#define IR4 0
bool ir4;
int count4 = 0;
boolean security4 = true;
boolean state4 = true;

//Servo1
#define SERVO_PIN1 2
Servo servo;
//Servo2
#define SERVO_PIN2 14
Servo servo2;
int angle = 0;          // the current angle of servo motor
int lastMotionState;    // the previous state of motion sensor
int currentMotionState;
//color
#define S2 12
#define S3 13
#define sensorOut 15
int redfrequency = 0;
int greenfrequency = 0;
int bluefrequency = 0;
int red = 0;
int green = 0;
int bleu = 0;
int countred =0;
int countgreen=0;

//wifi
#include <ESP8266WiFi.h> //<WiFi.h>
#include "AdafruitIO_WiFi.h"
 
#define WIFI_SSID       "WDC-WLAN"//"Redmi"//globalnet//esprit//Redmi
#define WIFI_PASS       "WwwDC19$"//"23091997" //39581064  70834402//23091997
//"70834402"
 
#define IO_USERNAME    "ghass"
#define IO_KEY         "aio_bgGB79o3k91ktCPOS16S66HFtzTa"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *wedochain = io.feed("wedochain"); 
AdafruitIO_Feed *wedochainstate = io.feed("wedochainstate");
int pieces =0;
void setup() {
  Serial.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  digitalWrite(motor1Pin1, LOW);
  //servo
  
  servo.attach(SERVO_PIN1);           // attaches the servo on pin 9 to the servo object
  servo2.attach(SERVO_PIN2);
  servo.write(angle);
  servo2.write(0);
  //color
  pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(sensorOut, INPUT);
//wifi
 io.connect();
// received from adafruit io.
wedochainstate->onMessage(handleMessage);
 
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  
}
void loop() {
io.run();
while(chainstate){
io.run();
//color

digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
// Reading the output frequency
redfrequency = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
Serial.print("R= ");//printing name
Serial.print(redfrequency);//printing RED color frequency
Serial.print(" ");
delay(20);
// Setting Green filtered photodiodes to be read
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
// Reading the output frequency
greenfrequency = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
Serial.print("G= ");//printing name
Serial.print(greenfrequency);//printing RED color frequency
Serial.print(" ");
delay(20);
// Setting Blue filtered photodiodes to be read
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
// Reading the output frequency
bluefrequency = pulseIn(sensorOut, LOW);
// Printing the value on the serial monitor
Serial.print("B= ");//printing name
Serial.print(bluefrequency);//printing RED color frequency
Serial.println(" ");
delay(20);
if ( redfrequency<30 && 22<redfrequency && greenfrequency<19 && 11<greenfrequency && bluefrequency< 10   && 5<bluefrequency  )  {Serial.print("bbbbbbb"); bleu = 1;}
if ( redfrequency<40 && 30<redfrequency && greenfrequency<25 && 15<greenfrequency && bluefrequency< 38   && 28<bluefrequency  ) {Serial.print("ggggggg");green =1;}
if ( redfrequency<23 && 12<redfrequency && greenfrequency<77 && 69<greenfrequency && bluefrequency< 62   && 52<bluefrequency  )  {Serial.print("rrrrr");red=1;}
Serial.print(" green  ");Serial.println(green);
Serial.print(" red  ");Serial.println(red);
  

  //ir 1
  ir1 = digitalRead(IR1);
  if (ir1 == 0 && state && security1)
  {
    pieces++;
    Serial.print("pieces   : " ); Serial.println(pieces);
    count1++;
    state = false;
    security1 = false;
    Serial.print("IR 1 :  " ); Serial.println(count1);
  
  }
  if (ir1 == 1)  {
    security1 = true;
  }
  if (ir1 == 0)  {
    state = true;
    delay(300);
  }

  //ir 2
  ir2 = digitalRead(IR2);
  if (ir2 == 0 && state2 && security2 && red == 1 )
  {
    
    count2++;
    countred++;
    state2 = false;
    security2 = false;
    Serial.print("IR 2 :  " ); Serial.println(count2);
    delay(450);
    servo.write(130);
    delay(500);
    servo.write(0);
    red=0;
    //adf
     // pieces++;
      if( pieces>2 ){
            io.run();
            wedochain->save("A"+String(count2)+"B"+String(count3)+"C"+String(count4)+"T"+String(count1)+"F");
            pieces=0;
         }
    delay(100);
  }
  if (ir2 == 1)  {
    security2 = true;
  }
  if (ir2 == 0)  {
    state2 = true;
    delay(300);
  }
  //ir 3
  ir3 = digitalRead(IR3);
  if (ir3 == 0 && state3 && security3 && green == 1)
  {
    countgreen++;
    count3++;
    state3 = false;
    security3 = false;
    Serial.print("IR 3 :  " ); Serial.println(count3);
    delay(300);
    servo2.write(140);
    delay(500);
    servo2.write(0);
    green = 0;
    //adf
    //pieces++;
      if( pieces>2 ){
            io.run();
            wedochain->save("A"+String(count2)+"B"+String(count3)+"C"+String(count4)+"T"+String(count1)+"F");
            pieces=0;
         }
    delay(100);
  }
  
  if (ir3 == 1)  {
    security3 = true;
  }
  if (ir3 == 0)  {
    state3 = true;
    delay(300);
  }
  //ir 4
  ir4 = digitalRead(IR4);
  if (ir4 == 0 && state4 && security4)
  {
    count4++;
    state4 = false;
    security4 = false;
    Serial.print("IR 4 :  " ); Serial.println(count4);
     //adf
     
      if( pieces>3 ){
            io.run();
           
            wedochain->save("A"+String(count2)+"B"+String(count3)+"C"+String(count4)+"T"+String(count1-1)+"F");
            pieces=0;
         }
  }
  if (ir4 == 1)  {
    security4 = true;
  }
  if (ir4 == 0)  {
    state4 = true;
    delay(300);
  }
}
}
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <-  ");
  Serial.println(data->toString());
  if(data->toString() == "startW"){
    chainstate= true;
    Serial.print("heyyyy");
    Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, HIGH);
    
    }
   if(data->toString() == "stopW"){
    chainstate= false;
    Serial.print("noooo");
    Serial.println("Moving back ");
  digitalWrite(motor1Pin1, LOW);
    
    }
  
}
