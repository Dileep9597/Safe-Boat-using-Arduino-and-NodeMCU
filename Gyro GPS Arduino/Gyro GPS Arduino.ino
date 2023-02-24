#include <SoftwareSerial.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "TinyGPS++.h"
TinyGPSPlus gps;
const int MPU6050_addr=0x68;
int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;

SoftwareSerial s(5,6);
SoftwareSerial g(0,1);

 
void setup() {
  s.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  Serial.println("GPS Start"); 

}
 
void loop() {
  while(g.available())              //While there are incoming characters  from the GPS
  {
    gps.encode(g.read());           //This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())          //This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.print("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(), 6);
    
    Serial.print("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");

Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  AccX=Wire.read()<<8|Wire.read();
  AccY=Wire.read()<<8|Wire.read();
  AccZ=Wire.read()<<8|Wire.read();
  Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
  Serial.print("AccX = "); Serial.print(AccX);
  Serial.print(" || AccY = "); Serial.print(AccY);
  Serial.print(" || AccZ = "); Serial.print(AccZ);
  Serial.print(" || Temp = "); Serial.print(Temp/340.00+36.53);
  Serial.print(" || GyroX = "); Serial.print(GyroX);
  Serial.print(" || GyroY = "); Serial.print(GyroY);
  Serial.print(" || GyroZ = "); Serial.println(GyroZ);
  
  delay(100);
  StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 
  root["data1"] = GyroX;
  root["data2"] = GyroY;
  root["data3"] = GyroZ;
  root["lat"]  = gps.location.lat();
  root["longit"]  = gps.location.lng();
if(s.available()>0)
{
 root.printTo(s);
}

  }

}
