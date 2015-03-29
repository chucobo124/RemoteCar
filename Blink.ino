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
 int turnAnchor = 0 ;
void runMoter(){
    digitalWrite(12, HIGH);   
    delay(100);            
  }
void backMoter(){
    digitalWrite(12, LOW);   
    delay(100);            
  }  
void turnRight(){
     if (turnAnchor <=2000){
        myservo.writeMicroseconds(turnAnchor+200);
        delay(100);
     }
  }
void turnLeft(){
    if(turnAnchor >= 1000){
      myservo.writeMicroseconds(turnAnchor-200);
      delay(100);
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
     case 'ar':
         runMoter();
         turnRight();
      break;
     case 'al':
         runMoter();
         turnLeft();
      break;
     case 'b':
         backMoter();
     case 'bl':
         backMoter();
         turnLeft();
     case 'br':
         backMoter();
         turnRight();
     break;
   }
}
void loop() {
   listenCommand();
}
