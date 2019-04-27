#ifndef KD_MATH_h
#define KD_MATH_h

//リテラル値(90、1.57など)または、constexprな定数を指定しないとかえって遅くなる
#include "KDSharedObjects.hpp"

class KDMath
{
  public:
    static constexpr float deg2Rad = 0.01745329251f;
    static constexpr float rad2Deg = 57.2957795131f;

    static int sign(int value)
    {
        if (value == 0)
            return 0;

        return value / abs(value);
    }

    /*//階乗
    static constexpr float PowConstexpr(double x, uint8_t y)
    {
        return y == 0 ? 1
                      : y > 1 ? x * PowConstexpr(x, y - 1) : x;
    }
    static float PowInline(double x, uint8_t y)
    {
        return y == 0 ? 1
                      : y > 1 ? x * PowInline(x, y - 1) : x;
    }

    static constexpr unsigned int FactorialConstexpr(uint8_t x)
    {
        return x > 1 ? x * FactorialConstexpr(x - 1) : 1;
    }
    static unsigned int FactorialInline(uint8_t x)
    {
        return x > 1 ? x * FactorialInline(x - 1) : 1;
    }

    static int ConvertDegreesRangeFrom0To360(int angle)
    {
        angle %= 360;
        if (angle < 0)
        {
            angle += 360;
        }

        return angle;
    }

    static int ConvertDegreesRangeOfPlusOrMinus180(int angle)
    {
        angle += 180;
        angle %= 360;
        if (angle < 0)
        {
            angle += 180;
        }
        else
        {
            angle -= 180;
        }

        return angle;
    }
*/
    static constexpr float safeDegreesConstexpr(int degrees)
    {
        return degrees > 360 ? degrees % 360 : (degrees < 0 ? 360 + (degrees % 360) : degrees);
    }
    INLINE static float safeDegreesInline(int degrees)
    {
        return degrees > 360 ? degrees % 360 : (degrees < 0 ? 360 + (degrees % 360) : degrees);
    }

    static float sinByTable(int degrees)
    {
        degrees = safeDegreesInline(degrees);

        int sign = degrees < 180 ? 1 : -1;
        int half = degrees % 180;
        int quarter = half;
        if (half > 90)
            quarter = 180 - half;

        return sign * sinTable[quarter];
    }

    static float cosByTable(int degrees)
    {
        return sinByTable(90 - degrees);
    }

    static constexpr float sinConstexpr(int degrees)
    {
        return sin(degrees * deg2Rad);
    }
    static constexpr float cosConstexpr(int degrees)
    {
        return cos(degrees * deg2Rad);
    }

  private:
    static constexpr float sinTable[91] = {sin(0 * deg2Rad), sin(1 * deg2Rad), sin(2 * deg2Rad), sin(3 * deg2Rad), sin(4 * deg2Rad),
                                           sin(5 * deg2Rad), sin(6 * deg2Rad), sin(7 * deg2Rad), sin(8 * deg2Rad), sin(9 * deg2Rad),
                                           sin(10 * deg2Rad), sin(11 * deg2Rad), sin(12 * deg2Rad), sin(13 * deg2Rad), sin(14 * deg2Rad),
                                           sin(15 * deg2Rad), sin(16 * deg2Rad), sin(17 * deg2Rad), sin(18 * deg2Rad), sin(19 * deg2Rad),
                                           sin(20 * deg2Rad), sin(21 * deg2Rad), sin(22 * deg2Rad), sin(23 * deg2Rad), sin(24 * deg2Rad),
                                           sin(25 * deg2Rad), sin(26 * deg2Rad), sin(27 * deg2Rad), sin(28 * deg2Rad), sin(29 * deg2Rad),
                                           sin(30 * deg2Rad), sin(31 * deg2Rad), sin(32 * deg2Rad), sin(33 * deg2Rad), sin(34 * deg2Rad),
                                           sin(35 * deg2Rad), sin(36 * deg2Rad), sin(37 * deg2Rad), sin(38 * deg2Rad), sin(39 * deg2Rad),
                                           sin(40 * deg2Rad), sin(41 * deg2Rad), sin(42 * deg2Rad), sin(43 * deg2Rad), sin(44 * deg2Rad),
                                           sin(45 * deg2Rad), sin(46 * deg2Rad), sin(47 * deg2Rad), sin(48 * deg2Rad), sin(49 * deg2Rad),
                                           sin(50 * deg2Rad), sin(51 * deg2Rad), sin(52 * deg2Rad), sin(53 * deg2Rad), sin(54 * deg2Rad),
                                           sin(55 * deg2Rad), sin(56 * deg2Rad), sin(57 * deg2Rad), sin(58 * deg2Rad), sin(59 * deg2Rad),
                                           sin(60 * deg2Rad), sin(61 * deg2Rad), sin(62 * deg2Rad), sin(63 * deg2Rad), sin(64 * deg2Rad),
                                           sin(65 * deg2Rad), sin(66 * deg2Rad), sin(67 * deg2Rad), sin(68 * deg2Rad), sin(69 * deg2Rad),
                                           sin(70 * deg2Rad), sin(71 * deg2Rad), sin(72 * deg2Rad), sin(73 * deg2Rad), sin(74 * deg2Rad),
                                           sin(75 * deg2Rad), sin(76 * deg2Rad), sin(77 * deg2Rad), sin(78 * deg2Rad), sin(79 * deg2Rad),
                                           sin(80 * deg2Rad), sin(81 * deg2Rad), sin(82 * deg2Rad), sin(83 * deg2Rad), sin(84 * deg2Rad),
                                           sin(85 * deg2Rad), sin(86 * deg2Rad), sin(87 * deg2Rad), sin(88 * deg2Rad), sin(89 * deg2Rad),
                                           sin(90 * deg2Rad)};
};

#endif
