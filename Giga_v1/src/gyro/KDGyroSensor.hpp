#ifndef KD_GYRO_SENSOR_h
#define KD_GYRO_SENSOR_h

class KDGyroSensor
{
  public:
    KDGyroSensor(HardwareSerial *serialInstance) : _serialInstance(serialInstance) {}
    void init();
    void reset();
    int read();
    void printValue();

  private:
    HardwareSerial *_serialInstance;
    int value = 0;
};

#endif