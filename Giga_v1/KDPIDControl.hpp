#ifndef KD_PID_Control_h
#define KD_PID_Control_h

class KDPIDControl
{
  public:
    KDPIDControl(float kp, float ki, float kd, float minValue, float maxValue) : KP(kp), KI(ki), KD(kd), MinValue(minValue), MaxValue(maxValue) {}

    float Calculate(float currentValue, float targetValue);

  private:
    const float KP;
    const float KI;
    const float KD;
    const float MinValue;
    const float MaxValue;
    float previousDifference = 0.0f;
    float previousUpdateTime = 0.0f;
    float integral = 0.0f;
};

#endif
