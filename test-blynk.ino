//#include <Blynk.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <SoftwareSerial.h> 

#define D0    16;
#define D1    5;
#define D2    4;
#define D3    0;
#define D4    2;
#define D5    14;
#define D6    12;
#define D7    13;
#define D8    15;
#define D9    3;
#define D10   1;

struct System
{
  int cnt= 0;
  int value;
  int Status;
  String Buff_Command;
  String Buffer;
};
struct Blynk_button
{ 
int Pressed  ;
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

#define Key 15
char auth[] = "84417ea530b94d92bc77cf07372b8299";    //AuthToken copy ở Blynk Project
char ssid[] = "boiboi";//"DCI Vietnam";//"boiboi"/;  //Tên wifi
char pass[] = "06060606";//dci@vietnam";//"06060606";     //Mật khẩu wifi
//Flash D3 
char Buff[100]= "12hgj2k31k2jk3k1j23k";
//WidgetLCD lcd(V3);

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); 
  pinMode(16, OUTPUT);  //led onboard  16 D0 
  pinMode(19, INPUT);

}

void loop()
{
  Serial_Manager();
  Blynk.run();
  System_Manager();
 /*
  if(digitalRead(Key))
  {   
   LEDSTT.Status = !LEDSTT.Status;
  }
   
   if(LEDSTT.Status)
   digitalWrite(16,LOW);
   else
   digitalWrite(16,HIGH);
  */
}

void Serial_Manager()
{ 
  int i,cnt_tam;
  if(Serial.available())
   {
     SYSTEM.Buff_Command =   Serial.readStringUntil('\n');
     SYSTEM.Buffer = SYSTEM.Buff_Command.substring(0,3);
     ////////////////////////V1////////////////////////////
     if(SYSTEM.Buffer=="hu:")
      {  
          Serial.print(SYSTEM.Buff_Command);
          Hum.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
          Hum.Buff_Command+="%               ";
      }
      else if(SYSTEM.Buffer=="wl:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Wl.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Wl.Buff_Command += "%";
      }
      /////////////////////////////////////////////////////
      ////////////////////////V0////////////////////////////
      else if(SYSTEM.Buffer=="wt:")
      {
        Serial.print(SYSTEM.Buff_Command);
        WTemp.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        WTemp.Buff_Command+="*C               ";
      }
      else if(SYSTEM.Buffer=="at:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Atp.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Atp.Buff_Command += "*C";
      }
      /////////////////////////////////////////////////////
      ////////////////////////V2////////////////////////////
      else if(SYSTEM.Buffer=="bh:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Bh.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Bh.Buff_Command+="Lux               ";
      }
      else if(SYSTEM.Buffer=="ec:")
      {
        Serial.print(SYSTEM.Buff_Command);
        Ec.Buff_Command = SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length());
        Ec.Buff_Command += "PPM";
      }
      //////////////////////////////////////////////////////
     else if(SYSTEM.Buffer=="mo:")
     {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Mode.Buff_Command = "Auto  ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Mode.Buff_Command = "Manual";
 
     }
     else if(SYSTEM.Buffer=="fa:")
     {
       Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Fan.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Fan.Buff_Command = "Off";
     }
     else if(SYSTEM.Buffer=="lt:")
     {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Light.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Light.Buff_Command = "Off";
     }
     else if(SYSTEM.Buffer=="vi:")
     {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          Valve.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          Valve.Buff_Command = "Off";
    }
    else if(SYSTEM.Buffer=="pa:")
    {
        Serial.print(SYSTEM.Buff_Command);
        if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "1")
          PumpA.Buff_Command = "On ";
        else if(SYSTEM.Buff_Command.substring(3,SYSTEM.Buff_Command.length())== "0")
          PumpA.Buff_Command = "Off";
    }
    else if(SYSTEM.Buffer=="pb:")
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
/////////////////////print LCD//////////////////////////////
  //    lcd_Manager();
 //     lcd.print(0,0, Mode.Buff_Command);
   //   lcd.print(8,0, Fan.Buff_Command);
     //lcd.print(1,0, Valve.Buff_Command);
      //lcd.print(1,8, Light.Buff_Command);
   } 
}
/*
void lcd_Manager()
{
     lcd.clear ();
      if(Mode_OUT.Status == 1)
        lcd.print(0,0,Comand_Mode);
      else if( Mode_OUT.Status == 0)
        lcd.print(0,0,Comand_Mode1);
        
      if(Fan_OUT.Status == 1)
        lcd.print(8,0,Comand_Fan);
      else if( Fan_OUT.Status == 0)
        lcd.print(8,0,Comand_Fan1);
        
      if(Light_OUT.Status == 1)
        lcd.print(0,1,Comand_Light);
      else if(Light_OUT.Status == 0)
        lcd.print(0,1,Comand_Light1);
        
      if(Valve_OUT.Status == 1)
        lcd.print(8,1,Comand_Valve_I);
      else if(Valve_OUT.Status == 0)
        lcd.print(8,1,Comand_Valve_I1);
  
}
*/
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

