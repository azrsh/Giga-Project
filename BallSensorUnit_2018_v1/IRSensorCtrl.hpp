#ifndef IR_SENSOR_CTRL
#define IR_SENSOR_CTRL

//#include <Arduino.h>
//#include <digitalWriteFast.h>

//センサの状態を格納する型・変数の定義
typedef struct {
    int activeSensors;      // 反応したセンサの個数
    int maxPulseWidth;      // 最大のセンサ値
    int maxSensorNumber;    // 最大の値を観測したセンサの番号
} sensorInfo_t;

//直交座標系ベクトルの型・変数の定義
typedef struct {
    float x;
    float y;
} vectorXY_t;

//直交座標系ベクトルのInt版の型・変数の定義
typedef struct {
    int x;
    int y;
} vectorXYInt_t;

//極座標系ベクトルの型・変数の定義
typedef struct {
    float radius;
    float theta;
} vectorRT_t;

//極座標系ベクトルのInt版の型・変数の定義
typedef struct {
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
        pinMode(BallSensorPins[0],INPUT);
        pinMode(BallSensorPins[1],INPUT);
        pinMode(BallSensorPins[2],INPUT);
        pinMode(BallSensorPins[3],INPUT);
        pinMode(BallSensorPins[4],INPUT);
        pinMode(BallSensorPins[5],INPUT);
        pinMode(BallSensorPins[6],INPUT);
        pinMode(BallSensorPins[7],INPUT);
        pinMode(BallSensorPins[8],INPUT);
        pinMode(BallSensorPins[9],INPUT);
        pinMode(BallSensorPins[10],INPUT);
        pinMode(BallSensorPins[11],INPUT);
    }

    bool GetSensorValue(const uint8_t index)
    {
        //なぜかこれが許されるけど原因不明
        //return digitalReadFast(BallSensorPins[index]);
        
        switch(index)
        {
            case 0:   return digitalReadFast(BallSensorPins[0]);
            case 1:   return digitalReadFast(BallSensorPins[1]);
            case 2:   return digitalReadFast(BallSensorPins[2]);
            case 3:   return digitalReadFast(BallSensorPins[3]);
            case 4:   return digitalReadFast(BallSensorPins[4]);
            case 5:   return digitalReadFast(BallSensorPins[5]);
            case 6:   return digitalReadFast(BallSensorPins[6]);
            case 7:   return digitalReadFast(BallSensorPins[7]);
            case 8:   return digitalReadFast(BallSensorPins[8]);
            case 9:   return digitalReadFast(BallSensorPins[9]);
            case 10:  return digitalReadFast(BallSensorPins[10]);
            case 11:  return digitalReadFast(BallSensorPins[11]);
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
    {A2, A1, 9, A0, 8, 5, 4, 3, 2, A5, A4, A3};

    //センサが向いている方向のsin,cos（正規化済みのセンサの方向ベクトル）,12個用
    static constexpr float UnitVectorX[NumberOfBallSensors] =
    {0.000, 0.500, 0.866, 1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500};
    static constexpr float UnitVectorY[NumberOfBallSensors] = 
    {1.000, 0.866, 0.500, 0.000, -0.500, -0.866, -1.000, -0.866, -0.500, 0.000, 0.500, 0.866};
    
    //パルス幅を加算していく際の1回読み込みあたりの加算量 必要に応じて変更
    static constexpr float deltaPulseWidth     = 2.0;
    
    //led port
    //static constexpr byte LED1 = 10;
    //static constexpr byte LED2 = 11;
    //-------------------------------
    
    float GetUnitVectorX(int8_t index) const
    {
        switch(index)
        {
            case 0:   return UnitVectorX[0];
            case 1:   return UnitVectorX[1];
            case 2:   return UnitVectorX[2];
            case 3:   return UnitVectorX[3];
            case 4:   return UnitVectorX[4];
            case 5:   return UnitVectorX[5];
            case 6:   return UnitVectorX[6];
            case 7:   return UnitVectorX[7];
            case 8:   return UnitVectorX[8];
            case 9:   return UnitVectorX[9];
            case 10:  return UnitVectorX[10];
            case 11:  return UnitVectorX[11];
        }
    }
    
    float GetUnitVectorY(int8_t index) const
    {
        switch(index)
        {
            case 0:   return UnitVectorY[0];
            case 1:   return UnitVectorY[1];
            case 2:   return UnitVectorY[2];
            case 3:   return UnitVectorY[3];
            case 4:   return UnitVectorY[4];
            case 5:   return UnitVectorY[5];
            case 6:   return UnitVectorY[6];
            case 7:   return UnitVectorY[7];
            case 8:   return UnitVectorY[8];
            case 9:   return UnitVectorY[9];
            case 10:  return UnitVectorY[10];
            case 11:  return UnitVectorY[11];
        }
    }
};

#endif
