#pragma once

#include <Arduino.h>

namespace MD {
  class DRV8833 {
    public:
      DRV8833(int AI1, int AI2, int BI1, int BI2) {
        Ain1 = AI1;
        Ain2 = AI2;
        Bin1 = BI1;
        Bin2 = BI2;
      }

      void begin(int st = 0) {
        stp = st;
        if (stp > 12) stp = 12;

        ledcSetup(stp,     1000, 8);
        ledcSetup(stp + 1, 1000, 8);
        ledcSetup(stp + 2, 1000, 8);
        ledcSetup(stp + 3, 1000, 8);

        ledcAttachPin(Ain1, stp);
        ledcAttachPin(Ain2, stp + 1);
        ledcAttachPin(Bin1, stp + 2);
        ledcAttachPin(Bin2, stp + 3);
        stop();
      }

      inline int pmap(int percent) {
        return map(constrain(percent, 0, 100);, 0, 100, 0, 255);
      }

      void run(int power) {
        power = constrain(power, -100, 100);
        int pwm = pmap(abs(power));

        if (power > 0) {
          ledcWrite(stp, pwm);
          ledcWrite(stp + 1, 0);
          ledcWrite(stp + 2, 0);
          ledcWrite(stp + 3, pwm);
        } else if (power < 0) {
          ledcWrite(stp, 0);
          ledcWrite(stp + 1, pwm);
          ledcWrite(stp + 2, pwm);
          ledcWrite(stp + 3, 0);
        } else {stop();}
      }

      void stop() {
        ledcWrite(stp, 0);
        ledcWrite(stp + 1, 0);
        ledcWrite(stp + 2, 0);
        ledcWrite(stp + 3, 0);
      }

      void brake() {
        ledcWrite(stp, 255);
        ledcWrite(stp + 1, 255);
        ledcWrite(stp + 2, 255);
        ledcWrite(stp + 3, 255);
      }

    private:
      int stp = 0;
      int Ain1, Ain2, Bin1, Bin2;
  };
}
