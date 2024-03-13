#include  <SoftwareSerial.h> 
#include <Password.h>
SoftwareSerial BTSerial(10, 11); // 宣告10腳位為Arduino的RX 、11為Arduino的 TX
char val;  //儲存接受到的資料變數
Password password = Password("1234");

void setup() {
  Serial.begin(9600);  
  BTSerial.begin(38400); //注意，HC-06要設定成9600(bps)
  //不重複隨機數字
  randomSeed(analogRead(A4));
  Serial.println("請輸入密碼：");
  //不重複隨機數字
  randomSeed(analogRead(A4));
}

void loop() {
  //產生隨機數字
  for(int i =0;i<3;i++){
    ans[i]=random(11)-1;
  }
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val=Serial.read();
    BTSerial.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BTSerial.available()) {
  val=BTSerial.read();
  Serial.print(val);
  }
}
