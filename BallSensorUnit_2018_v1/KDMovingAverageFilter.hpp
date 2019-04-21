#ifndef KD_MOVING_AVERAGE_FILTER_h
#define KD_MOVING_AVERAGE_FILTER_h

template <typename T>
class KDMovingAverageFilter
{
  public:
    //KDMovingAverageFilter() : SamplingNumber(samplingNumber) {}
    T GetFilteredValue();
    T GetFilteredValue(T value);
    T SetNewValue(T value);
    
  private:
    static constexpr int SamplingNumber = 8;
    T samples[SamplingNumber];
    int currentIndex = 0;
};

#endif