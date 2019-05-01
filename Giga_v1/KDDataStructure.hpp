#ifndef KD_DATA_STRUCTURE_h
#define KD_DATA_STRUCTURE_h

typedef struct
{
    int right;
    int left;
    int rear;
} MotorPowers;

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