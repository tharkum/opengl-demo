#include "Matrix.h"

Matrix4f::Matrix4f()
{
    setIdentity();
}

Matrix4f::Matrix4f(float x00, float x01, float x02, float x03,
                   float x10, float x11, float x12, float x13,
                   float x20, float x21, float x22, float x23,
                   float x30, float x31, float x32, float x33)
{
    setMatrix(x00, x01, x02, x03,
              x10, x11, x12, x13,
              x20, x21, x22, x23,
              x30, x31, x32, x33);
}

Matrix4f::~Matrix4f()
{
}

void Matrix4f::setIdentity()
{
    setMatrix(1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix4f::setMatrix(float x00, float x01, float x02, float x03,
                         float x10, float x11, float x12, float x13,
                         float x20, float x21, float x22, float x23,
                         float x30, float x31, float x32, float x33)
{
    m[0][0] = x00; m[0][1] = x01; m[0][2] = x02; m[0][3] = x03;
    m[1][0] = x10; m[1][1] = x11; m[1][2] = x12; m[1][3] = x13;
    m[2][0] = x20; m[2][1] = x21; m[2][2] = x22; m[2][3] = x23;
    m[3][0] = x30; m[3][1] = x31; m[3][2] = x32; m[3][3] = x33;
}


Matrix4f Matrix4f::operator*(const Matrix4f& Right) const
{
    Matrix4f Ret;
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                          m[i][1] * Right.m[1][j] +
                          m[i][2] * Right.m[2][j] +
                          m[i][3] * Right.m[3][j];
        }
    }

    return Ret;
}

void Matrix4f::setScaleTransform(const Vector3f& scale)
{
    setMatrix(scale.x, 0.0f,    0.0f,    0.0f,
              0.0f,    scale.y, 0.0f,    0.0f,
              0.0f,    0.0f,    scale.z, 0.0f,
              0.0f,    0.0f,    0.0f,    1.0f);
}


void Matrix4f::setRotateTransform(const Vector3f& rotate)
{
    Matrix4f xy, xz, yz;

    const float x = ToRadian(rotate.x);
    const float y = ToRadian(rotate.y);
    const float z = ToRadian(rotate.z);

    xy.setMatrix(cosf(z), -sinf(z), 0.0f, 0.0f,
                 sinf(z),  cosf(z), 0.0f, 0.0f,
                 0.0f,     0.0f,    1.0f, 0.0f,
                 0.0f,     0.0f,    0.0f, 1.0f);

    xz.setMatrix(cosf(y),  0.0f, -sinf(y), 0.0f,
                 0.0f,     1.0f,  0.0f,    0.0f,
                 sinf(y),  0.0f,  cosf(y), 0.0f,
                 0.0f,     0.0f,  0.0f,    1.0f);

    yz.setMatrix(1.0f,  0.0f,    0.0f,    0.0f,
                 0.0f,  cosf(x), sinf(x), 0.0f,
                 0.0f, -sinf(x), cosf(x), 0.0f,
                 0.0f,  0.0f,    0.0f,    1.0f);

    *this = xy * xz * yz;
}

void Matrix4f::setTranslateTransform(const Vector3f& translate)
{
    setMatrix(1.0f, 0.0f, 0.0f, translate.x,
              0.0f, 1.0f, 0.0f, translate.y,
              0.0f, 0.0f, 1.0f, translate.z,
              0.0f, 0.0f, 0.0f, 1.0f);

}
