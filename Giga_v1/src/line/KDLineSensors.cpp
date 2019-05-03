#include <Arduino.h>
#include "../hardware/KDHardwere.hpp"
#include "../utilities/KDDebugUtility.hpp"
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
    /*KDDebugUtility::printValueWithTag("Front", CcheckFrontLineSensor());
    KDDebugUtility::printValueWithTag("Rear", checkRearLineSensor());
    KDDebugUtility::printValueWithTag("Right", checkRightLineSensor());
    KDDebugUtility::printValueWithTag("Left", checkLeftLineSensor());*/
    KDDebugUtility::println();
}
