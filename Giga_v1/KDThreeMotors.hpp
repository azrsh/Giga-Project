#ifndef KD_THREE_MOTORS_h
#define KD_THREE_MOTORS_h

class KDThreeMotors
{
  public:
    static void SetMotorPower(int right, int left, int rear);
    static void Brake();
};

#endif
