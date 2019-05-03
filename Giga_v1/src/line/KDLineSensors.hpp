#ifndef KD_LINE_SENSORS_h
#define KD_LINE_SENSORS_h

#include "../utilities/KDMacroUtilities.hpp"
#include "../utilities/KDDebugUtility.hpp"

template <class FrontLineSensor, class RearLineSensor, class RightLineSensor, class LeftLineSensor>
class KDLineSensors
{
  private:
    FrontLineSensor *frontSensor;
    RearLineSensor *rearSensor;
    RightLineSensor *rightSensor;
    LeftLineSensor *leftSensor;
    const uint8_t analogPin;
    const uint8_t thresholdPin;
    int whiteValue = 0;
    int greenValue = 0;

  public:
    KDLineSensors(const FrontLineSensor *frontSensor, const RearLineSensor *rearSensor, const RightLineSensor *rightSensor, const LeftLineSensor *leftSensor, uint8_t analogPin, uint8_t thresholdPin)
        : frontSensor(frontSensor), rearSensor(rearSensor), rightSensor(rightSensor), leftSensor(leftSensor), analogPin(analogPin), thresholdPin(thresholdPin){};
    INLINE bool checkFrontLineSensor() { return frontSensor->read(); }
    INLINE bool checkRearLineSensor() { return rearSensor->read(); }
    INLINE bool checkRightLineSensor() { return rightSensor->read(); }
    INLINE bool checkLeftLineSensor() { return leftSensor->read(); }
    void setWhiteValue()
    {
        whiteValue = analogRead(analogPin);
    };
    void setGreenValue()
    {
        greenValue = analogRead(analogPin);
    };
    void setThreshold()
    {
        int lineThreshold = round(greenValue * 0.7 + whiteValue * 0.3);
        //analogWrite(thresholdPin, lineThreshold);
        analogWrite(thresholdPin, 85);
        //analogWrite(thresholdPin, 400);
    };
    void printValue()
    {
        KDDebugUtility::printValueWithTag("Front", checkFrontLineSensor());
        KDDebugUtility::printValueWithTag("Rear", checkRearLineSensor());
        KDDebugUtility::printValueWithTag("Right", checkRightLineSensor());
        KDDebugUtility::printValueWithTag("Left", checkLeftLineSensor());

        KDDebugUtility::printValueWithTag("analog", analogRead(analogPin));
        analogWrite(KDHardwere::LineThreshold, 256);

        KDDebugUtility::printValueWithTag("Front", frontSensor->analogRead());
        KDDebugUtility::printValueWithTag("Rear", rearSensor->analogRead());
        KDDebugUtility::printValueWithTag("Right", rightSensor->analogRead());
        KDDebugUtility::printValueWithTag("Left", leftSensor->analogRead());
        KDDebugUtility::println();
    };
};

#endif
