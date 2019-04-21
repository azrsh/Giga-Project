#include <Arduino.h>
#include "KDSharedObjects.hpp"
#include "KDThreeMotors.hpp"
#include "KDMoveCtrl.hpp"
#include "KDMath.hpp"

char KDMoveCtrl::lockX = 0;
char KDMoveCtrl::lockY = 0;
VectorXY_t KDMoveCtrl::baseVector = {0, 0};

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

    KDThreeMotors::SetMotorPower(motorPowers->right,
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

    KDThreeMotors::SetMotorPower(motorPowers->right,
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
        if (lockX != 0 && (lockX > 0) == (x > 0))
            x = 0;
        if (lockY != 0 && (lockY > 0) == (y > 0))
            y = 0;
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
    degree = getLockedDegree(degree);
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

int KDMoveCtrl::getLockedDegree(int degree)
{
    degree %= 360;
    if (degree < 0)
        degree += 360;

    if (lockX == 0 && lockY == 1)
    {
        if (degree > 0 && degree < 90)
            return 90;
        else if (degree > 270)
            return 270;
        else if (degree == 0)
            return -1;
    }
    if (lockX == 0 && lockY == -1)
    {
        if (degree > 90 && degree < 180)
            return 90;
        else if (degree > 180 && degree < 270)
            return 270;
        else if (degree == 180)
            return -1;
    }
    if (lockX == 1 && lockY == 0)
    {
        if (degree > 0 && degree < 90)
            return 0;
        else if (degree > 90 && degree < 180)
            return 180;
        else if (degree == 90)
            return -1;
    }
    if (lockX == -1 && lockY == 0)
    {
        if (degree > 270)
            return 0;
        else if (degree > 180 && degree < 270)
            return 180;
        else if (degree == 270)
            return -1;
    }
    if (lockX == 1 && lockY == 1)
    {
        if (degree > 45 && degree < 135)
            return 135;
        else if (degree > 315 || degree < 45)
            return 315;
        else if (degree == 45)
            return -1;
    }
    if (lockX == -1 && lockY == 1)
    {
        if (degree > 315 || degree < 45)
            return 45;
        else if (degree > 225 && degree < 315)
            return 225;
        else if (degree == 315)
            return -1;
    }
    if (lockX == 1 && lockY == -1)
    {
        if (degree > 45 && degree < 135)
            return 45;
        else if (degree > 135 && degree < 225)
            return 225;
        else if (degree == 135)
            return -1;
    }
    if (lockX == -1 && lockY == -1)
    {
        if (degree > 135 && degree < 225)
            return 135;
        else if (degree > 225 && degree < 315)
            return 315;
        else if (degree == 225)
            return -1;
    }
    return degree;
}
