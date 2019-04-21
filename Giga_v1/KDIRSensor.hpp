#ifndef KD_IR_SENSOR_h
#define KD_IR_SENSOR_h

typedef struct
{
    VectorDD_t polarVector = {0, 0};
    VectorXY_t deltaRectangularVector = {0, 0};
} BallStatus_t;

class KDIRSensor
{
  public:
    KDIRSensor(HardwareSerial *serialInstance) : _serialInstance(serialInstance) {}
    void init();
    //VectorDD_t read();
    void printValue();
    BallStatus_t *read();

  private:
    HardwareSerial *_serialInstance;
    BallStatus_t ballStatus;
    int16_t pastRadius = 0;
    int16_t pastTheta = 0;
    int16_t pastX = 0;
    int16_t pastY = 0;
};

#endif
