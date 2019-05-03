#ifndef KD_ULTRA_SONIC_SENSORS_h
#define KD_ULTRA_SONIC_SENSORS_h

#include "../utilities/KDMacroUtilities.hpp"

class KDUltraSonicSensor;

enum class FieldArea
{
    None = -1,
    CenterForward = 0,
    CenterBack = 1,
    RightSideForward = 2,
    RightSideBack = 3,
    LeftSideForward = 4,
    LeftSideBack = 5,
};

class KDUltraSonicSensors
{
  private:
    KDUltraSonicSensor *frontSensor;
    KDUltraSonicSensor *rearSensor;
    KDUltraSonicSensor *rightSensor;
    KDUltraSonicSensor *leftSensor;
    FieldArea currentArea = FieldArea::None;

  public:
    KDUltraSonicSensors(KDUltraSonicSensor *frontSensor, KDUltraSonicSensor *rearSensor, KDUltraSonicSensor *rightSensor, KDUltraSonicSensor *leftSensor)
        : frontSensor(frontSensor), rearSensor(rearSensor), rightSensor(rightSensor), leftSensor(leftSensor) {}
    void update();
    FieldArea getCurrentArea();
    int getFrontDistance();
    int getRearDistance();
    int getRightDistance();
    int getLeftDistance();

    void printValue();
};

#endif
