#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <dht11.h>
#include <Servo.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#define TH 8
LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;
const byte rxPin = 2;
const byte txPin = 3;
const int BEDWET = A0;
const int CRYING = 4;
const int SWING1=5;
const int FAN=6;
const int BUZZER=7;
SoftwareSerial mySerial (rxPin, txPin);
String person;
String crying;
String bedwet;
dht11 DHT11;
Servo SWING;
int aax=0;
int bbx=0;
const byte LED=13;
void setup()
{
   pinMode(FAN,OUTPUT);
   pinMode(BUZZER,OUTPUT);
   pinMode(CRYING,INPUT);
   digitalWrite(FAN,LOW);
   digitalWrite(BUZZER,LOW);
   pinMode(LED,OUTPUT);
    digitalWrite(LED,LOW);
   #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
  SWING.attach(SWING1);
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IOT BASED CHILD");  
  lcd.setCursor(0,1);
  lcd.print(" MONITORING SYS");
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  pinMode(LED_PIN, OUTPUT);
  
  delay(3000);
  lcd.clear();


  
}
 
void loop()
{
    int temp_adc_val;
    float temp_val;
    float temp_val1;
    int temp;
    
// CHILD MOVEMENT CODE
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    
    if((ax>8000) || (ax<-6000) )
    {
       aax=ax;
       person="MOVED";
       digitalWrite(FAN,HIGH);
    }
    else 
    {
       person="STABLE";
    }
//READING TEMP AND HUM

int chk = DHT11.read(TH);
String tmp=(String)DHT11.temperature;
String hum=(String)DHT11.humidity;
//READING SOIL

int bedwetval=analogRead(BEDWET);
if(bedwetval>=750)
{
bedwet="NO";
}
else
{
 bedwet="YES"; 
 digitalWrite(BUZZER,HIGH);
}

//READING SOUND
int soundval=digitalRead(CRYING);
Serial.println(soundval);


if(soundval==1)
{
    crying="YES";
    for (int pos=0;pos<=90;pos+=1)
    { 
        // in steps of 1 degree
        SWING.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      for (int pos=90;pos>=0;pos-=1) 
      { // goes from 180 degrees to 0 degrees
        SWING.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }

      for (int pos=0;pos<=90;pos+=1)
    { 
        // in steps of 1 degree
        SWING.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      for (int pos=90;pos>=0;pos-=1) 
      { // goes from 180 degrees to 0 degrees
        SWING.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }

      for (int pos=0;pos<=90;pos+=1)
    { 
        // in steps of 1 degree
        SWING.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      for (int pos=90;pos>=0;pos-=1) 
      { // goes from 180 degrees to 0 degrees
        SWING.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
}
else
{
 crying="NO"; 
}
                                  lcd.clear();
                                  delay(200);
                                   digitalWrite(LED,HIGH);
                                  lcd.setCursor(0,0);
                                  lcd.print("CRY:"+crying+",");   
                                
                                  lcd.setCursor(8,0);
                                  lcd.print("BWET:"+bedwet);  
                               
                                  lcd.setCursor(0,1);
                                  lcd.print("PS:"+person+",");

                                  lcd.setCursor(10,1);
                                  lcd.print("TP:"+tmp+"C");


  mySerial.println(person+","+tmp+","+hum+","+bedwet+","+crying+","+"dum"+","+"dum"+","+"dum"+","+"dum"+","+"dum");
  Serial.println(person+","+tmp+","+hum+","+bedwet+","+crying+","+"dum"+","+"dum"+","+"dum"+","+"dum"+","+"dum");
  delay(3000);
  digitalWrite(FAN,LOW);digitalWrite(BUZZER,LOW);digitalWrite(LED,LOW);
}
 
