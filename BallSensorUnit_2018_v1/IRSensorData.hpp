#ifndef IR_SENSOR_CTRL
#define IR_SENSOR_CTRL

//#include <Arduino.h>
//#include <digitalWriteFast.h>

//センサの状態を格納する型・変数の定義
typedef struct
{
    int activeSensors;   // 反応したセンサの個数
    int maxPulseWidth;   // 最大のセンサ値
    int maxSensorNumber; // 最大の値を観測したセンサの番号
} sensorInfo_t;

//直交座標系ベクトルの型・変数の定義
typedef struct
{
    float x;
    float y;
} vectorXY_t;

//直交座標系ベクトルのInt版の型・変数の定義
typedef struct
{
    int x;
    int y;
} vectorXYInt_t;

//極座標系ベクトルの型・変数の定義
typedef struct
{
    float radius;
    float theta;
} vectorRT_t;

//極座標系ベクトルのInt版の型・変数の定義
typedef struct
{
    int radius;
    int theta;
} vectorRTInt_t;

class IRSensorData
{
  public:
    //---------ハード依存変数---------
    //IRセンサの数
    static constexpr uint8_t NumberOfBallSensors = 12;
    //-------------------------------

    //公式ボールのMode Aでのパルスの周期(833us)
    //https://www.elekit.co.jp/pdf/RCJ-05%20waveform_j.pdf
    static constexpr uint16_t IRBallWaveformModeA = 833;

    //---------ハード依存変数---------
    //センサのピン番号
    static constexpr uint8_t BallSensorPins[NumberOfBallSensors] =
        {2, A2, A1, A0, 10, 9, 8, 7, 6, 5, 4, 3};

    //センサが向いている方向のsin,cos（正規化済みのセンサの方向ベクトル）,12個用
    static constexpr float UnitVectorX[NumberOfBallSensors] =
        {0.000, 0.500, 0.866, 1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500};
    static constexpr float UnitVectorY[NumberOfBallSensors] =
        {1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500, 0.000, 0.500, 0.866};

    //パルス幅を加算していく際の1回読み込みあたりの加算量 必要に応じて変更
    static constexpr float deltaPulseWidth = 2.0;

    //led port
    //static constexpr byte LED1 = 10;
    //static constexpr byte LED2 = 11;
    //-------------------------------
};

#endif
