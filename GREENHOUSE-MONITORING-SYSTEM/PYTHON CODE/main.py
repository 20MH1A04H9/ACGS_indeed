from machine import I2C, Pin
from machine import Pin,UART
import utime as time
import time
from pico_i2c_lcd import I2cLcd
i2c = I2C(0, sda=Pin(8), scl=Pin(9), freq=400000)
from dht import DHT11, InvalidChecksum
I2C_ADDR = i2c.scan()[0]
DHT11pin = Pin(28, Pin.OUT, Pin.PULL_DOWN)
uart = UART(1, baudrate=9600, tx=Pin(4), rx=Pin(5))
uart.init(bits=8, parity=None, stop=2)
LDR=machine.ADC(27)
SOIL=machine.ADC(26)
lcd = I2cLcd(i2c, I2C_ADDR, 2, 16)
lcd.move_to(0,0)
lcd.putstr("IOT BASED GREEN")
lcd.move_to(0,1)
lcd.putstr("HOUSE MNTRG SYS")
time.sleep(5)
PUMP = Pin(20, Pin.OUT)
BULB = Pin(21, Pin.OUT)
lcd.clear()
DUMMY1="dummy"
DUMMY2="dummy"
while True:
  print(I2C_ADDR, "| Hex:",hex(I2C_ADDR))
  print()
  time.sleep(1)
  sensor = DHT11(DHT11pin)
  t  = (sensor.temperature)
  h = (sensor.humidity)
  
  DAYLIGHT=LDR.read_u16()
  MOISTURE=SOIL.read_u16()
  print("DAYLIGHT:",DAYLIGHT)
  print("SOIL:",MOISTURE)
  print("Temp:{}°C ,".format(sensor.temperature))
  print("Humi:{}%".format(sensor.humidity))
  lcd.move_to(0,0)
  lcd.putstr("T:{}C".format(sensor.temperature))
  lcd.move_to(0,1)
  lcd.putstr("H:{}%".format(sensor.humidity))
  TEMP=str(sensor.temperature)
  HUMI=str(sensor.humidity)
  
  if DAYLIGHT<=15000:
    lcd.move_to(8,0)
    lcd.putstr("SL:YES")
    BULB.low()
    BULBS="OFF"
    LDRS="YES"
    
  else:
    lcd.move_to(8,0)
    lcd.putstr("SL:NO ")
    BULB.high()
    BULBS="ON"
    LDRS="NO"
    
  if MOISTURE<=45000:
    lcd.move_to(8,1)
    lcd.putstr("SC:WET")
    PUMP.low()
    SOILS="WET"
    PUMPS="OFF"
    
  else:
    lcd.move_to(8,1)
    lcd.putstr("SC:DRY")
    PUMP.high()
    SOILS="DRY"
    PUMPS="ON"
    
  if t>=33.5																																																																:
    FANS="ON"
    
  else:
    FANS="OFF"
    
  if h>=65:
    ACS="ON"

    
  else:
    ACS="OFF"      
    
#   uart.write(TEMP+","+HUMI+","+LDRS+","+SOILS+","+PUMPS+","+BULBS+","+DUMMY1+","+DUMMY2)
#   print(TEMP+","+HUMI+","+LDRS+","+SOILS+","+PUMPS+","+BULBS+","+DUMMY1+","+DUMMY2)
  
  uart.write(LDRS+","+BULBS+","+TEMP+","+FANS+","+HUMI+","+ACS+","+SOILS+","+PUMPS+", ")
  print(LDRS+","+BULBS+","+TEMP+","+FANS+","+HUMI+","+ACS+","+SOILS+","+PUMPS)

