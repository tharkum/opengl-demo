#ifndef Pipeline_h
#define Pipeline_h

#include "Matrix.h"
#include "Vector.h"

class Pipeline
{
public:
    Pipeline();
    ~Pipeline();

    void setScale(float, float, float);
    void setRotate(float, float, float);
    void setTranslate(float, float, float);

    const Matrix4f* getTransformation();

private:
    bool m_changed;

    Vector3f m_scale;
    Vector3f m_rotate;
    Vector3f m_translate;

    Matrix4f m_transformation;
};

#endif
