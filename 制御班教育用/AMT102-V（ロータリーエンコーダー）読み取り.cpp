
#include <Arduino.h>

//エンコーダーのライブラリ
#include <ESP32Encoder.h>
//https://github.com/madhephaestus/ESP32Encoder/tree/masterをiniに書くかzipをlibフォルダに投入


#define A 4
#define B 5

/*
ピン設定
A相 4
B相 5
G GND
5V 3V3
*/

//
ESP32Encoder encoder;

/*
  関数                1回転あたりのカウント数
  attachSingleEdge(A,B)  2048
  attachHalfQuad(A,B)    4096
  attachFullQuad(A,B)    8192

  DIPスイッチと分解能の関係
  DIPスイッチ 分解能
  0000        2048 <=このライブラリではこの分解能を使用するため、すべてのDIPスイッチをoffにしておく
  0010        1024
  1000        1000
  0100         800
  0001         512
  1010         500
  0110         400
  1100         384
  0011         256
  1001         250
  0101         200
  1110         192
  1011         125
  0111         100
  1101          96
  1111          48
*/

void setup() {
  //シリアルの初期化
  Serial.begin(115200);
  
  //動作モードとピンを設定
  encoder.attachHalfQuad(A,B);

  //カウンタをクリア（現在の位置を0にする）
  encoder.setCount(0);
}

void loop() {
  //取得して変換した値を出力
  Serial.println(encoder.getCount()*360/4096);
}
