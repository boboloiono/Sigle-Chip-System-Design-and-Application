#include <Wire.h>
#include<LiquidCrystal_I2C.h> //匯入CD_I2C函式庫
LiquidCrystal_I2C lcd(0x27,16,2); //設定LCD位址

int trigPin = 12;                  //Trig Pin
int echoPin = 11;                  //Echo Pin
long duration, cm;
int Led = 2;
const int LedPin = 3;

void setup() {
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出 
  pinMode(echoPin, INPUT);
  pinMode(Led,OUTPUT);
  lcd.init();//初始化LCD
  lcd.backlight();//開啟背光
  lcd.print("E24086064");//在LCD上貼出字串
}
 
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);             // 讀取 echo 的電位
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
 
  cm = (duration/2) / 29.1;         // 將時間換算成距離 cm
  Serial.print(cm);
  Serial.println();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(cm);
  
  analogWrite(10, 255-10*cm);

  if(cm<10){
    digitalWrite(LedPin, HIGH);
  }
  else{
    digitalWrite(LedPin, LOW);
  }
  delay(250);
}
