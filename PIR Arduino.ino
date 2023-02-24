#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

const char* ssid = "SCT";                  
const char* pass =  "9703316666";
int buttonState=0;

char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1229746 ;
char* readAPIKey = "ZHKHYHIB2SY9MOJE"  ;
char* writeAPIKey = "UFFFF878UW2EAHAN" ;
int dataField1 = 1;
int data1;
int count=0;

WiFiClient client;
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
      pinMode(2,INPUT);
      pinMode(3,INPUT); 

}
void loop(){
   buttonState = digitalRead(2);
  if(buttonState == HIGH){
    Serial.print("count is ");
    Serial.print(count);
    Serial.print("\n");
    count++;
    delay(1000);
  }
  else{
    Serial.print("pushbutton should click for counting \n");
  }
  
      data1=count;
      write2Data(1229217,dataField1,data1);  
}

int write2Data( long Channel,int Field1,int field1Data){

      ThingSpeak.setField(Field1, field1Data);
      
   
      int writeSuccess = ThingSpeak.writeFields(1229217,writeAPIKey);
      if ( writeSuccess )
      {
          Serial.println( String(field1Data) + " member came" );
          
      }
    
      return writeSuccess;
}
