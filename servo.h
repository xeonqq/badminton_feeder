
#include "math.h"
#include <Servo.h>

class FeederServo {
public:
  FeederServo(int pin, int us_min = 1000, int us_max = 2000)
      : us_min_{us_min}, us_max_{us_max} {
    servo.attach(pin, us_min_, us_max_);
  }

  void Reset() { WriteMicroseconds(us_min_); }

  void Write(float percentage) {
    const auto us_input = math::map(percentage, 0.0F, 1.F, us_min_, us_max_);
    // Serial.print("servo write:");
    // Serial.println(us_input);
    WriteMicroseconds(us_input);
  }
  static float GetNetualPositionPercentage() { return 0.5; }

  void WriteMicroseconds(uint16_t us) {
    // Serial.print("servo write:");
    // Serial.println(us);
    servo.writeMicroseconds(ConstrainPWM(us));
  }

  float ReadPercentage() {
    return math::map(static_cast<float>(servo.readMicroseconds()),
                     static_cast<float>(us_min_), static_cast<float>(us_max_),
                     0.F, 1.F);
  }

private:
  int ConstrainPWM(int value) { return constrain(value, us_min_, us_max_); }
  int us_min_;
  int us_max_;
  Servo servo;
};
