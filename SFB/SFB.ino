//Smart Fish Bowl

#include <SoftwareSerial.h>  //Bluetooth library
#include <math.h>  //Relay library
#include <Arduino-Temperature-Control-Library-master.h>  //Temperature Sensor ds18b20 library
#include <OneWire-master.h>  //Temperature Sensor ds18b20 library

#define bRx 11 //Bluetooth Pin RX
#define bTx 12 //Bluetooth Pin TX
SoftwareSerial BtSerial(bTx,bRx);

char Input_ModeKey;  //選擇模式（手動/自動）
char Input_EqKey;  //選擇設備Equipment

//各設備狀態預設為「關」
int Eq_Stat_Heater = 2;  //設備「加溫器」開關狀態，2表示關，1表示開
int Eq_Stat_AirBump = 2;  //設備「空氣幫浦」開關狀態，2表示關，1表示開
int Eq_Stat_WaterFilter = 2;  //設備「魚缸過濾器」開關狀態，2表示關，1表示開
int Eq_Stat_AutoFeeder = 2;  //設備「自動餵食器」開關狀態，2表示關，1表示開
int Eq_Stat_LEDLamp = 2;  //設備「LED燈」開關狀態，2表示關，1表示開
int pin_RelayHeater = 13;  //設備「加溫器_繼電器」腳位13
int pin_RelayAirBump = 10;  //設備「空氣幫浦_繼電器」腳位10
int pin_RelayWaterFilter = 9;  //設備「魚缸過濾器_繼電器」腳位9
int pin_RelayAutoFeeder = 8;  //設備「自動餵食器_繼電器」腳位8
int pin_RelayLEDLamp = 7;  //設備「LED燈_繼電器」腳位7

void setup() {
  Serial.begin(9600);
  BtSerial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  BtSerial.println("歡迎使用Smart Fish Bowl系統");  //顯示內容：歡迎使用Smart Fish Bowl系統
}

void loop() {
  Menu_Mode();
}

void Menu_Mode()  //主選單選擇模式副程式
{
  //if(Serial.available())
  if(BtSerial.available())
  {
    //Input_ModeKey = Serial.read();
    Input_ModeKey = BtSerial.read();
    delay(5);
    BtSerial.println("選擇手動或自動模式： 1.手動 2.自動");  //顯示內容：選擇手動或自動模式： 1.手動 2.自動
    BtSerial.println(Input_ModeKey);
    if(Input_ModeKey=='1')
    {
      BtSerial.println("手動模式");  //顯示內容：手動模式
      HandMode();  //手動模式
    }
    /*else if(Input_ModeKey=='2')
    {
      BtSerial.println("自動模式");  //顯示內容：自動模式
      AutoMode();  //自動模式
    }*/
    else  //偵錯
    {
      BtSerial.println("Please try again.");  //請重新輸入
      Menu_Mode();
    }
  }
}

void HandMode()
{
  //if(Serial.available())
  if(BtSerial.available())
  {
    //Input_EqKey = Serial.read();
    Input_EqKey = BtSerial.read();
    delay(5);
    BtSerial.println("選擇設備：");  //顯示內容：選擇設備
    BtSerial.println("1.加溫器");
    BtSerial.println("2.空氣幫浦");
    BtSerial.println("3.魚缸過濾器");
    BtSerial.println("4.自動餵食器");
    BtSerial.println("5.LED燈");
    BtSerial.println(Input_EqKey);
    if(Input_EqKey=='1')  //加溫器
    {
      BtSerial.println("選擇設備：加溫器");  //顯示內容：選擇設備：加溫器
      Eq_Heater();  //加溫器副程式
      HandMode();
    }
    else if(Input_EqKey=='2')  //空氣幫浦
    {
      BtSerial.println("選擇設備：空氣幫浦");  //顯示內容：選擇設備：空氣幫浦
      Eq_AirBump();  //空氣幫浦副程式
      HandMode();
    }
    else if(Input_EqKey=='3')  //魚缸過濾器
    {
      BtSerial.println("選擇設備：魚缸過濾器");  //顯示內容：選擇設備：魚缸過濾器
      Eq_WaterFilter();  //魚缸過濾器副程式
      HandMode();
    }
    else if(Input_EqKey=='4')  //自動餵食器
    {
      BtSerial.println("選擇設備：自動餵食器");  //顯示內容：選擇設備：自動餵食器
      Eq_AutoFeeder();  //自動餵食器副程式
      HandMode();
    }
    else if(Input_EqKey=='5')  //LED燈
    {
      BtSerial.println("選擇設備：LED燈");  //顯示內容：選擇設備：LED燈
      Eq_LEDLamp();  //LED燈副程式
      HandMode();
    }
    else  //偵錯
    {
      BtSerial.println("Please try again.");  //顯示內容：請重新輸入
      HandMode();
    }
  }
  else
  {
    HandMode();
  }
}

/*void AutoMode()
{
  //自動模式
}*/

void Eq_Heater()  //加溫器副程式
{
  //if(Serial.available())
  if(BtSerial.available())
  {
    //Eq_Stat_Heater = Serial.read();
    Eq_Stat_Heater = BtSerial.read();
    delay(5);
    BtSerial.println("選擇開關：");  //顯示內容：選擇開關：1.開 2.關
    if(Eq_Stat_Heater=='1')
    {
      digitalWrite(pinOut, HIGH);
    }
    else if(Eq_Stat_Heater=='2')
    {
      //
    }
  }
  else
  {
    Eq_Heater();
  }
}

