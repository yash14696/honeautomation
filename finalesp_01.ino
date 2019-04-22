#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


//Firebase connectivity part
#define FIREBASE_HOST "myapplication4-e887b.firebaseio.com"
#define FIREBASE_AUTH "mAyPN4XS7fH1hHI1vuPLGY1ktFAQ1BOM9VXDamg2"
//wifi connectivity part
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "qwerty12"

#define LED 2


void setup() {
      pinMode(LED,OUTPUT);//setting GPIO2 as output pin
      Serial.begin(115200);
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);// connect to wifi
      Serial.print("connecting");
      while(WiFi.status() != WL_CONNECTED)
      {
            Serial.print(".");
            delay(500);
      }
      Serial.println();
      Serial.print("connected: ");
      Serial.println(WiFi.localIP());
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);// connect to firebase
}

int light=0,sen=0,y=0;

void loop()
{
 
     if (Firebase.failed()) //if error occurs
     {
          Serial.print("setting /number failed:");
          Serial.println(Firebase.error());  
          return;
     }
     delay(5);
     if (Serial.available())
         y=Serial.read();
     Firebase.setFloat("bright",y); // update value
     sen=Firebase.getInt("sense"); //get value from the firebase
     if(sen==1)  //auto sensing
     {  
         
         if(y<100)  
              Firebase.setFloat("led",1);
         else
              Firebase.setFloat("led",0);
              
     }   
  
     light=Firebase.getInt("led"); //get value from the firebase
     if (light==1)
     {
         digitalWrite(LED,HIGH); //turn on led
         delay(10);
         return;
     }
  

     else
     {
         digitalWrite(LED,LOW);   //turn off led
         delay(10);
         return;
     }
  
 
}
