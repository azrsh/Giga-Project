#ifndef KD_SHARED_OBJECTS_h
#define KD_SHARED_OBJECTS_h

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

#endif
