#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "GravityTDS.h"
#include <SoftwareSerial.h>
#define TdsSensorPin A1
#define PHPIN A0 
#define ONE_WIRE_BUS 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long int PH_avgValue; 
float calibration_value = 21.34; 
int Turbidity=A2;
float Tempvolt;
float ntu;
float b;
int buf[10],temp;
GravityTDS gravityTds;
float temperature = 25,tdsValue = 0;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
String ph;
String tds;
String turb;
String tempa;
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial mySerial (rxPin, txPin);
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.begin();
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
  sensors.begin();
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  IOT BASED AQUA ");  
  lcd.setCursor(0,1);
  lcd.print("CLTR MONTRG SYS");
  delay(3000);
  lcd.clear();
}
 
void loop()
{
/*#################################### PH SENSOR ###################################*/
  
              for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
              { 
                buf[i]=analogRead(PHPIN);
                //delay(10);
              }
              for(int i=0;i<9;i++)        //sort the analog from small to large
              {
                for(int j=i+1;j<10;j++)
                {
                  if(buf[i]>buf[j])
                  {
                    temp=buf[i];
                    buf[i]=buf[j];
                    buf[j]=temp;
                  }
                }
              }
              PH_avgValue=0;
              for(int i=2;i<8;i++)                      //take the average value of 6 center sample
              PH_avgValue+=buf[i];
              float phValuevolt=(float)PH_avgValue*5.0/1024/6; //convert the analog into millivolt
              phValuevolt=3.5*phValuevolt;
              //float actph= -5.70 * phValuevolt + calibration_value;                     //convert the millivolt into pH value
              ph=String(phValuevolt+4.5);
              lcd.setCursor(0,0);
              //lcd.print("        ");
              lcd.print("PH:"+ph);
   /*#################################### END OF PH SENSOR ###################################*/

   /*#################################### TEMPARATURE SENSOR #################################*/
              Tempvolt = 0;
              for(int i=0; i<800; i++)
              {
              Tempvolt+=((float)analogRead(Turbidity)/1023)*5;
              }
              Tempvolt=Tempvolt/800;
              Tempvolt=round_to_dp(Tempvolt,2);
              if(Tempvolt < 2.5)
              {
              ntu=3000;
              }else
              {
              ntu=-1120.4*square(Tempvolt)+5742.3*Tempvolt-4353.8; 
              }

            //  int Tempvolt1=analogRead(Turbidity);
            //  int turbi1=map(Tempvolt1,0,640,100,0);


              turb=String(ntu) ;
              lcd.setCursor(8,0);
              //lcd.print("        ");
              lcd.print(",TB:"+turb);
  /*#################################### TDS SENSOR #################################*/
              gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
              gravityTds.update();  //sample and calculate
              tdsValue = gravityTds.getTdsValue();  // then get the value
              tds=String(tdsValue);
              lcd.setCursor(0,1);
              //lcd.print("        ");
              lcd.print("ppm:"+tds);
  /*#################################### END OF TDS SENSOR #################################*/
  /*#################################### DS18B20 SENSOR #################################*/
              sensors.requestTemperatures(); 
             //Serial.print("Celsius temperature: ");
             // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
             //Serial.print(sensors.getTempCByIndex(0)); 
             //Serial.print(" - Fahrenheit temperature: ");
             //Serial.println(sensors.getTempFByIndex(0));
              tempa=String(sensors.getTempCByIndex(0)) ;
              lcd.setCursor(8,1);
              //lcd.print("        ");
              lcd.print(",TC:"+tempa);
              Serial.println(ph+","+turb+","+tds+","+tempa+","+"dum"+","+"dum"+","+"dum"+","+"dum"+","+"dum"+","+"dum");
              mySerial.println(ph+","+turb+","+tds+","+tempa+","+"dum"+","+"dum"+","+"dum"+","+"dum"+","+"dum"+","+"dum");
              delay(1000);
  /*####################################  END OF DS18B20 SENSOR #################################*/


}
 
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}