#ifndef KD_MOVE_CTRL_h
#define KD_MOVE_CTRL_h

#include "../utilities/KDMacroUtilities.hpp"
#include "../KDSharedObjects.hpp"
#include "../utilities/KDDataStructure.hpp"
#include "../utilities/KDMath.hpp"
#include "KDMoveLocker.hpp"

template <class ThreeMotors>
class KDMoveCtrl
{
  public:
    KDMoveCtrl(ThreeMotors *threeMotors, KDMoveLocker *moveLocker) : threeMotors(threeMotors), moveLocker(moveLocker){};
    VectorXY_t baseVector = {0, 0};

    void moveByLocalVector2(int x, int y, int w)
    {
        moveByLocalVector2(x, y, w, true);
    };

    void moveByLocalVector2(int x, int y, int w, bool isLock)
    {
        MotorPowers *motorPowers = getMotorPowersByLocalVector2(x, y, w, isLock);

        threeMotors->drive(motorPowers);
    };

    void moveByLocalDegreeAndPower(int degrees, int power, int w)
    {
        moveByLocalDegreeAndPower(degrees, power, w, true);
    };

    void moveByLocalDegreeAndPower(int degrees, int power, int w, bool isAddBaseVector)
    {
        MotorPowers *motorPowers = getMotorPowersByLocalDegreeAndPower(degrees, power, w);
        if (isAddBaseVector)
            addMotorPowersByLocalDegreeAndPower(motorPowers);

        threeMotors->drive(motorPowers);
    };

  private:
    ThreeMotors *threeMotors;
    KDMoveLocker *moveLocker;

    MotorPowers *getMotorPowersByLocalVector2(int x, int y, int w)
    {
        return getMotorPowersByLocalVector2(x, y, w, true);
    };

    MotorPowers *getMotorPowersByLocalVector2(int x, int y, int w, bool isLock)
    {
        if (isLock)
        {
            VectorXY_t vector = moveLocker->getLockedVector({x, y});
            x = vector.x;
            y = vector.y;
        }

        //元の式
        //int right = (x / 2) - (y * sqrt3 / 2) + (KDSharedObjects::BodyRadius * w);
        //int left = (x / 2) + (y * sqrt3 / 2) + (KDSharedObjects::BodyRadius * w);
        //int back = -x + (KDSharedObjects::BodyRadius * w);

        float xTerm = x * KDMath::sinByTable(30);
        float yTerm = y * KDMath::cosByTable(30);
        int rotatingForce = KDSharedObjects::BodyRadius * w;

        static MotorPowers motorPowers = {0, 0, 0};
        motorPowers.right = xTerm - yTerm + rotatingForce;
        motorPowers.left = xTerm + yTerm + rotatingForce;
        motorPowers.rear = -x + rotatingForce;

        return &motorPowers;
    };

    MotorPowers *getMotorPowersByLocalDegreeAndPower(int degree, int power, int w)
    {
        degree = moveLocker->getLockedDegree(degree);
        if (degree == -1)
            power = 0;

        int rotatingForce = KDSharedObjects::BodyRadius * w;

        static MotorPowers motorPowers = {0, 0, 0};
        motorPowers.right = KDMath::sinByTable(degree - 60) * power + rotatingForce;
        motorPowers.left = KDMath::sinByTable(degree - 300) * power + rotatingForce;
        motorPowers.rear = KDMath::sinByTable(degree - 180) * power + rotatingForce;

        return &motorPowers;
    }

    void addMotorPowersByLocalDegreeAndPower(MotorPowers *motorPowers)
    {
        MotorPowers *baseMotorPowers = getMotorPowersByLocalVector2(baseVector.x, baseVector.y, 0, true);
        motorPowers->right += baseMotorPowers->right;
        motorPowers->left += baseMotorPowers->left;
        motorPowers->rear += baseMotorPowers->rear;
    };
};

#endif
