#ifndef KD_EEPROM_MAP_h
#define KD_EEPROM_MAP_h

typedef struct
{
    int address;
    uint8_t size;
} EEPROMData;

class KDEEPROMMap
{
  public:
    static constexpr int NumberOfAddresses = 1;
    static constexpr int LineThreshold = 0;
    static constexpr EEPROMData Addresses[NumberOfAddresses] =
        {
            {0, 2},
    };
};

constexpr int KDEEPROMMap::NumberOfAddresses;
constexpr int KDEEPROMMap::LineThreshold;
constexpr EEPROMData KDEEPROMMap::Addresses[NumberOfAddresses];

//アドレスリストの整合性を確認します. 整合性が無い場合はコンパイルエラーになります.
class KDEEPROMAddressCehecker
{
  public:
    constexpr static bool checkCorrection(int i)
    {
        return i <= 0
                   ? true
                   : (KDEEPROMMap::Addresses[i - 1].address + KDEEPROMMap::Addresses[i - 1].size == KDEEPROMMap::Addresses[i].address
                          ? checkCorrection(i - 1)
                          : false);
    };
};
static_assert(KDEEPROMAddressCehecker::checkCorrection(KDEEPROMMap::NumberOfAddresses - 1), "EEPROM address list is invaid.");

#endif
