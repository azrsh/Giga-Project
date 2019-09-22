#ifndef COMMUNICATION_PROTOCOL_h
#define COMMUNICATION_PROTOCOL_h

template <int baudRate, char header, typename DataType>
class CommunicationProtocol
{
  private:
    HardwareSerial *serialInstance;
    const unsigned long timeout;
    byte[sizeof(DataType)] buffer;
    static constexpr int DataTypeSize = sizeof(DataType);
    static constexpr int DataSize = sizeof(header) + sizeof(DataType);

  public:
    KDIRSensor(HardwareSerial *serialInstance, , unsigned long timeout) : serialInstance(serialInstance), timeout(timeout) {}
    void init()
    {
        serialInstance.begin(baudRate);
    };
    void send(const DataType *data)
    {
        serialInstance.write(header);
        buffer = (byte *)data;
        for (int i = 0; i < DataTypeSize; i++)
        {
            serialInstance.write(buffer);
        }
    };
    DataType recieve()
    {
        int time = 0;
        while (serialInstance->available() >= DataSize && time < timeout)
        {
            char character = serialInstance->read();
            if (character == header)
            {
                for (int i = 0; i < DataTypeSize; i++)
                {
                    buffer[i] = serialInstance.read();
                }
                break;
            }

            time++;
        }

        return *((DataType *)buffer);
    };
};

#endif
