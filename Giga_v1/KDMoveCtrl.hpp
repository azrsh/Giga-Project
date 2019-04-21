#ifndef KD_MOVE_CTRL_h
#define KD_MOVE_CTRL_h

typedef struct
{
    int right;
    int left;
    int rear;
} MotorPowers;

class KDMoveCtrl
{
  public:
    static VectorXY_t baseVector;
    static void moveByLocalVector2(int x, int y, int w);
    static void moveByLocalVector2(int x, int y, int w, bool isLock);
    static void moveByLocalDegreeAndPower(int degree, int power, int w);
    static void moveByLocalDegreeAndPower(int degree, int power, int w, bool isAddBaseVector);

    static MotorPowers *getMotorPowersByLocalVector2(int x, int y, int w);
    static MotorPowers *getMotorPowersByLocalVector2(int x, int y, int w, bool isLock);
    static MotorPowers *getMotorPowersByLocalDegreeAndPower(int degree, int power, int w);
    static void addMotorPowersByLocalDegreeAndPower(MotorPowers *motorPowers);

    INLINE static void lockMovement(char x, char y)
    {
        lockX = x;
        lockY = y;
    };
    INLINE static void unlockMovement()
    {
        lockX = 0;
        lockY = 0;
    };

  private:
    static char lockX;
    static char lockY;
    static int getLockedDegree(int degree);
};

#endif
