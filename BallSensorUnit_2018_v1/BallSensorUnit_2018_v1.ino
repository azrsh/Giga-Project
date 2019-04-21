#include <math.h>
#include <digitalWriteFast.h>
#include "IRSensorCtrl.hpp"

constexpr unsigned long Baud = 115200;

IRSensorCtrl irSensorCtrl = IRSensorCtrl();

float pulseWidth[IRSensorCtrl::NumberOfBallSensors];

void setup()
{
    Serial.begin(Baud);

    //センサpinのpuMode設定
    irSensorCtrl.SetupSensors();
}

void loop()
{
    static unsigned long time_ms = 0;

    float currentPulseWidth[IRSensorCtrl::NumberOfBallSensors];                       // パルス幅を格納する変数
    sensorInfo_t sensorInfo = irSensorCtrl.GetAllSensorPulseWidth(currentPulseWidth); // 実験用の測定データ ベクトルのみ使う場合は無視することも可能

    //フィルタリング
    constexpr float Rate = 0.05;
    for (int i = 0; i < IRSensorCtrl::NumberOfBallSensors; i++)
    {
        pulseWidth[i] = currentPulseWidth[i] * Rate + pulseWidth[i] * (1 - Rate);
    }

    static vectorXY_t previousVectorXY = {0, 0};
    vectorXY_t vectorXY = irSensorCtrl.CaliculateVectorXYFromPulseWidth(pulseWidth); // 直交座標系のベクトル構造体
    vectorRT_t vectorRT = irSensorCtrl.CaliculateVectorRTfromVectorXY(&vectorXY);    // 極座標系のベクトル構造体
    vectorXY_t deltaVectorXY = {(vectorXY.x - previousVectorXY.x) * 10, (vectorXY.y - previousVectorXY.y) * 10};
    previousVectorXY = vectorXY;

    vectorRTInt_t vectorRTInt;
    vectorRTInt.radius = round(vectorRT.radius);
    vectorRTInt.theta = round(vectorRT.theta);

    vectorXYInt_t vectorXYInt;
    vectorXYInt.x = round(vectorXY.x);
    vectorXYInt.y = round(vectorXY.y);

    vectorXYInt_t deltaVectorXYInt;
    deltaVectorXYInt.x = round(deltaVectorXY.x);
    deltaVectorXYInt.y = round(deltaVectorXY.y);

    constexpr int ThetaOffset = 10;
    vectorRTInt.theta -= ThetaOffset;

    // 10ms周期でシリアル通信
    if (millis() - time_ms > 10)
    {
        time_ms = millis();

        sendVectorRTIntBySerial(vectorRTInt, deltaVectorXYInt);
        //printVectorRTIntBySerial(vectorRTInt, deltaVectorXYInt);
    }
}

void sendVectorRTIntBySerial(vectorRTInt_t vectorRT, vectorXYInt_t vectorXY)
{
    //各2バイト以上は無視でいい？
    int16_t radius = vectorRT.radius;
    int16_t theta = vectorRT.theta;
    Serial.print('B');
    Serial.write(lowByte(radius));
    Serial.write(highByte(radius));
    Serial.write(lowByte(theta));
    Serial.write(highByte(theta));

    int16_t x = vectorXY.x;
    int16_t y = vectorXY.y;
    Serial.write(lowByte(x));
    Serial.write(highByte(x));
    Serial.write(lowByte(y));
    Serial.write(highByte(y));
}

void printVectorRTIntBySerial(vectorRTInt_t vectorRT, vectorXYInt_t vectorXY)
{
    //各2バイト以上は無視でいい？
    int16_t radius = vectorRT.radius;
    int16_t theta = vectorRT.theta;

    Serial.print("radius : ");
    Serial.print(radius);
    Serial.print("    theta : ");
    Serial.print(theta);

    int16_t x = vectorXY.x;
    int16_t y = vectorXY.y;
    Serial.print("    x : ");
    Serial.print(x);
    Serial.print("    y : ");
    Serial.print(y);
    Serial.println();
}