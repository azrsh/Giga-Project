#ifndef KD_SHARED_OBJECTS_h
#define KD_SHARED_OBJECTS_h

#include <Arduino.h>

//INLINE展開のためのマクロ
#define INLINE inline __attribute__((always_inline))

//モード設定用のdefine
//------------------------------------------
//多少処理を犠牲にして安全な実行を優先する,未実装
#define SAFE_MODE

//ベンチマーク機能を実行する,未実装
#define BENCHMARK_MODE

//デバックモードで実行する
#define DEBUG_MODE
//------------------------------------------

class KDSharedObjects
{
  public:
    int positionX, positionY;
    int ballWorldPositionX, ballWorldPositionY;
    int ballLocalPositionX, ballLocalPositionY;

    //使用未定の変数
    int ballVelocityX, ballVelocityY;
    int ballAccelarationX, ballAccelarationY;

    //コート・機体・ボールなどに関する定数の定義
    static constexpr int WalledFieldWidth = 0, WalledFieldHeight = 0;
    static constexpr int BoxedFieldWidth = 0, BoxedFieldHeight = 0;
    static constexpr int GoalCenterPositionX = WalledFieldWidth / 2, GoalCenterPositionY = 100;
    static constexpr int BallRadius = 5;                                  //--------------------
    static constexpr int BodyRadius = 10;                                 //この三つの定義順に注意
    static constexpr int PositioningRadius = BallRadius + BodyRadius + 3; //--------------------

    static constexpr int ReferenceMotorPower = 500;
    static constexpr int MaximamMotorPower = 255; //pwm出力の最大

    //一度初期化したら変更しない値の定義
    const int DefaultConpassDegree;
};

//直交座標系ベクトルの型・変数の定義
typedef struct
{
    float x;
    float y;
} VectorXYf_t;

typedef struct
{
    int x;
    int y;
} VectorXY_t;

typedef struct
{
    int distance;
    int degrees;
} VectorDD_t;

#endif
