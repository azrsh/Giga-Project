#include <Arduino.h>
#include "KDSharedObjects.hpp"
#include "KDHardwere.hpp"
#include "KDThreeMotors.hpp"

/*INLINE*/ void KDThreeMotors::SetMotorPower(int right, int left, int rear)
{
    //出力比を保って最大値に補正
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

    //すべてのモータを正転させると時計回りに旋回するようにする
    rear *= -1;

    //安全のためどの場合もLOWから入るようにしてる
    if (right >= 0)
    {
        digitalWriteFast(KDHardwere::RightMotorDirectionPin, HIGH);
    }
    else
    {
        digitalWriteFast(KDHardwere::RightMotorDirectionPin, LOW);

        right = -right;
    }

    if (left >= 0)
    {
        digitalWriteFast(KDHardwere::LeftMotorDirectionPin, HIGH);
    }
    else
    {
        digitalWriteFast(KDHardwere::LeftMotorDirectionPin, LOW);

        left = -left;
    }

    if (rear >= 0)
    {
        digitalWriteFast(KDHardwere::RearMotorDirectionPin, HIGH);
    }
    else
    {
        digitalWriteFast(KDHardwere::RearMotorDirectionPin, LOW);

        rear = -rear;
    }

    analogWrite(KDHardwere::RightMotorPwmPin, right);
    analogWrite(KDHardwere::LeftMotorPwmPin, left);
    analogWrite(KDHardwere::RearMotorPwmPin, rear);
}

/*INLINE*/ void KDThreeMotors::Brake()
{
    analogWrite(KDHardwere::RightMotorPwmPin, 0);
    analogWrite(KDHardwere::LeftMotorPwmPin, 0);
    analogWrite(KDHardwere::RearMotorPwmPin, 0);
}
