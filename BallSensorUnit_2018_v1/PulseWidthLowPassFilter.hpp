#ifndef PULSE_WIDTH_LOW_PASS_FILTER_h
#define PULSE_WIDTH_LOW_PASS_FILTER_h

template <uint8_t numberOfBallSensors>
class PulseWidthLowPassFilter
{
  private:
    const float rate;
    const float otherRate;
    float pulseWidth[numberOfBallSensors];

  public:
    PulseWidthLowPassFilter(float rate) : rate(rate), otherRate(1.0 - rate){};

    const float *calculate(const float *currentPulseWidth)
    {
        for (int i = 0; i < numberOfBallSensors; i++)
        {
            pulseWidth[i] = currentPulseWidth[i] * rate + pulseWidth[i] * otherRate;
        }

        return pulseWidth;
    };
};

#endif
