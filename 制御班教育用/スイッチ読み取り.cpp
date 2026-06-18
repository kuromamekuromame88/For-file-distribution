#include <Arduino.h>

int BUTTON_PIN = 5;//ボタンを接続したピン

void setup(){
  pinMode(BUTTON_PIN, INPUT_PULLUP); //入力モード（プルアップ）に設定する
  //プルアップとは
  //プルアップとは、ピンの端子と+極の電源の間に内部的に抵抗をつけた状態である。ピンの電圧をHIGHの状態をデフォルトとするモード。
  //つまり、ボタンの片方の端子をGNDに接続して、押されたときにピンがLOWになることを検知すればよい。

  Serial.begin(115200);
  //シリアル通信の設定。引数の数値は通信速度。

  //シリアルモニタを使用して、マイコンから実行中の変数の値やその他のメッセージをPCなどに送信することができる。応用するとその逆もできる。
}

void loop(){
  if(!digitalRead(BUTTON_PIN)) Serial.println("ボタンが押されました");
}
