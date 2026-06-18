//一部関係のないコメントなどありますが各自整理してください。

#include <Arduino.h>

#include <PS4Controller.h>

//#include "esp_mac.h"
/*

#include "cytron_dcmd.hpp"

Motor1
dir 18
pwm 19

Motor2
dir 17
pwm 5

Motor3
dir 16
pwm 4
*/

class motor{
  public:
    motor(int pwm, int dir, int chan){
      Ppwm=pwm;
      Pdir=dir;
      Chan=chan;
    }

    void begin(){
      pinMode(Pdir, OUTPUT);
      ledcSetup(Chan, 20000, 8);
      ledcAttachPin(Ppwm, Chan);
    }

    void run(int power, int dir){
      //％で出力を指定
      power = (constrain(power, -100, 100)*255)/ 100;
      digitalWrite(Pdir, dir);
      ledcWrite(Chan, power);
    }
  private:
    int Ppwm, Pdir, Chan;
};


motor A(19, 18, 0);
motor B(5, 22, 1);//2217
motor C(4, 23, 2);//2316


double thr = 0.8660254037844386;

void move(double Vx, double Vy, double Vtheta){
  double kRot = 1.0;

  double V1 = Vx + kRot*Vtheta;
  double V2 = -0.5*Vx + thr*Vy + kRot*Vtheta;
  double V3 = -0.5*Vx - thr*Vy + kRot*Vtheta;

  double maxv = max(fabs(V1), max(fabs(V2), fabs(V3)));

  if(maxv > 1.0){
    V1 /= maxv;
    V2 /= maxv;
    V3 /= maxv;
  }

  Serial.printf(
    "V1=%f V2=%f V3=%f\n",
    V1, V2, V3
  );

  A.run(fabs(V1)*100, V1>0);
  B.run(fabs(V2)*100, V2>0);
  C.run(fabs(V3)*100, V3>0);
}

void setup() {
  Serial.begin(115200);

  PS4.begin();

  A.begin();
  B.begin();
  C.begin();

  
  A.run(10, -1);
  B.run(10, -1);
  C.run(10, -1);
  while(true);

  move(0, 0, 0);

  //MACアドレスを調べる
  /*Serial.println("-----------------");
  uint8_t macBT[6];
  esp_read_mac(macBT, ESP_MAC_BT);
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", macBT[0], macBT[1], macBT[2], macBT[3], macBT[4], macBT[5]);
  while(true);*/
}

void loop() {
  if(PS4.isConnected()){
    double Lx,Ly,Rx;
    Lx = PS4.LStickX();
    Ly = PS4.LStickY();
    Rx = PS4.RStickX();
    
    Lx = abs(Lx)<20?0:-Lx/127.0;
    Ly = abs(Ly)<20?0:Ly/127.0;
    Rx = abs(Rx)<20?0:-Rx/127.0;

    //Serial.printf("Lx: %f Ly: %f Rx: %f\n", Lx, Ly, Rx);
    
    move(Lx, Ly, Rx);
  }else{
    move(0,0,0);
  }
}





