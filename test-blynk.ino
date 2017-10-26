#define BLYNK_PRINT Serial 
#define BLYNK_DEBUG    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>  
String Buffer, a;

char auth[] = "84417ea530b94d92bc77cf07372b8299";    //AuthToken copy ở Blynk Project
char ssid[] = "boiboi";  //Tên wifi
char pass[] = "06060606";     //Mật khẩu wifi


BLYNK_READ(V1) //Blynk app has something on V1
{
   //reading the sensor on A0
  Blynk.virtualWrite(V1,39 ); //sending to Blynk
}

BLYNK_READ(V0) //Blynk app has something on V0
{
   //reading the sensor on A0
  Blynk.virtualWrite(V0, a); //sending to Blynk
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); 
 // pinMode(16, OUTPUT);  //led chân 16 
}

void loop()
{
  Blynk.run();
   if (Serial.available() > 0) 
   {
      Buffer =  Serial.readString(); 
       Serial.println(Buffer);
       a = Buffer.substring(0,5);
       if (a == "hello")
       {
          Serial.println("i love you");
          BLYNK_READ (V0);       
       }
   }

}

