#include <Wire.h>
#include <LiquidCrystal_I2C.h> //匯人CD_I2C函式庫
#include <Password.h>
#include  <SoftwareSerial.h> 
SoftwareSerial BTSerial(10, 11); // 宣告10腳位為Arduino的RX 、11為Arduino的 TX
char val;  //儲存接受到的資料變數
Password password = Password("0020");
LiquidCrystal_I2C lcd(0x27,16,2);//設定LCD位址

void setup() {
  lcd.init(); //初始化LCD
  lcd.backlight(); //開啟背光
  Serial.begin(9600);
  BTSerial.begin(38400); //注意，HC-06要設定成9600(bps)
  for(int i=0; i<5; i++)
    pinMode(Led[i], OUTPUT);
}

void loop(){
  if (BTSerial.available()) {
    val=BTSerial.read();
    Serial.print(val);
    switch(val){
      case'A':True_OR_false();password.reset();temp[0]=0;temp[1]=0;temp[2]=0;temp[3]=0;i=0;break;
      default:KeyNumber(val);
    }
  }
}
//判斷密碼是否正確
void True_OR_false(){
  password.append(temp[0]);//add 1 to the guessed password
  password.append(temp[1]);//add 2 to the guessed password
  password.append(temp[2]);//add 3 to the guessed password
  password.append(temp[3]);//add 4 to the guessed password
  lcd.setCursor (0, 0);
  lcd.println( password.evaluate()?"BINGO！":"ERRO\n 請重新輸入密碼" );
  lcd.clear();
}
