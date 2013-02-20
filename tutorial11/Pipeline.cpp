#include "Pipeline.h"

Pipeline::Pipeline()
: m_changed(false)
, m_scale(1.0f, 1.0f, 1.0f)
, m_rotate(0.0f, 0.0f, 0.0f)
, m_translate(0.0f, 0.0f, 0.0f)
, m_transformation()
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::setScale(float scaleX, float scaleY, float scaleZ)
{
    m_scale.x = scaleX;
    m_scale.y = scaleY;
    m_scale.z = scaleZ;

    m_changed = true;
}

void Pipeline::setRotate(float rotateX, float rotateY, float rotateZ)
{
    m_rotate.x = rotateX;
    m_rotate.y = rotateY;
    m_rotate.z = rotateZ;

    m_changed = true;
}

void Pipeline::setTranslate(float x, float y, float z)
{
    m_translate.x = x;
    m_translate.y = y;
    m_translate.z = z;

    m_changed = true;
}

const Matrix4f* Pipeline::getTransformation()
{
    if (m_changed) {
        Matrix4f scale, rotate, translate;

        scale.setScaleTransform(m_scale);
        rotate.setRotateTransform(m_rotate);
        translate.setTranslateTransform(m_translate);

        m_transformation = translate * rotate * scale;

        m_changed = false;
    }

    return &m_transformation;
}
