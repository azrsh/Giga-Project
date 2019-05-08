#ifndef PULSE_WIDTH_READER_h
#define PULSE_WIDTH_READER_h

template <uint8_t numberOfBallSensors, const uint8_t pins[numberOfBallSensors]>
class PulseWidthReader
{
  private:
    const int timeLimit;
    const float deltaPulseWidth;
    float pulseWidth[numberOfBallSensors];
    bool getSensorValue(uint8_t index)
    {
        switch (index)
        {
        case 0:
            return digitalReadFast(pins[0]);
        case 1:
            return digitalReadFast(pins[1]);
        case 2:
            return digitalReadFast(pins[2]);
        case 3:
            return digitalReadFast(pins[3]);
        case 4:
            return digitalReadFast(pins[4]);
        case 5:
            return digitalReadFast(pins[5]);
        case 6:
            return digitalReadFast(pins[6]);
        case 7:
            return digitalReadFast(pins[7]);
        case 8:
            return digitalReadFast(pins[8]);
        case 9:
            return digitalReadFast(pins[9]);
        case 10:
            return digitalReadFast(pins[10]);
        case 11:
            return digitalReadFast(pins[11]);
        }
    };

  public:
    PulseWidthReader(int timeLimit, float deltaPulseWidth) : timeLimit(timeLimit), deltaPulseWidth(deltaPulseWidth){};

    void setupPins()
    {
        for (int i = 0; i < numberOfBallSensors; i++)
            pinMode(pins[i], INPUT);
    }

    const float *read()
    {
        for (int i = 0; i < numberOfBallSensors; i++)
            pulseWidth[i] = 0;

        const unsigned long startTimeUs = micros();
        while ((micros() - startTimeUs) < timeLimit)
        {
            for (int i = 0; i < numberOfBallSensors; i++)
            {
                if (getSensorValue(i) == false)
                {
                    pulseWidth[i] += deltaPulseWidth;
                }
            }
        }

        return pulseWidth;
    };
};

#endif
