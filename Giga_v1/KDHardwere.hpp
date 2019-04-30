#ifndef KD_HARDWERE_h
#define KD_HARDWERE_h

#include <Arduino.h>

//ハードウェア依存クラス

class KDHardwere
{
  public:
    static constexpr uint8_t KickerPin = 50;

    static constexpr uint8_t RightMotorDirectionPin = 25;
    static constexpr uint8_t LeftMotorDirectionPin = 26;
    static constexpr uint8_t RearMotorDirectionPin = 24;

    static constexpr uint8_t RightMotorPwmPin = 21;
    static constexpr uint8_t LeftMotorPwmPin = 22;
    static constexpr uint8_t RearMotorPwmPin = 20;

    static constexpr uint8_t FrontLineSensorPin = 39;
    static constexpr uint8_t RearLineSensorPin = 36;
    static constexpr uint8_t RightLineSensorPin = 38;
    static constexpr uint8_t LeftLineSensorPin = 37;

    static constexpr uint8_t FrontUSSensorPin = A5;
    static constexpr uint8_t RearUSSensorPin = A4;
    static constexpr uint8_t RightUSSensorPin = A2;
    static constexpr uint8_t LeftUSSensorPin = A3;

    static constexpr uint8_t Switch1Pin = 10;
    static constexpr uint8_t Switch2Pin = 9;

    static constexpr uint8_t CatchSensorPin = A16;

    static constexpr uint8_t LineThreshold = A21; //DAC0
    static constexpr uint8_t LineAnalogPin = A22;
    static constexpr uint8_t RightMotorElectricCurrentMonitoringPin = A0;
    static constexpr uint8_t LeftMotorElectricCurrentMonitoringPin = A1;
    static constexpr uint8_t RearMotorElectricCurrentMonitoringPin = A10;
    static constexpr uint8_t PowerVoltageMonitoringPin = A23;

    static constexpr uint8_t SpeakerPin = 2;

    static constexpr uint8_t LEDPin = 13;

    /*
    Serial1 ESP32
    Serail2 UI
    Serial3 RasberryPi
    Serial4 Ball
    Serial5 MPU6050
    rx : 3, tx : 4 EmptyMicon 
    */

    static void Initialize(void);

  private:
    //pinModeの初期化用関数
    static void SetupDigitalPins(void);
};

#endif