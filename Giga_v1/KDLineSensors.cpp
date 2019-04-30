#include <Arduino.h>
#include "KDHardwere.hpp"
#include "KDSharedObjects.hpp"
#include "KDDebugUtility.hpp"
#include "KDLineSensors.hpp"

void KDLineSensors::setWhiteValue()
{
    whiteValue = analogRead(KDHardwere::LineAnalogPin);
}

void KDLineSensors::setGreenValue()
{
    greenValue = analogRead(KDHardwere::LineAnalogPin);
}

void KDLineSensors::setThreshold()
{
    int lineThreshold = round(greenValue * 0.7 + whiteValue * 0.3);
    //analogWrite(KDHardwere::LineThreshold, lineThreshold);
    analogWrite(KDHardwere::LineThreshold, 85);
    //analogWrite(KDHardwere::LineThreshold, 400);
}

void KDLineSensors::printValue()
{
    KDDebugUtility::printValueWithTag("Front", analogRead(KDHardwere::FrontLineSensorPin));
    KDDebugUtility::printValueWithTag("Rear", analogRead(KDHardwere::RearLineSensorPin));
    KDDebugUtility::printValueWithTag("Right", analogRead(KDHardwere::RightLineSensorPin));
    KDDebugUtility::printValueWithTag("Left", analogRead(KDHardwere::LeftLineSensorPin));
    /*KDDebugUtility::printValueWithTag("Front", CheckFrontLineSensor());
    KDDebugUtility::printValueWithTag("Rear", CheckRearLineSensor());
    KDDebugUtility::printValueWithTag("Right", CheckRightLineSensor());
    KDDebugUtility::printValueWithTag("Left", CheckLeftLineSensor());*/
    KDDebugUtility::println();
}
