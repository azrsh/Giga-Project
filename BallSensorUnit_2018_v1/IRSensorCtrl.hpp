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

class IRSensorCtrl
{
  public:
    //---------ハード依存変数---------
    //IRセンサの数
    static constexpr int8_t NumberOfBallSensors = 12;
    //-------------------------------

    void SetupSensors()
    {
        for (int i = 0; i < NumberOfBallSensors; i++)
            pinMode(BallSensorPins[i], INPUT);
    }

    bool GetSensorValue(const uint8_t index)
    {
        //なぜかこれが許されるけど原因不明
        //return digitalReadFast(BallSensorPins[index]);

        switch (index)
        {
        case 0:
            return digitalReadFast(BallSensorPins[0]);
        case 1:
            return digitalReadFast(BallSensorPins[1]);
        case 2:
            return digitalReadFast(BallSensorPins[2]);
        case 3:
            return digitalReadFast(BallSensorPins[3]);
        case 4:
            return digitalReadFast(BallSensorPins[4]);
        case 5:
            return digitalReadFast(BallSensorPins[5]);
        case 6:
            return digitalReadFast(BallSensorPins[6]);
        case 7:
            return digitalReadFast(BallSensorPins[7]);
        case 8:
            return digitalReadFast(BallSensorPins[8]);
        case 9:
            return digitalReadFast(BallSensorPins[9]);
        case 10:
            return digitalReadFast(BallSensorPins[10]);
        case 11:
            return digitalReadFast(BallSensorPins[11]);
        }
    }

    //センサの状態を格納する型
    //すべてのセンサのパルス幅を取得
    sensorInfo_t GetAllSensorPulseWidth(float pulseWidth[NumberOfBallSensors]);

    //パルス幅から直交座標系ベクトルに変換
    vectorXY_t CaliculateVectorXYFromPulseWidth(float *pulseWidth) const;

    //直交座標系ベクトルを極座標系ベクトルに変換
    vectorRT_t CaliculateVectorRTfromVectorXY(vectorXY_t *vectorXY_p) const;

  private:
    //公式ボールのMode Aでのパルスの周期(833us)
    //https://www.elekit.co.jp/pdf/RCJ-05%20waveform_j.pdf
    static constexpr uint16_t IRBallWaveformModeA = 833;

    //---------ハード依存変数---------
    //センサのピン番号
    static constexpr uint8_t BallSensorPins[NumberOfBallSensors] =
        {2, 3, 4, 5, 6, 7, 8, 9, 10, A0, A1, A2};

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
