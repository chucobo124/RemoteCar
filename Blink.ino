#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#define MAX_BTCMDLEN 128
Servo myservo;

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

SoftwareSerial BTSerial(2,3); 
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  myservo.attach(13,1000,2000);
  Serial.begin(9600);
  BTSerial.begin(9600);
  myservo.write(0);
  pinMode(12, OUTPUT);
}
 int insize,ii;
 int len = 0 ;
 byte cmd[MAX_BTCMDLEN];
 int uartCmdLen = 0;
 int trick = 0 ;
void runMoter(){
    digitalWrite(12, HIGH);   
    delay(5000);            
    digitalWrite(12, LOW);   
    delay(5000);
  }
void turnRight(){
  delay(300);
    for(int i = 1000; i <= 2000; i+=100){
      myservo.writeMicroseconds(i);
      delay(300);
    }
  }
void turnLeft(){
  delay(300);  
    for(int i = 2000; i >= 1000; i-=100){
      myservo.writeMicroseconds(i);
      delay(300);
    } 
  }
void listenCmd(){
  while(trick < MAX_BTCMDLEN){
    if ((insize =(BTSerial.available()))>0){
        for(ii=0; ii<insize; ii++){
           cmd[(len++)%MAX_BTCMDLEN]=char(BTSerial.read());
        }
     }
     else{
       trick++;
     }
     delay(5);
  }
}
void listenCommand(){
  char *p;
   char key = 0;
   int avaliable = 0 ; 
   /*key = Serial.read();*/
   key = BTSerial.read();
   avaliable  = BTSerial.available();
   Serial.println("My Status");
   Serial.println(avaliable); 
   Serial.println("Key");
   Serial.println(key);
   switch(key){
     case 'a':
       runMoter();
      break;
     case 'r':
         turnRight();
      break;
     case 'l':
         turnLeft();
       break;
   }
}
void loop() {
   listenCommand();
}
