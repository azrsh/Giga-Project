#ifndef PULSE_WIDTH_PRINTER_h
#define PULSE_WIDTH_PRINTER_h

template <uint8_t numberOfBallSensors>
class PulseWidthPrinter
{
    HardwareSerial *debugSerial;

  public:
    PulseWidthPrinter(HardwareSerial *debugSerial) : debugSerial(debugSerial){};

    void print(const float *pulseWidth)
    {
        for (int i = 0; i < numberOfBallSensors; i++)
        {
            debugSerial->print(pulseWidth[i]);
            debugSerial->print("    ");
        }
        debugSerial->println();
    };
};

#endif
