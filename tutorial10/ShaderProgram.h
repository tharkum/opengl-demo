#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <GL/gl.h>

struct Shader
{
    GLuint shader;
    GLint  compile_status;
};

struct ShaderProgram
{
    GLuint program;
    GLint  link_status;
    GLint  validate_status;

    Shader vertex;
    Shader fragment;
};

#endif
