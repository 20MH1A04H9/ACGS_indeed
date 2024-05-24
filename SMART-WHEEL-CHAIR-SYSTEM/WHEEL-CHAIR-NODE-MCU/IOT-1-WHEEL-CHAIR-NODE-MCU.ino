/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>
const unsigned int IR1=16,IR3=18,IR2=17;
const unsigned int M13P=2,M13N=3,M24P=4,M24N=5;//2,3,4,5M13P=D1,M13N=D2,M24P=D3,M24N=D4
boolean autonomus=false;
// Replace with your network credentials
const char* ssid     = "IOTWC";
const char* password = "12345678";
int NETWLED=D0;
// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "https://tech-guide.online/iot-1-iotsw.php";


#define SEALEVELPRESSURE_HPA (1013.25)
int i=0;
String  datastr = "20,OFF,32,OFF,80,ON,WET,OFF";
//Adafruit_BME280 bme(BME_CS);  // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);  // software SPI

void datarxd(void)
{
digitalWrite(LED_BUILTIN, HIGH);
delay(100);
digitalWrite(LED_BUILTIN, LOW);
delay(900);
}
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
void dataposting(void)
{
digitalWrite(NETWLED,LOW);
delay(500);
digitalWrite(NETWLED,HIGH);
delay(50);
digitalWrite(NETWLED,LOW);
}
void setup() 
{
  pinMode(IR1,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR2,INPUT);
  pinMode(M13P,OUTPUT);
  pinMode(M13N,OUTPUT);
  pinMode(M24P,OUTPUT);
  pinMode(M24N,OUTPUT);
  Serial.begin(9600);
  Serial.println("Start");
  halt();
  pinMode(NETWLED,OUTPUT); 
  digitalWrite(NETWLED,HIGH);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 digitalWrite(NETWLED,LOW);
  // (you can also pass in a Wire library object like &Wire2)
}

void loop() 
{ 
                    yield();
                    if(Serial.available()>0)
                    {
                      
                            switch(Serial.read())
                            {
                              case 'f': forward();
                                        Serial.println("Forward, , , , , ");
                                        delay(300);
                                        halt();
                                        break;
                              case 'b': backward();
                                        Serial.println(" ,Backward, , , , ");
                                        delay(300);
                                        halt();
                                        break;
                              case 'l': left();
                                        Serial.println(" , ,Left, , , ");
                                        delay(300);
                                        halt();
                                        break;
                              case 'r': right();
                                        Serial.println(" , , ,Right, , ");
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
   
  


            
 