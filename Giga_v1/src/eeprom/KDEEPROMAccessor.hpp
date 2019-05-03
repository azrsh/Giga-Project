#ifndef KD_EEPROM_ACCESSOR_h
#define KD_EEPROM_ACCESSOR_h

#include <EEPROM.h>
#include "KDEEPROMMap.hpp"

template <typename DataType>
class KDEEPROMAccsessor
{
  private:
    const int address;

  public:
    KDEEPROMAccsessor(int address) : address(address){};
    ~KDEEPROMAccsessor(){};
    void push(const DataType *data)
    {
        EEPROM.put<DataType>(address, data);
    };
    DataType pull()
    {
        EEPROM.get<DataType>(address);
    };
};

#endif
