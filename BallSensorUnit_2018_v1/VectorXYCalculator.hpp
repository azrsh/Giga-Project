#ifndef VECTOR_XY_CALCULATOR_h
#define VECTOR_XY_CALCULATOR_h

template <uint8_t numberOfBallSensors,
          const float unitVectorX[numberOfBallSensors], const float unitVectorY[numberOfBallSensors]>
class VectorXYCalculator
{
  public:
    VectorXYCalculator(){};

    const vectorXY_t calculate(const float *pulseWidth)
    {
        vectorXY_t result = {0, 0};
        float pulseWidthSum = 0;
        for (int i = 0; i < numberOfBallSensors; i++)
        {
            result.x += pulseWidth[i] * unitVectorX[i];
            result.y += pulseWidth[i] * unitVectorY[i];
            pulseWidthSum += pulseWidth[i];
        }

        float sqrtRadius = sqrt(pulseWidthSum);
        float cube = pulseWidthSum * sqrtRadius;
        float rate;
        if (cube > 0.0001)
            rate = 1 / cube * 500;
        else
            rate = 0;
        result.x *= rate;
        result.y *= rate;

        return result;
    };
};

#endif
