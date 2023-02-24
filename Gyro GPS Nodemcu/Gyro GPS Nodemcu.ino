#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>


const char* ssid = "SCT";                  
const char* pass =  "9703316666";


char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1257746 ;
char* readAPIKey = "SK2A7RGCU3ZK098K";
char* writeAPIKey = "AL5SUM7MV6FD4Y5Q";

int dataField1 = 1;                        
int dataField2 = 2;                   
int dataField3 = 3;
int dataField4 = 4;
int dataField5 = 5;
    
WiFiClient client;                

int16_t data1;
int16_t data2; 
int16_t data3;
float data4;
float data5;
 
void setup() {
  
  Serial.begin(9600);
  Serial.println("Connecting to ");
      Serial.println(ssid);
 
      WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
      {
            delay(500);
            Serial.print(".");
      }
      
      Serial.println("WiFi connected");
      ThingSpeak.begin( client );
  s.begin(9600);
  while (!Serial) continue;
 
}
 
void loop() {
  s.write("s");
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
 
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("X-angle: ");
  data1=root["data1"];
  Serial.print(data1);
  Serial.println("");
  Serial.print("Y-angle: ");
  data2=root["data2"];
  Serial.print(data2);
  Serial.println("");
  Serial.print("Z-angle: ");
  data3=root["data3"];
  Serial.print(data3);
  Serial.println("");
  Serial.print("latitude coordinate: ");
  data4=root["latit"];
  Serial.print(data4);
  Serial.println("");
  Serial.print("longitude coordinate: ");
  data5=root["longit"];
  Serial.print(data5);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
  write2Data(channelID,dataField1,data1,dataField2,data2,dataField3,data3,dataField4,data4,dataField5,data5);  
 
}
int write2Data( long Channel,int Field1,int16_t Data1,int Field2,int16_t Data2,int Field3,int16_t Data3,int Field4,float Data4,int Field5,float Data5)
{
     ThingSpeak.setField(dataField1, data1);
     ThingSpeak.setField(dataField2, data2);
     ThingSpeak.setField(dataField3, data3);
     ThingSpeak.setField(dataField4, data4);
     ThingSpeak.setField(dataField5, data5);
     
      int  write1= ThingSpeak.writeField( channelID,dataField1,data1,writeAPIKey ); // Write the data to the channel
      int  write2= ThingSpeak.writeField( channelID,dataField2,data2,writeAPIKey ); // Write the data to the channel
      int  write3= ThingSpeak.writeField( channelID,dataField3,data3,writeAPIKey ); // Write the data to the channel
      int  write4= ThingSpeak.writeField( channelID,dataField4,data4,writeAPIKey );
      int  write5= ThingSpeak.writeField( channelID,dataField4,data5,writeAPIKey );
      
      if ( write1&&write2&&write3&&write4&&write5 )
      {  
            Serial.println( String(data1)  + " written to Thingspeak." );
            Serial.println( String(data2)  + " written to Thingspeak." );
            Serial.println( String(data3)  + " written to Thingspeak." );
            Serial.println( String(data4)  + " written to Thingspeak." );
            Serial.println( String(data5)  + " written to Thingspeak." );
      }
    
     return write1&&write2&&write3&&write4&&write5 ;
}
