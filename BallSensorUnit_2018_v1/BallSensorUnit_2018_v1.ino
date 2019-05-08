#include <math.h>
#include <digitalWriteFast.h>
#include "IRSensorData.hpp"
#include "PulseWidthReader.hpp"
#include "VectorXYCalculator.hpp"
#include "VectorRTCalculator.hpp"
#include "PulseWidthLowPassFilter.hpp"

constexpr unsigned long Baud = 115200;

PulseWidthReader<IRSensorData::NumberOfBallSensors, IRSensorData::BallSensorPins> pulseWidthReader(IRSensorData::IRBallWaveformModeA, 2.0);
VectorXYCalculator<IRSensorData::NumberOfBallSensors, IRSensorData::UnitVectorX, IRSensorData::UnitVectorY> vectorXYCalculator;
VectorRTCalculator vectorRTCalculator;

PulseWidthLowPassFilter<IRSensorData::NumberOfBallSensors> pulseWidthLowPassFilter(0.05);

float *pulseWidth;

void setup()
{
    Serial.begin(Baud);

    //センサpinのpuMode設定
    pulseWidthReader.setupPins();
}

void loop()
{
    static unsigned long time_ms = 0;

    const float *currentPulseWidth = pulseWidthReader.read(); // IRセンサから読み出し

    pulseWidth = pulseWidthLowPassFilter.calculate(currentPulseWidth);

    static vectorXY_t previousVectorXY = {0, 0};
    const vectorXY_t vectorXY = vectorXYCalculator.calculate(pulseWidth);
    const vectorRT_t vectorRT = vectorRTCalculator.calculate(&vectorXY);
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

    //constexpr int ThetaOffset = 0;
    //vectorRTInt.theta -= ThetaOffset;

    // 10ms周期でシリアル通信
    if (millis() - time_ms > 10)
    {
        time_ms = millis();

        sendVectorRTIntBySerial(vectorRTInt, deltaVectorXYInt);
        //printVectorRTIntBySerial(vectorRTInt, deltaVectorXYInt);
        //Serial.println((bool)digitalReadFast(10));
        //Serial.println(pulseIn(10, LOW, 833));
        //printRawData();
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

void printRawData()
{
    for (int i = 0; i < IRSensorData::NumberOfBallSensors; i++)
    {
        Serial.print(pulseWidth[i]);
        Serial.print("    ");
    }
    Serial.println();
}