/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

*/
#include <SoftwareSerial.h>
//const unsigned int IR1=16,IR3=18,IR2=17;
const unsigned int M13P=4,M13N=5,M24P=6,M24N=7;//2,3,4,5M13P=D1,M13N=D2,M24P=D3,M24N=D4
boolean autonomus=false;
// Replace with your network credentials



//Adafruit_BME280 bme(BME_CS);  // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);  // software SPI
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial mySerial (rxPin, txPin);

void halt(void)
{
  digitalWrite(M13P,LOW);
  digitalWrite(M13N,LOW);
  digitalWrite(M24P,LOW);
  digitalWrite(M24N,LOW);
  //Serial.println("Stop");
}
void forward(void)
{
  digitalWrite(M13P,HIGH);
  digitalWrite(M13N,LOW);
  digitalWrite(M24P,HIGH);
  digitalWrite(M24N,LOW);
  //Serial.println("Forward");
}
void backward(void)
{
  digitalWrite(M13P,LOW);
  digitalWrite(M13N,HIGH);
  digitalWrite(M24P,LOW);
  digitalWrite(M24N,HIGH);
  //Serial.println("Backward");
}
void left(void)
{
  digitalWrite(M13N,HIGH);
  digitalWrite(M13P,LOW);
  digitalWrite(M24N,LOW);
  digitalWrite(M24P,HIGH);
  //Serial.println("Left");
}
void right(void)
{
  digitalWrite(M13P,HIGH);
  digitalWrite(M13N,LOW);
  digitalWrite(M24N,HIGH);
  digitalWrite(M24P,LOW);

  //Serial.println("Right");
}

void setup() 
{
  mySerial.begin(9600);
  //pinMode(IR1,INPUT);
  //pinMode(IR3,INPUT);
  //pinMode(IR2,INPUT);
  pinMode(M13P,OUTPUT);
  pinMode(M13N,OUTPUT);
  pinMode(M24P,OUTPUT);
  pinMode(M24N,OUTPUT);
  Serial.begin(9600);
  Serial.println("Start");
  halt();
  

  // (you can also pass in a Wire library object like &Wire2)
}

void loop() 
{ 
                   // yield();
                    if(Serial.available()>0)
                    {
                      
                            switch(Serial.read())
                            {
                              case 'f': forward();
                                        mySerial.println("Forward, , , , , ");
                                        delay(300);
                                        halt();
                                        break;
                              case 'b': backward();
                                        mySerial.println(" ,Backward, , , , ");
                                        delay(300);
                                        halt();
                                        break;
                              case 'l': left();
                                        mySerial.println(" , ,Left, , , ");
                                        delay(300);
                                        halt();
                                        break;
                              case 'r': right();
                                        mySerial.println(" , , ,Right, , ");
                                        delay(300);
                                        halt();
                                        break;
                              case 's': halt();
                                        //Serial.println("Stop");
                                        break;
                              case 'a': autonomus=true;
                                        //Serial.println("Switched to AUTONOMUS mode");
                                        break;
                              default : break;          
                            }


                    }
}
   
  


            
 