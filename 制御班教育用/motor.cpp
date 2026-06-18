//MD10CまたはMD30Cを制御するサンプルコード

#include <Arduino.h>

int Channel = 0; //チャンネル（PWMの出口）

int Ppwm = 5; //PWMを出力するGIPOピンのピン番号

int Pdir = 6; //(モーターの回転方向を決める制御信号)のGPIOピンの番号

void setup(){
  ledcSetup(Channel, 20000, 8); //ledcSetup(チャンネル, 周波数, 分解能);
  ledcAttachPin(Ppwm, Channel);
  pinMode(Pdir, OUTPUT); //OUTPUTにすることでそのGPIOピンを出力モードにできる
}

void loop(){
  digitalWrite(Pdir, HIGH); //第2引数をHIGHかLOWにすることで回転方向を切り替える
  ledcWrite(Channel, 255); //第2引数によってモーターの回転速度が変わる
  //↑ledcSetupで分解能を8ビットにしたので、0~255の範囲で出力できる
}
