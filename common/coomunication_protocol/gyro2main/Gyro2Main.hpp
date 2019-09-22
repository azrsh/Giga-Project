#ifndef GYRO_2_MAIN_h
#define GYRO_2_MAIN_h

#include "../CommunicationProtocol.hpp"

/*
115200bps
Protocol Definition
header || int   || 
1byte  || 2byte || 
*/

typedef CommunicationProtocol<115200, 'H', int> Gyro2Main;

#endif
