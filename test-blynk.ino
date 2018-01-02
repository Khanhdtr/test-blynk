//#include <Blynk.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h> 

#define LED_STT    16         //led on board


#define VI      5      //D1
#define VO      4      //D2
#define PB      0      //D3
#define LIGHT   2      //D4
#define PA      14     //5
#define PO      12     //D6
#define FAN     13    //D7
/*
#define D8    15;
#define D9    3;
#define D10   1;
*/
struct System
{
  int cnt= 0;
  int value;
  int Status;
  String Buff_Command;
};
struct Blynk_button
{ 
int Pressed =0 ;
int Wait_Press = 0;
int Press ;
int Status;
String Buff_Command;
};
struct Blynk_button Mode;
struct Blynk_button Light;
struct Blynk_button PumpA;
struct Blynk_button Valve;
struct Blynk_button Fan;
struct Blynk_button PumpB;

struct Blynk_button VI_F;
struct Blynk_button FAN_F;
struct System LEDSTT;
struct System SYSTEM;
struct System WTemp;
struct System Hum;
struct System Bh;
struct System Ec;
struct System Wl;
struct System Atp;
struct System Hum_Wl;
struct System WTemp_Atp;
struct System Bh_Ec;
struct System Mode_OUT;

//{"mo:1","po:1","pa:1","pb:0","fa:1","lt:1","vi:1","vo:1","wtp:29.5","bh:56321","ec:4021","hu:42","at:26","wl:1"}

char Comand_Fan[20] =     "Fan ON";
char Comand_Fan1[20] =     "Fan OFF";
char Comand_Mode[20] =    "Auto";
char Comand_Mode1[20] =    "Manual";
char Comand_Light[20] =   "Light ON";
char Comand_Light1[20] =   "Light OFF";
char Comand_Valve_I[20] = "Valve ON";
char Comand_Valve_I1[20] = "Valve OFF";


char auth[] = "84417ea530b94d92bc77cf07372b8299";    //AuthToken copy ở Blynk Project
char ssid[] = "boiboi";//"boiboi"/;  //Tên wifi
char pass[] = "06060606";//"06060606";     //Mật khẩu wifi
//Flash D3 
char Buff[100]= "12hgj2k31k2jk3k1j23k";
//WidgetLCD lcd(V3);
long lastDebounceTime = 0;  
long debounceDelay = 50;
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); 
  pinMode(LED_STT, OUTPUT);  //led onboard  16 D0 
  pinMode(LIGHT, INPUT);
  pinMode(VI, INPUT);
  pinMode(VO, INPUT);
  pinMode(PA, INPUT);
  pinMode(PB, INPUT);
  pinMode(PO, INPUT);
  pinMode(FAN,INPUT);
}

void loop()
{
  Serial_Manager();
  //Blynk.run();
  System_Manager();
  FeedBack_Manager();
  Serial.println("Wrong str");

  
}

void Serial_Manager()
{ 
  int i,cnt_tam;
  if(Serial.available())
   {
     SYSTEM.Buff_Command =   Serial.readStringUntil('\n');
     ////////////////////////V1////////////////////////////
     if(SYSTEM.Buff_Command.substring(0,3)=="hu:")
      {  
          Serial.print(SYSTEM.Buff_Command);
          Hum.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
          Hum.Buff_Command+="%               ";
      }
      else if(SYSTEM.Buff_Command.substring(0,3)=="wl:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Wl.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Wl.Buff_Command += "%";
      }
      /////////////////////////////////////////////////////
      ////////////////////////V0////////////////////////////
      else if(SYSTEM.Buff_Command.substring(0,3)=="wt:")
      {
        Serial.print(SYSTEM.Buff_Command);
        WTemp.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        WTemp.Buff_Command+="*C               ";
      }
      else if(SYSTEM.Buff_Command.substring(0,3)=="at:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Atp.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Atp.Buff_Command += "*C";
      }
      /////////////////////////////////////////////////////
      ////////////////////////V2////////////////////////////
      else if(SYSTEM.Buff_Command.substring(0,3)=="bh:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Bh.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Bh.Buff_Command+="Lux               ";
      }
      else if(SYSTEM.Buff_Command.substring(0,3)=="ec:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Ec.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Ec.Buff_Command += "PPM";
      }
      //////////////////////////////////////////////////////
     else if(SYSTEM.Buff_Command.substring(0,3)=="mo:")
     {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Mode.Buff_Command = "Auto  ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Mode.Buff_Command = "Manual";
 
     }
     else if(SYSTEM.Buff_Command.substring(0,3)=="fa:")
     {
       Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Fan.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Fan.Buff_Command = "Off";
     }
     else if(SYSTEM.Buff_Command.substring(0,3)=="lt:")
     {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Light.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Light.Buff_Command = "Off";
     }
     else if(SYSTEM.Buff_Command.substring(0,3)=="vi:")
     {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Valve.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Valve.Buff_Command = "Off";
    }
    else if(SYSTEM.Buff_Command.substring(0,3)=="pa:")
    {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          PumpA.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          PumpA.Buff_Command = "Off";
    }
    else if(SYSTEM.Buff_Command.substring(0,3)=="pb:")
    {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          PumpB.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          PumpB.Buff_Command = "Off";
    }
     else
      Serial.println("Wrong str");

//////////////////////////////print Value////////////////////
      Hum_Wl.Buff_Command = Hum.Buff_Command+Wl.Buff_Command;
      WTemp_Atp.Buff_Command= WTemp.Buff_Command+Atp.Buff_Command;
      Bh_Ec.Buff_Command= Bh.Buff_Command+Ec.Buff_Command;
      Mode_OUT.Buff_Command = Mode.Buff_Command + "   "+Fan.Buff_Command+ "   "+Light.Buff_Command+"   "+Valve.Buff_Command+"   "+PumpA.Buff_Command+"   "+PumpB.Buff_Command;
      Blynk.virtualWrite(V1, Hum_Wl.Buff_Command);
      Blynk.virtualWrite(V0, WTemp_Atp.Buff_Command);
      Blynk.virtualWrite(V2, Bh_Ec.Buff_Command);
      Blynk.virtualWrite(V3, Mode_OUT.Buff_Command);

   } 
}

void FeedBack_Manager()
{
  
   FAN_F.Wait_Press = digitalRead(FAN); //Press switch Mode
   if(FAN_F.Wait_Press==0 && FAN_F.Pressed ==0)
   {
     Serial.print("Fan Off\0");
     digitalWrite(LED_STT, 0);
     FAN_F.Pressed = 1;
   }
   else if(FAN_F.Wait_Press==1&&FAN_F.Pressed ==1)
   {
     Serial.print("Fan On\0");
     digitalWrite(LED_STT, 1);
     FAN_F.Pressed = 0;
   }
}  


//////////////////////////////// Manager button from app Blynk/////////////////////////
void System_Manager()
{
  if(Mode.Status)
  {
    Serial.print("Mode:Switch\0");
    Mode.Status = 0;
  }  
  if(Light.Status)
  {
    Serial.print("Light:Switch\0");
    Light.Status = 0;
  }
  if(PumpA.Status)
  {
    Serial.print("Pump_A:Switch\0");
    PumpA.Status = 0;
  }
  if(PumpB.Status)
  {
    Serial.print("Pump_B:Switch\0");
    PumpB.Status = 0;
  }
  if(Valve.Status)
  {
    Serial.print("Valve_I:Switch\0");
    Valve.Status = 0;
  }
  if(Fan.Status)
  {
    Serial.print("Fan:Switch\0");
    Fan.Status = 0;
  }

}
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////Get button from app Blynk////////////////////////
BLYNK_WRITE(V6)
{
   Mode.Press = param.asInt();
   if(Mode.Press)
      Mode.Status = 1;        
}
BLYNK_WRITE(V7)
{
   Light.Press = param.asInt();
   if(Light.Press)
      Light.Status = 1;      
}
BLYNK_WRITE(V8)
{
   PumpA.Press = param.asInt();
   if(PumpA.Press)
      PumpA.Status = 1;      
}
BLYNK_WRITE(V9)
{
   Valve.Press = param.asInt();
   if(Valve.Press)
      Valve.Status = 1;      
}
BLYNK_WRITE(V10)
{
   Fan.Press = param.asInt();
   if(Fan.Press)
      Fan.Status = 1;      
}
BLYNK_WRITE(V4)
{
   PumpB.Press = param.asInt();
   if(PumpB.Press)
      PumpB.Status = 1;        
}
/////////////////////////////////////////////////////////////////////////////////

