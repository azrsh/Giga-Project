#ifndef VECTOR_STRUCT_h
#define VECTOR_STRUCT_h

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

#endif
