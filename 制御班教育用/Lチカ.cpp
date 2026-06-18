#include <Arduino.h>

//LEDを接続したピン
int LED_PIN = 4;

void setup(){
  PinMode(LED_PIN, OUTPUT); //ピンを出力モードに設定する
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  //digitalWriteで、LEDを接続したピンに、第二引数に出力する信号を設定する。
  //HIGHは電圧が高い状態(3.3V)、LOWは電圧が低い状態(0V)。LEDに流れる電流（LEDの明るさ）はオームの法則の通り、電圧の大きさに比例する。
  //delayの引数に入れる時間の単位は1s/1000である。1000を渡すと、1秒待つ。
}


//注意
//マイコンから大きな電流は流せないが、一応保護抵抗をつけること。
//マイコンの出力ピンのうち、-極はGNDというピンである。Groundの略である。ここにLEDの-極をつなぐ。
//保護抵抗（保護抵抗をつけていない場合はLEDのアノード）の方をマイコンのGPIOにつなぐ。

