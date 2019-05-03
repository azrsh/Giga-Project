#ifndef KD_KICKER_h
#define KD_KICKER_h

class KDKicker
{
  public:
    void init();
    void kick();
    void kickWithSerialPrint();

  private:
    unsigned long pastKickTime = 0;
};

#endif
