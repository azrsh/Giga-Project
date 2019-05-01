#ifndef KD_THREE_MOTORS_h
#define KD_THREE_MOTORS_h

#include "KDModeMacros.hpp"
#include "KDDataStructure.hpp"

template <class RightMotor, class LeftMotor, class RearMotor>
class KDThreeMotors
{
  private:
    RightMotor *rightMotor;
    LeftMotor *leftMotor;
    RearMotor *rearMotor;

  public:
    KDThreeMotors(RightMotor *rightMotor, LeftMotor *leftMotor, RearMotor *rearMotor) : rightMotor(rightMotor), leftMotor(leftMotor), rearMotor(rearMotor){};
    ~KDThreeMotors(){};
    void drive(int right, int left, int rear)
    {
#ifdef SAFE_MODE
        //ここでやるべきではない
        static_assert(KDSharedObjects::MaximamMotorPower < 256, "ERROR：KDSharedObjects::MaximamMotorPower（モータ出力の最大値）がpwm出力の最大値を超えています");

        int horizontalMax = max(abs(right), abs(right));
        int maxPower = max(horizontalMax, rear);
        if (maxPower > KDSharedObjects::MaximamMotorPower)
        {
            float rate = (float)KDSharedObjects::MaximamMotorPower / (float)maxPower;
            right *= rate;
            left *= rate;
            rear *= rate;
        }
#endif

        rightMotor->drive(right);
        leftMotor->drive(left);
        rearMotor->drive(rear);
    };
    void brake()
    {
        rightMotor->brake();
        leftMotor->brake();
        rearMotor->brake();
    };
};

#endif
