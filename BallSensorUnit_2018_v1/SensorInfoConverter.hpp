#ifndef SENOSR_INFO_CONVERTER_h
#define SENOSR_INFO_CONVERTER_h

template <uint8_t numberOfBallSensors>
class SensorInfoConverter
{
  public:
    SensorInfoConverter(){};

    const sensorInfo_t convert(float *pulseWidth)
    {
        sensorInfo_t sensorInfo;

        sensorInfo.activeSensors = 0;   // ボールに反応しているセンサの個数
        sensorInfo.maxPulseWidth = 0;   // 一番反応の強いセンサのパルス幅
        sensorInfo.maxSensorNumber = 0; // 一番反応の強いセンサの番号
        for (int i = 0; i < numberOfBallSensors; i++)
        {
            if (pulseWidth[i] > 0)
            {
                sensorInfo.activeSensors += 1;
            }
            if (pulseWidth[i] > sensorInfo.maxPulseWidth)
            {
                sensorInfo.maxPulseWidth = pulseWidth[i];
                sensorInfo.maxSensorNumber = i;
            }
        }

        return sensorInfo;
    };
};

#endif
