#ifndef KD_CONSTEXPR_TEST_h
#define KD_CONSTEXPR_TEST_h

class KDConstexprTest
{
  public:
    constexpr KDConstexprTest(int8_t pin) : _pin(pin) {}
    void read()
    {
        volatile const uint8_t pin = _pin; //コードサイズ優先で最適化されるので、最適化を禁止してこう書いた方が複数回呼ぶなら早い
        unsigned long countstart = micros();
        for (int i = 0; i < 100; i++)
        {
            digitalReadFast(pin);
        }
        KDDebugUtility::printValueWithTag("Time", micros() - countstart);
        KDDebugUtility::printValueWithTag("Pin", _pin);
        Serial.println();
        delay(10);
    }
    constexpr int8_t Test() const { return _pin; }

  private:
    const uint8_t _pin;
};

#endif