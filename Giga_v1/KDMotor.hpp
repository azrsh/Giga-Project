#ifndef KD_MOTOR_h
#define KD_MOTOR_h

template <uint8_t directionPin, uint8_t pwmPin, bool initialDirection>
class KDMotor
{
  private:
    float correctionValue;

  public:
    KDMotor(float correction) : correctionValue(correction){};
    ~KDMotor(){};
    void drive(int power)
    {
        if (!initialDirection)
            power *= -1;

        power *= correctionValue;

        if (power >= 0)
        {
            digitalWriteFast(directionPin, HIGH);
        }
        else
        {
            digitalWriteFast(directionPin, LOW);
            power = -power;
        }

        analogWrite(pwmPin, power);
    };
};

#endif