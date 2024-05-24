const unsigned int IR1=16,IR3=18,IR2=17;
const unsigned int M1P=4,M1N=5,M2P=6,M2N=7;
const unsigned int M3P=8,M3N=9,M4P=10,M4N=11;
#include <SoftwareSerial.h>
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
boolean autonomus=false;
void datarxd(void)
{
digitalWrite(LED_BUILTIN, HIGH);
delay(100);
digitalWrite(LED_BUILTIN, LOW);
delay(900);
}
void halt(void)
{
  digitalWrite(M1P,LOW);
  digitalWrite(M1N,LOW);
  digitalWrite(M2P,LOW);
  digitalWrite(M2N,LOW);
  digitalWrite(M3P,LOW);
  digitalWrite(M3N,LOW);
  digitalWrite(M4P,LOW);
  digitalWrite(M4N,LOW);
  //Serial.println("Stop");
}
void forward(void)
{
  digitalWrite(M1P,HIGH);
  digitalWrite(M1N,LOW);
  digitalWrite(M2P,HIGH);
  digitalWrite(M2N,LOW);
  digitalWrite(M3P,HIGH);
  digitalWrite(M3N,LOW);
  digitalWrite(M4P,HIGH);
  digitalWrite(M4N,LOW);
  //Serial.println("Forward");
}
void backward(void)
{
  digitalWrite(M1P,LOW);
  digitalWrite(M1N,HIGH);
  digitalWrite(M2P,LOW);
  digitalWrite(M2N,HIGH);
  digitalWrite(M3P,LOW);
  digitalWrite(M3N,HIGH);
  digitalWrite(M4P,LOW);
  digitalWrite(M4N,HIGH);
  //Serial.println("Backward");
}
void left(void)
{
  digitalWrite(M1N,HIGH);
  digitalWrite(M1P,LOW);
  digitalWrite(M2P,LOW);
  digitalWrite(M2N,HIGH);
  digitalWrite(M3P,HIGH);
  digitalWrite(M3N,LOW);
  digitalWrite(M4N,LOW);
  digitalWrite(M4P,HIGH);
  //Serial.println("Left");
}
void right(void)
{
  digitalWrite(M1P,HIGH);
  digitalWrite(M1N,LOW);
  digitalWrite(M2P,HIGH);
  digitalWrite(M2N,LOW);
  digitalWrite(M3P,LOW);
  digitalWrite(M3N,HIGH);
  digitalWrite(M4P,LOW);
  digitalWrite(M4N,HIGH);
  //Serial.println("Right");
}
void setup()
{
   pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    
    // Set the baud rate for the SoftwareSerial object
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IR1,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR2,INPUT);
  pinMode(M1P,OUTPUT);
  pinMode(M1N,OUTPUT);
  pinMode(M2P,OUTPUT);
  pinMode(M2N,OUTPUT);
  pinMode(M3P,OUTPUT);
  pinMode(M3N,OUTPUT);
  pinMode(M4P,OUTPUT);
  pinMode(M4N,OUTPUT);
  Serial.begin(9600);
 // Serial.println("Start");
  halt();
  
}
void loop()
{
        while(1)
        {
              if(autonomus)
              {
                    mySerial.println("Autonomus");
                    if(mySerial.available()>0)
                    {
                      datarxd();
                        if(mySerial.read()=='u')
                          {
                            autonomus=false;
                            halt();
                          }
                    }

                    if(digitalRead(IR3)==LOW && digitalRead(IR1)==LOW && digitalRead(IR2)==LOW)
                    {
                    forward();
                    }

                    else if( (digitalRead(IR3)==LOW && digitalRead(IR1)==HIGH && digitalRead(IR2)==LOW) || (digitalRead(IR3)==HIGH && digitalRead(IR1)==HIGH && digitalRead(IR2)==LOW))
                    {
                    right();
                    }

                    else if(digitalRead(IR3)==LOW && digitalRead(IR1)==HIGH && digitalRead(IR2)==HIGH)
                    {
                    left();
                    }


                    else if(digitalRead(IR3)==HIGH && digitalRead(IR1)==HIGH && digitalRead(IR2)==HIGH)
                    {
                    halt();
                    }
              }


              else
              {
                if(mySerial.available()>0)
                {
                  switch(mySerial.read())
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
  }
}
