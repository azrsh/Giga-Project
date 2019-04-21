#include <Arduino.h>
#include "KDMovingAverageFilter.hpp"

//実質intのみの実装になってしまった…templateわからん

template <typename T>
T KDMovingAverageFilter<T>::GetFilteredValue()
{
    T sam;
    for (int i = 0; i < SamplingNumber; i++)
    {
        sam += samples[i];
    }

    return sam / SamplingNumber;
}
template int KDMovingAverageFilter<int>::GetFilteredValue();

template <typename T>
T KDMovingAverageFilter<T>::GetFilteredValue(T value)
{
    SetNewValue(value);
    return GetFilteredValue();
}
template int KDMovingAverageFilter<int>::GetFilteredValue(int);

template <typename T>
T KDMovingAverageFilter<T>::SetNewValue(T value)
{
    samples[currentIndex] = value;
    currentIndex++;
    if (currentIndex >= SamplingNumber)
    {
        currentIndex = 0;
    }
}
template int KDMovingAverageFilter<int>::SetNewValue(int);