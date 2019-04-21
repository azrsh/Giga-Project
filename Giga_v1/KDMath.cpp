#include <Arduino.h>
#include <math.h>
#include "KDMath.hpp"

//コンパイルオプション　-O3 コードサイズを大きくしてでも高速にする
//(unsigned int)i / 4;//掛け算割り算自動ビットシフト
//ポインタ　&aでアドレス、*aで値
//int8_t int より速い、arduinoは8bit

//差の絶対値が十分に小さい…範囲で見る（＋－）

//間違ってる＆使わないので一時凍結
/*constexpr double ArcsinConstexpr(double x, int i = 10)
{
    return i == 0 ? x :
    ((FactorialConstexpr(2 * i) / FactorialConstexpr(i))/ (PowConstexpr(4,i) * (2*i + 1))) * PowConstexpr(x,i) + SinConstexpr(x, i - 1);
}

constexpr double ArccosConstexpr(double x, int i = 10)
{
    return PI / 2 - ArcsinConstexpr(x,i);
}

constexpr double ArctanConstexpr(double x, int i = 10)
{
    return i == 0 ? x :
    PowConstexpr(-1,i) * PowConstexpr(x,2 * i +1) / (2 * i + 1) + ArctanConstexpr(x,i);
}*/

//作成中
//近似的三平方の定理でベクトルの大きさを求める
//参考 : http://d.hatena.ne.jp/nowokay/20120604
float FastDistance(int8_t x, int8_t y)
{
    //最小値　最大値　近似値
    int8_t min, max, approximate;

    if (x < 0)
        x = -x;
    if (y < 0)
        y = -y;

    if (x < y)
    {
        min = x;
        max = y;
    }
    else
    {
        min = y;
        max = x;
    }

    approximate = (max * 1007) + (min * 441);
    if (max < (min << 4))
        approximate -= (max * 40);

    return (float)((approximate + 512) >> 10);
}

//再帰的平方根算出
//ニュートン法で1/√xを求めxを後から乗算する
//速度の低下原因である割り算なし
//参考 : http://takashiijiri.com/study/miscs/fastsqrt.html
float FastSqrt2F(const float &x)
{
    float xHalf = 0.5f * x;
    int tmp = 0x5F3759DF - (*(int *)&x >> 1); //initial guess
    float xRes = *(float *)&tmp;

    xRes *= (1.5f - (xHalf * xRes * xRes)); //有効数字3桁くらいの精度
    //xRes *= ( 1.5f - ( xHalf * xRes * xRes ) );//コメントアウトを外すと精度が上がる、有効数字7桁くらいの精度
    return xRes * x;
}

constexpr float KDMath::sinTable[91];