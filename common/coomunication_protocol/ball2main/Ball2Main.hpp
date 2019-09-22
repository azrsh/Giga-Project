#ifndef BALL_2_MAIN_h
#define BALL_2_MAIN_h

#include "../CommunicationProtocol.hpp"

/*
Protocol Definition



*/

/*struct
{
    theta, radius, dx, dy;
}*/

typedef CommunicationProtocol<115200, 'B', int> Ball2Main;

#endif
