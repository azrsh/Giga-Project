#include <Arduino.h>
#include "KDSharedObjects.hpp"
#include "KDPIDControl.hpp"

//限界感応法のチューニング
/*
オーバーシュートが収束せず振動が持続する最小のKPを探す
KI=KP/DELTA_TIME
KD＝KP*DELTA_TIME
を用いて値を求める
*/

float KDPIDControl::Calculate(float currentValue, float targetValue)
{
    float currentTime = millis();
    float deltaTime = currentTime - previousUpdateTime;
    if (deltaTime <= 0)
    {
        //もうちょっといい書き方ない？
        previousUpdateTime = currentTime;
        return 0;
    }
    previousUpdateTime = currentTime;

    float currentDifference = currentValue - targetValue;

    integral += (currentDifference + previousDifference) / 2.0f * deltaTime;

    float p = KP * currentDifference;
    float i = KI * integral;
    float d = KD * (currentDifference - previousDifference) / deltaTime;

    previousDifference = currentDifference;

    return constrain(p, MinValue, MaxValue);
}
