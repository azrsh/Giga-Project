#ifndef VECTOR_RT_CALCULATOR_h
#define VECTOR_RT_CALCULATOR_h

class VectorRTCalculator
{
  public:
    VectorRTCalculator(){};

    const vectorRT_t calculate(const vectorXY_t *vectorXY_p) const
    {
        vectorRT_t result;
        result.radius = sqrt(pow(vectorXY_p->x, 2.0) + pow(vectorXY_p->y, 2.0));
        result.theta = atan2(vectorXY_p->x, vectorXY_p->y) / PI * 180.0;

        return result;
    };
};

#endif
