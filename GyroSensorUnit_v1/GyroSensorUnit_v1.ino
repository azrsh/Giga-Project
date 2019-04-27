#include <Wire.h>
#include <MPU6050_6Axis_MotionApps20.h>

//方位補正用のPID制御インスタンスだが、P制御しか実装してない
//KP=0.071~0.072の範囲
//KI=KP/DELTA_TIME
//KD＝KP*DELTA_TIME
//static constexpr float GyroPidKP = 0.072;
static constexpr float GyroPidKP = 0.02;
static constexpr float GyroPidKI = GyroPidKP / 14.5;
static constexpr float GyroPidKD = GyroPidKP * 14.5;
//KDPIDControl pidControl = KDPIDControl(GyroPidKP, GyroPidKI, GyroPidKD, -6.0f, 6.0f);

//仮置き-------------------------------------------------------------
//この囲みの中のブロックはMPU6050以外はその外側に依存していな
static constexpr int GyroX = 250;
static constexpr int GyroY = -65;
static constexpr int GyroZ = -10;
static constexpr int AccelZ = 4302;
/*calibtration result
Sensor readings with offsets:	4	0	16389	0	-1	-1
Your offsets:	-465	-1552	4302	250	-65	-10

Data is printed as: acelX acelY acelZ giroX giroY giroZ
Check that your sensor readings are close to 0 0 16384 0 0 0
If calibration was succesful write down your offsets so you can set them in your projects using something similar to mpu.setXAccelOffset(youroffset)
*/

MPU6050 mpu;
static uint8_t mpuIntStatus;
static bool dmpReady = false; // set true if DMP init was successful
static uint16_t packetSize;   // expected DMP packet size (default is 42 bytes)

int16_t Gyro_Now = 0, Gyro = 0, Gyro_Offset = 0;
int16_t gyro_test;
uint16_t fifoCount;
uint8_t fifoBuffer[64]; // FIFO storage buffer                 // orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
uint16_t test[4];

void GyroGet()
{
    mpuIntStatus = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();
    if ((mpuIntStatus & 0x10) || fifoCount == 1024)
    {
        mpu.resetFIFO();
    }
    else if (mpuIntStatus & 0x02)
    {
        while (fifoCount < packetSize)
            fifoCount = mpu.getFIFOCount();
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        Gyro_Now = degrees(ypr[0]) + 180;
        Gyro = Gyro_Now + Gyro_Offset;
        if (Gyro < 0)
            Gyro += 360;
        if (Gyro > 359)
            Gyro -= 360;
    }
}

void GryoStart()
{
    mpu.initialize();
    if (!mpu.testConnection())
    {
        Serial.println("MPU disconection");
        digitalWrite(10, HIGH);
        while (true)
        {
        }
    }
    if (mpu.dmpInitialize() != 0)
    {
        Serial.println("MPU break");
        digitalWrite(10, HIGH);
        while (true)
        {
        }
    }
    mpu.setXGyroOffset(GyroX);
    mpu.setYGyroOffset(GyroY);
    mpu.setZGyroOffset(GyroZ);
    mpu.setZAccelOffset(AccelZ);
    mpu.setDMPEnabled(true);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
}

void setup()
{
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
    Serial.begin(9600);
    GryoStart();
    Serial.println("SetUp Finished.");
}

void loop()
{
    static unsigned long previousUpdateTime = 0;
    int deltaTime = millis() - previousUpdateTime;
    if (deltaTime > 10)
    {
        GyroGet();
        int bodyDirection = Gyro;
        //これとか入れる
        if (bodyDirection > 360)
            bodyDirection -= 360;

        //printlnInt(bodyDirection);
        sendData(bodyDirection);

        previousUpdateTime = millis();
    }
}

void printlnInt(int bodyDirection)
{
    Serial.println(bodyDirection);
}

void sendData(int bodyDirection)
{
    Serial.write('H');
    Serial.write(lowByte(bodyDirection));
    Serial.write(highByte(bodyDirection));
}
