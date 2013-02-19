#ifndef Vertex_h
#define Vertex_h

struct Vertex2f
{
    float x;
    float y;

    Vertex2f() {}
    Vertex2f(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};

struct Vertex3f
{
    float x;
    float y;
    float z;

    Vertex3f() {}
    Vertex3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct Vertex4f
{
    float x;
    float y;
    float z;
    float w;

    Vertex4f() {}
    Vertex4f(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
};

#endif
