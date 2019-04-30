#include <Arduino.h>
#include "KDSharedObjects.hpp"
#include "KDHardwere.hpp"
#include "KDMotor.hpp"
#include "KDThreeMotors.hpp"
#include "KDMoveCtrl.hpp"
#include "KDMoveLocker.hpp"
#include "KDMath.hpp"

#include "KDMotor.hpp"

VectorXY_t KDMoveCtrl::baseVector = {0, 0};

RightMotor KDMoveCtrl::rightMotor(1.0);
LeftMotor KDMoveCtrl::leftMotor(1.0);
RearMotor KDMoveCtrl::rearMotor(1.0);
KDThreeMotors<RightMotor, LeftMotor, RearMotor> KDMoveCtrl::threeMotors(&rightMotor, &leftMotor, &rearMotor);

KDMoveLocker *KDMoveCtrl::moveLocker = nullptr;

void KDMoveCtrl::init(KDMoveLocker *moveLocker)
{
    KDMoveCtrl::moveLocker = moveLocker;
}

//非ハード依存関数
/*void KDMoveCtrl::moveByWorldVector2(int worldX, int worldY, int w)
{
    int cosDegree;
    int sinDegree; //自機の角度のsin,cosを取得

    //座標系の変換
    int localX = (worldX * cosDegree) + (worldY * sinDegree);
    int localY = -(worldX * sinDegree) + (worldY * cosDegree);

    moveByLocalVector2(localX, localY, w);
}*/

//ハード依存関数
void KDMoveCtrl::moveByLocalVector2(int x, int y, int w)
{
    moveByLocalVector2(x, y, w, true);
}

void KDMoveCtrl::moveByLocalVector2(int x, int y, int w, bool isLock)
{
    MotorPowers *motorPowers = getMotorPowersByLocalVector2(x, y, w, isLock);

    threeMotors.drive(motorPowers->right,
                      motorPowers->left,
                      motorPowers->rear);
}

void KDMoveCtrl::moveByLocalDegreeAndPower(int degrees, int power, int w)
{
    moveByLocalDegreeAndPower(degrees, power, w, true);
}

void KDMoveCtrl::moveByLocalDegreeAndPower(int degrees, int power, int w, bool isAddBaseVector)
{
    MotorPowers *motorPowers = getMotorPowersByLocalDegreeAndPower(degrees, power, w);
    if (isAddBaseVector)
        addMotorPowersByLocalDegreeAndPower(motorPowers);

    threeMotors.drive(motorPowers->right,
                      motorPowers->left,
                      motorPowers->rear);
}

MotorPowers *KDMoveCtrl::getMotorPowersByLocalVector2(int x, int y, int w)
{
    return getMotorPowersByLocalVector2(x, y, w, true);
}

MotorPowers *KDMoveCtrl::getMotorPowersByLocalVector2(int x, int y, int w, bool isLock)
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
}

MotorPowers *KDMoveCtrl::getMotorPowersByLocalDegreeAndPower(int degree, int power, int w)
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

void KDMoveCtrl::addMotorPowersByLocalDegreeAndPower(MotorPowers *motorPowers)
{
    MotorPowers *baseMotorPowers = KDMoveCtrl::getMotorPowersByLocalVector2(baseVector.x, baseVector.y, 0, true);
    motorPowers->right += baseMotorPowers->right;
    motorPowers->left += baseMotorPowers->left;
    motorPowers->rear += baseMotorPowers->rear;
}
