#ifndef KD_TEST_SENSOR_READER_h
#define KD_TEST_SENSOR_READER_h

class KDTestSensorReader : IReadable<KDTestSensorReader>
{
  public:
    constexpr KDTestSensorReader(int8_t pin) : _pin(pin) {}
    int read() { return _pin; }

  private:
    const int8_t _pin;
};

#endif