#include <Arduino.h>
#include <digitalWriteFast.h>
#include "IRSensorCtrl.hpp"

constexpr uint8_t IRSensorCtrl::BallSensorPins[NumberOfBallSensors];
constexpr float IRSensorCtrl::UnitVectorX[NumberOfBallSensors];
constexpr float IRSensorCtrl::UnitVectorY[NumberOfBallSensors];

//センサの状態を格納する型
//すべてのセンサのパルス幅を取得
sensorInfo_t IRSensorCtrl::GetAllSensorPulseWidth(float pulseWidth[NumberOfBallSensors])
{
    uint16_t timeLimit = IRBallWaveformModeA;

    // 実験用データを格納する構造体
    sensorInfo_t sensorInfo;

    // pulseWidth[]は加算計算用変数なので最初に初期化する
    for (int i = 0; i < NumberOfBallSensors; i++)
    {
        pulseWidth[i] = 0;
    }

    // do-whileで時間(833us)を監視しながらセンサの読み込み
    // timeLimit = IRのパルスの周期
    const unsigned long startTime_us = micros();
    do
    {
        //全センサを同時読み
        for (int i = 0; i < NumberOfBallSensors; i++)
        {
            if (GetSensorValue(i) == false)
            {
                pulseWidth[i] += deltaPulseWidth;
            }
        }
    } while ((micros() - startTime_us) < timeLimit);

    // ベクトル計算のみでセンシングを行うのであれば以下の実装は不要
    sensorInfo.activeSensors = 0;   // ボールに反応しているセンサの個数
    sensorInfo.maxPulseWidth = 0;   // 一番反応の強いセンサのパルス幅
    sensorInfo.maxSensorNumber = 0; // 一番反応の強いセンサの番号
    for (int i = 0; i < NumberOfBallSensors; i++)
    {
        if (pulseWidth[i] > 0)
        {
            sensorInfo.activeSensors += 1;
        }
        if (pulseWidth[i] > sensorInfo.maxPulseWidth)
        {
            sensorInfo.maxPulseWidth = pulseWidth[i];
            sensorInfo.maxSensorNumber = i;
        }
    }

    return sensorInfo;
}

//パルス幅から直交座標系ベクトルに変換
vectorXY_t IRSensorCtrl::CaliculateVectorXYFromPulseWidth(float *pulseWidth) const
{
    vectorXY_t result = {0, 0};
    float pulseWidthSum = 0;
    for (int i = 0; i < NumberOfBallSensors; i++)
    {
        result.x += pulseWidth[i] * UnitVectorX[i];
        result.y += pulseWidth[i] * UnitVectorY[i];
        pulseWidthSum += pulseWidth[i];
    }

    float sqrtRadius = sqrt(pulseWidthSum);
    float cube = pulseWidthSum * sqrtRadius;
    float rate;
    if (cube > 0.0001)
        rate = 1 / cube * 500;
    else
        rate = 0;
    result.x *= rate;
    result.y *= rate;

    return result;
}

//直交座標系ベクトルを極座標系ベクトルに変換
vectorRT_t IRSensorCtrl::CaliculateVectorRTfromVectorXY(vectorXY_t *vectorXY_p) const
{
    vectorRT_t result;
    result.radius = sqrt(pow(vectorXY_p->x, 2.0) + pow(vectorXY_p->y, 2.0));
    result.theta = atan2(vectorXY_p->x, vectorXY_p->y) / PI * 180.0;

    return result;
}
