#include "math.h"
#include <Servo.h>

class BrushlessMotor {
public:
  BrushlessMotor(uint8_t pin) { esc_.attach(pin); }

  void RunSpeed(float percentage) {
    const int speed_microseconds =
        Map(percentage, 0.F, 1.F, min_microseconds_, max_microseconds_);
    esc_.writeMicroseconds(speed_microseconds);
  }

  void Calibrate() {
    esc_.writeMicroseconds(max_microseconds_);
    delay(1000); // wait 1s
    esc_.writeMicroseconds(min_microseconds_);
  }

private:
  const uint16_t max_microseconds_{2000};
  const uint16_t min_microseconds_{1000};
  Servo esc_;
};
