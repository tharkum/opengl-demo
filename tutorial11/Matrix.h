#ifndef Matrix_h
#define Matrix_h

#include "Vector.h"

#include <cmath>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

class Matrix4f
{
public:
    Matrix4f();
    Matrix4f(float x00, float x01, float x02, float x03,
             float x10, float x11, float x12, float x13,
             float x20, float x21, float x22, float x23,
             float x30, float x31, float x32, float x33);
    ~Matrix4f();

    void setIdentity();
    void setMatrix(float x00, float x01, float x02, float x03,
                   float x10, float x11, float x12, float x13,
                   float x20, float x21, float x22, float x23,
                   float x30, float x31, float x32, float x33);

    void setScaleTransform(const Vector3f&);
    void setRotateTransform(const Vector3f&);
    void setTranslateTransform(const Vector3f&);

    Matrix4f operator*(const Matrix4f& Right) const;

    float m[4][4];
};

#endif
