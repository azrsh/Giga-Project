#include "KDSharedObjects.hpp"
#include "KDMoveLocker.hpp"

VectorXY_t KDMoveLocker::getLockedVector(VectorXY_t vector) const
{
    if (lockX != 0 && (lockX > 0) == (vector.x > 0))
        vector.x = 0;
    if (lockY != 0 && (lockY > 0) == (vector.y > 0))
        vector.y = 0;

    return vector;
}

int KDMoveLocker::getLockedDegree(int degree) const
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
