#ifndef KD_KICKER_h
#define KD_KICKER_h

#include "../utilities/KDDebugUtility.hpp"

template <uint8_t pin>
class KDKicker
{
  private:
    unsigned long pastKickTime = 0;

  public:
    void init()
    {
        digitalWriteFast(pin, LOW); //キッカーをチャージモードに設定
        pastKickTime = 0;
    };
    void kick()
    {
        volatile unsigned long deltaTime = millis() - pastKickTime;
        if (deltaTime < 660)
            return;

        FlexiTimer2::stop();
        digitalWriteFast(KDHardwere::KickerPin, HIGH); //キック
        delay(150);                                    //キックには100us程度の待機時間が必要,この時間にほかの処理ができなくなってしまうので修正したい
        digitalWriteFast(KDHardwere::KickerPin, LOW);  //元に戻す
        FlexiTimer2::start();
        pastKickTime = millis();
    };
    void kickWithSerialPrint()
    {
        KDDebugUtility::printString("Kick");
        KDDebugUtility::println();
        kick();
    }
};

#endif
