#include <Arduino.h>
#include <digitalWriteFast.h>
#include "IRSensorData.hpp"

constexpr uint8_t IRSensorData::BallSensorPins[NumberOfBallSensors];
constexpr float IRSensorData::UnitVectorX[NumberOfBallSensors];
constexpr float IRSensorData::UnitVectorY[NumberOfBallSensors];
