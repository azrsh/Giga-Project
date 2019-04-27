#include <Arduino.h>
#include "KDSharedObjects.hpp"
#include "KDDebugUtility.hpp"
#include "KDIRSensor.hpp"
#include "KDHardwere.hpp"

//後で過去のボールの位置とかも見るようにする？

//_serialInstanceを元に戻すときはSerial2に置き換えること

void KDIRSensor::init()
{
    _serialInstance->begin(115200);
}

BallStatus_t *KDIRSensor::read()
{
    constexpr int8_t dataSize = sizeof('B') + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int);

    int16_t radius = pastRadius;
    int16_t theta = pastTheta;
    int16_t x = pastX, y = pastY;

    byte radiusLow, radiusHigh, thetaLow, thetaHigh, xHigh, xLow, yHigh, yLow;
    //int count = 0; //上限回数の設定
    while (_serialInstance->available() >= dataSize /* && count < 10 && digitalReadFast(KDHardwere::Switch1Pin)*/)
    {
        char header = _serialInstance->read();
        if (header == 'B')
        {
            radiusLow = (byte)_serialInstance->read();
            radiusHigh = (byte)_serialInstance->read();
            thetaLow = (byte)_serialInstance->read();
            thetaHigh = (byte)_serialInstance->read();

            xLow = (byte)_serialInstance->read();
            xHigh = (byte)_serialInstance->read();
            yLow = (byte)_serialInstance->read();
            yHigh = (byte)_serialInstance->read();

            radius = makeWord(radiusHigh, radiusLow);
            theta = makeWord(thetaHigh, thetaLow);
            x = makeWord(xHigh, xLow);
            y = makeWord(yHigh, yLow);

            bool isThetaTrue = theta >= -180 && theta <= 180;
            bool isRadiusTrue = radius >= 0 && radius < 100;

            if (isThetaTrue)
                pastTheta = theta;
            else
                theta = pastTheta;

            if (isRadiusTrue)
                pastRadius = radius;
            else
                radius = pastRadius;

            pastX = x;
            pastY = y;

            if (isThetaTrue && isRadiusTrue)
                break;
        }
        else
        {
            radius = pastRadius;
            theta = pastTheta;
            x = pastX;
            y = pastY;
        }

        //count++;
    }

    /*Serial.print("Raw : ");
    Serial.print(radius);
    Serial.print("    ");
    Serial.print(theta);
    Serial.print("    ");*/

    ballStatus.polarVector.distance = radius;
    ballStatus.polarVector.degrees = theta;
    ballStatus.deltaRectangularVector.x = x;
    ballStatus.deltaRectangularVector.y = y;

    return &ballStatus;
}

void KDIRSensor::printValue()
{
    KDDebugUtility::printValueWithTag("analog", analogRead(KDHardwere::LineAnalogPin));
    analogWrite(KDHardwere::LineThreshold, 256);

    BallStatus_t *ballStatus = read();

    VectorDD_t polarVector = ballStatus->polarVector;
    KDDebugUtility::printValueWithTag("dir", polarVector.degrees);
    KDDebugUtility::printValueWithTag("rad", polarVector.distance);

    VectorXY_t deltaRectangularVector = ballStatus->deltaRectangularVector;
    KDDebugUtility::printValueWithTag("deltaX", deltaRectangularVector.x);
    KDDebugUtility::printValueWithTag("deltaY", deltaRectangularVector.y);

    KDDebugUtility::println();
}