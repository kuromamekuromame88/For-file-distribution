
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
