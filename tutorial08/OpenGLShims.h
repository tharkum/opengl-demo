#ifndef OpenGLShims_h
#define OpenGLShims_h

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glext.h>

#if 0
#define GL_CHECK(func) func
#else
#define GL_CHECK(func) \
    ({ func; \
       GLenum error = glGetError(); \
       if (error != GL_NO_ERROR) { \
           fprintf(stderr, "\n[GL_ERROR]: %s: %s (%i)\n%s - (ERROR: %#x)\n", __FILE__, __FUNCTION__, __LINE__, #func, error); \
           exit(1); \
       } \
     })
#endif

typedef struct _OpenGLFunctionTable OpenGLFunctionTable;

bool initializeOpenGLShims();
OpenGLFunctionTable* openGLFunctionTable();

typedef void (*glAttachShaderType) (GLuint, GLuint);
typedef void (*glBindAttribLocationType) (GLuint, GLuint, const GLchar*);
typedef void (*glBindBufferType) (GLenum, GLuint);
typedef void (*glBindFramebufferType) (GLenum, GLuint);
typedef void (*glBindVertexArrayType) (GLuint);
typedef void (*glBufferDataType) (GLenum, GLsizeiptr, const GLvoid*, GLenum);
typedef void (*glClearType) (GLbitfield);
typedef void (*glClearColorType) (GLclampf, GLclampf, GLclampf, GLclampf);
typedef void (*glCompileShaderType) (GLuint);
typedef GLuint (*glCreateProgramType) (void);
typedef GLuint (*glCreateShaderType) (GLenum);
typedef void (*glDeleteBuffersType) (GLsizei, const GLuint*);
typedef void (*glDeleteProgramType) (GLuint);
typedef void (*glDeleteShaderType) (GLuint);
typedef void (*glDeleteVertexArraysType) (GLsizei, const GLuint*);
typedef void (*glDetachShaderType) (GLuint, GLuint);
typedef void (*glDisableVertexAttribArrayType) (GLuint);
typedef void (*glDrawArraysType) (GLenum, GLint, GLsizei);
typedef void (*glEnableVertexAttribArrayType) (GLuint);
typedef void (*glGenBuffersType) (GLsizei, GLuint*);
typedef void (*glGenVertexArraysType) (GLsizei, GLuint*);
typedef void (*glGetProgramivType) (GLuint, GLenum, GLint*);
typedef void (*glGetProgramInfoLogType) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (*glGetShaderInfoLogType) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (*glGetShaderivType) (GLuint, GLenum, GLint*);
typedef GLint (*glGetUniformLocationType) (GLuint, const GLchar*);
typedef void (*glLinkProgramType) (GLuint);
typedef void (*glShaderSourceType) (GLuint, GLsizei, const GLchar**, const GLint*);
typedef void (*glUniform1fType) (GLuint, GLfloat);
typedef void (*glUniformMatrix4fvType) (GLuint, GLsizei, GLboolean, const GLfloat*);
typedef void (*glUseProgramType) (GLuint);
typedef void (*glValidateProgramType) (GLuint);
typedef void (*glVertexAttribPointerType) (GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);

#define FUNCTION_TABLE_ENTRY(FunctionName)  FunctionName##Type FunctionName

typedef struct _OpenGLFunctionTable {
    FUNCTION_TABLE_ENTRY(glAttachShader);
    FUNCTION_TABLE_ENTRY(glBindAttribLocation);
    FUNCTION_TABLE_ENTRY(glBindBuffer);
    FUNCTION_TABLE_ENTRY(glBindFramebuffer);
    FUNCTION_TABLE_ENTRY(glBindVertexArray);
    FUNCTION_TABLE_ENTRY(glBufferData);
    FUNCTION_TABLE_ENTRY(glClear);
    FUNCTION_TABLE_ENTRY(glClearColor);
    FUNCTION_TABLE_ENTRY(glCompileShader);
    FUNCTION_TABLE_ENTRY(glCreateProgram);
    FUNCTION_TABLE_ENTRY(glCreateShader);
    FUNCTION_TABLE_ENTRY(glDeleteBuffers);
    FUNCTION_TABLE_ENTRY(glDeleteProgram);
    FUNCTION_TABLE_ENTRY(glDeleteShader);
    FUNCTION_TABLE_ENTRY(glDeleteVertexArrays);
    FUNCTION_TABLE_ENTRY(glDetachShader);
    FUNCTION_TABLE_ENTRY(glDisableVertexAttribArray);
    FUNCTION_TABLE_ENTRY(glDrawArrays);
    FUNCTION_TABLE_ENTRY(glEnableVertexAttribArray);
    FUNCTION_TABLE_ENTRY(glGenBuffers);
    FUNCTION_TABLE_ENTRY(glGenVertexArrays);
    FUNCTION_TABLE_ENTRY(glGetProgramiv);
    FUNCTION_TABLE_ENTRY(glGetProgramInfoLog);
    FUNCTION_TABLE_ENTRY(glGetShaderInfoLog);
    FUNCTION_TABLE_ENTRY(glGetShaderiv);
    FUNCTION_TABLE_ENTRY(glGetUniformLocation);
    FUNCTION_TABLE_ENTRY(glLinkProgram);
    FUNCTION_TABLE_ENTRY(glShaderSource);
    FUNCTION_TABLE_ENTRY(glUniform1f);
    FUNCTION_TABLE_ENTRY(glUniformMatrix4fv);
    FUNCTION_TABLE_ENTRY(glUseProgram);
    FUNCTION_TABLE_ENTRY(glValidateProgram);
    FUNCTION_TABLE_ENTRY(glVertexAttribPointer);
} OpenGLFunctionTable;

#ifndef DISABLE_OPENGL_SHIMS
#define LOOKUP_GL_FUNCTION(Function)     openGLFunctionTable()->Function
#define glAttachShader                   LOOKUP_GL_FUNCTION(glAttachShader)
#define glBindAttribLocation             LOOKUP_GL_FUNCTION(glBindAttribLocation)
#define glBindBuffer                     LOOKUP_GL_FUNCTION(glBindBuffer)
#define glBindFramebuffer                LOOKUP_GL_FUNCTION(glBindFramebuffer)
#define glBindVertexArray                LOOKUP_GL_FUNCTION(glBindVertexArray)
#define glBufferData                     LOOKUP_GL_FUNCTION(glBufferData)
#define glClear                          LOOKUP_GL_FUNCTION(glClear)
#define glClearColor                     LOOKUP_GL_FUNCTION(glClearColor)
#define glCompileShader                  LOOKUP_GL_FUNCTION(glCompileShader)
#define glCreateProgram                  LOOKUP_GL_FUNCTION(glCreateProgram)
#define glCreateShader                   LOOKUP_GL_FUNCTION(glCreateShader)
#define glDeleteBuffers                  LOOKUP_GL_FUNCTION(glDeleteBuffers)
#define glDeleteProgram                  LOOKUP_GL_FUNCTION(glDeleteProgram)
#define glDeleteShader                   LOOKUP_GL_FUNCTION(glDeleteShader)
#define glDeleteVertexArrays             LOOKUP_GL_FUNCTION(glDeleteVertexArrays)
#define glDetachShader                   LOOKUP_GL_FUNCTION(glDetachShader)
#define glDisableVertexAttribArray       LOOKUP_GL_FUNCTION(glDisableVertexAttribArray)
#define glDrawArrays                     LOOKUP_GL_FUNCTION(glDrawArrays)
#define glEnableVertexAttribArray        LOOKUP_GL_FUNCTION(glEnableVertexAttribArray)
#define glGenBuffers                     LOOKUP_GL_FUNCTION(glGenBuffers)
#define glGenVertexArrays                LOOKUP_GL_FUNCTION(glGenVertexArrays)
#define glGetProgramiv                   LOOKUP_GL_FUNCTION(glGetProgramiv)
#define glGetProgramInfoLog              LOOKUP_GL_FUNCTION(glGetProgramInfoLog)
#define glGetShaderInfoLog               LOOKUP_GL_FUNCTION(glGetShaderInfoLog)
#define glGetShaderiv                    LOOKUP_GL_FUNCTION(glGetShaderiv)
#define glGetUniformLocation             LOOKUP_GL_FUNCTION(glGetUniformLocation)
#define glLinkProgram                    LOOKUP_GL_FUNCTION(glLinkProgram)
#define glShaderSource                   LOOKUP_GL_FUNCTION(glShaderSource)
#define glUniform1f                      LOOKUP_GL_FUNCTION(glUniform1f)
#define glUniformMatrix4fv               LOOKUP_GL_FUNCTION(glUniformMatrix4fv)
#define glUseProgram                     LOOKUP_GL_FUNCTION(glUseProgram)
#define glValidateProgram                LOOKUP_GL_FUNCTION(glValidateProgram)
#define glVertexAttribPointer            LOOKUP_GL_FUNCTION(glVertexAttribPointer)
#endif

#endif
