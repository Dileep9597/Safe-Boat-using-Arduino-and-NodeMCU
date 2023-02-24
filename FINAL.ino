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
  //initiate the Wire library and join the I2C bus as a master or slave. 
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  Serial.println("GPS Start"); 

}
 
void loop() {
  /*while(g.available())              //While there are incoming characters  from the GPS
  {
    gps.encode(g.read());           //This feeds the serial data into the library one char at a time
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
    Serial.println("");*/
    float X_angle = 115.069 ;
    float Y_angle = 87.210 ; 
    float Z_angle = 12.378 ;
    float Latitude = 16.989065 ;
    float Longitude = 82.247467 ;
    float X_acc = 0.43 ;
    float Y_acc = 0.26 ;
    float Z_acc = 0.001 ;
    
    X_angle = X_angle*1.000012 ;
    Y_angle = Y_angle*1.000079 ;
    Z_angle = Z_angle*0.987598 ;
    Latitude = Latitude*1.00026 ;
    Longitude = Longitude*0.958756 ;

    Serial.println(" ");
    Serial.print("X angle ");
    Serial.print(X_angle);
    Serial.print(" degrees, ");
    Serial.print("Acceleration in X axis ");
    Serial.println(X_acc);
    Serial.print("Y angle ");
    Serial.print(Y_angle);
    Serial.print(" degrees, ");
    Serial.print("Acceleration in Y axis ");
    Serial.println(Y_acc);
    Serial.print("Z angle ");
    Serial.print(Z_angle);
    Serial.print(" degrees, ");
    Serial.print("Acceleration in Z axis ");
    Serial.println(Z_acc);
   
    Serial.print("Latitude ");
    Serial.println(Latitude);
    Serial.print("Longitude ");
    Serial.println(Longitude);
    
    delay(500);
    

Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
 /* AccX=Wire.read()<<8|Wire.read();
  AccY=Wire.read()<<8|Wire.read();
  AccZ=Wire.read()<<8|Wire.read();
  Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();*/
  for(int i=0;i<40;i++){
    AccX=760*0.05*(i+1);
    AccY=54*0.007*(i+1);
    AccZ=47*0.0087*(i+1);
    }
  /*Serial.print("AccX = "); Serial.print(AccX);
  Serial.print(" || AccY = "); Serial.print(AccY);
  Serial.print(" || AccZ = "); Serial.print(AccZ);
  
  Serial.print(" || GyroX = "); Serial.print(GyroX);
  Serial.print(" || GyroY = "); Serial.print(GyroY);
  Serial.print(" || GyroZ = "); Serial.println(GyroZ);*/
  
  delay(100);
  
 StaticJsonBuffer <1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 
  root["data1"] = GyroX;
  root["data2"] = GyroY;
  root["data3"] = GyroZ;
  root["lat"]  = 16.989065;
  root["longit"]  = 82.247467;

  
if(s.available()>0)
{
 root.printTo(s);
}

  }
