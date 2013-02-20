#ifndef Vector_h
#define Vector_h

struct Vector2f
{
    float x;
    float y;

    Vector2f() {}
    Vector2f(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};

struct Vector3f
{
    float x;
    float y;
    float z;

    Vector3f() {}
    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct Vector4f
{
    float x;
    float y;
    float z;
    float w;

    Vector4f() {}
    Vector4f(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
};

#endif
