#ifndef KD_UI_UNIT_COMMUNICATION_h
#define KD_UI_UNIT_COMMUNICATION_h

class KDUIUnitCommunication
{
  public:
    KDUIUnitCommunication(HardwareSerial *serialInstance) : _serialInstance(serialInstance) {}
    void init();
    void reset();
    int read();
    void printValue();

  private:
    HardwareSerial *_serialInstance;
    int value = 0;
    static constexpr char HederCharacter = 'S';
};

#endif