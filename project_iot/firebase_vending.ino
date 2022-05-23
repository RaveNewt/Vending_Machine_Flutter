#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
                          
#define FIREBASE_HOST "iot-vending-default-rtdb.firebaseio.com"                          // database URL 
#define FIREBASE_AUTH "qoiihaoe5dbiZnoaADY8RV3FbjETTrlZKfd9uJRU"             // secret key

#define WIFI_SSID "SMY"                                                
#define WIFI_PASSWORD "souma2409"   

  String myString;
  
 
 bool light;
 bool light2;
 const int PIN = 14;
 const int PIN2 = 12;
 const int ldrPin = A0;
 
 //unsigned long previousMillis=0;//for adding a timelimit after which the data will be read
 //const long interval=10000;
void setup()
{
  lcd.init(); 
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(ldrPin, INPUT);
  Serial.begin(115200);
  delay(500);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
   Serial.println("Vending Machine");
  delay(1000);
}
     
void loop()
{
  digitalWrite(14,HIGH);
  digitalWrite(12,HIGH);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Vending Machine    ");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("SilahkanMasukkan");
  lcd.setCursor(0,1);
  lcd.print("Uang Anda     "); 
  delay(2000);
   

 moneyRead();
 
}
void moneyRead(){
  int ldrStatus = analogRead(ldrPin);
  Serial.println(ldrStatus);
  if(ldrStatus < 1024){
    lcd.setCursor(0,0);
    lcd.print("Uang terdeteksi ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    delay(3000);
    vending();
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Uang Tidak      ");
    lcd.setCursor(0,1);
    lcd.print("Terdeteksi      ");
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("SilahkanMasukkan");
    lcd.setCursor(0,1);
    lcd.print("Uang Anda       ");
    delay(3000);
  }
  moneyRead();
}
void vending(){
  lcd.setCursor(0,0);
  lcd.print("Silahkan pilih  ");
  lcd.setCursor(0,1);
  lcd.print("Snack Anda      ");   
  delay(5000);
  
  light=Firebase.getBool("Light/Switch");
  light2=Firebase.getBool("Light2/Switch");
  Serial.println(light);
  Serial.println(light2);
  
  if(light2 == false){
      vend1();
      delay(200);
      lcd.setCursor(0,0);
      lcd.print("Silahkan Ambil  ");
      lcd.setCursor(0,1);
      lcd.print("Snack Anda   ;   ");
      delay(10000);
      moneyRead();
    }
    else{
      vend2(); 
      delay(200);
      lcd.setCursor(0,0);
      lcd.print("Silahkan Ambil");
      lcd.setCursor(0,1);
      lcd.print("Snack Anda     ");
      delay(10000);
      moneyRead();
    }
}
void vend1(){
  digitalWrite(14,LOW);
  delay(460);
  digitalWrite(14,HIGH);    
}
 void vend2(){
  digitalWrite(12,LOW);
  delay(460);
  digitalWrite(12,HIGH);
}
