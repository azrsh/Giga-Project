#include <Arduino.h>
#include <FlexiTimer2.h> //ラインセンサのタイマ割り込み用
#include "KDKicker.hpp"
#include "KDHardwere.hpp"
#include "KDSharedObjects.hpp"

//pinModeの初期化を各クラスに分散したらこっちに移動したい
/*void KDKicker::KDKicker()
{
    digitalWriteFast(KDHardwere::KickerPin, LOW); //キッカーをチャージモードに設定
}*/

void KDKicker::init()
{
    digitalWriteFast(KDHardwere::KickerPin, LOW); //キッカーをチャージモードに設定
    pastKickTime = 0;
}

void KDKicker::kick()
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
}
