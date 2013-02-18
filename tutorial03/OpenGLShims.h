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

typedef void (*glBindBufferType) (GLenum, GLuint);
typedef void (*glBindFramebufferType) (GLenum, GLuint);
typedef void (*glBindVertexArrayType) (GLuint);
typedef void (*glBufferDataType) (GLenum, GLsizeiptr, const GLvoid*, GLenum);
typedef void (*glClearType) (GLbitfield);
typedef void (*glClearColorType) (GLclampf, GLclampf, GLclampf, GLclampf);
typedef void (*glDeleteBuffersType) (GLsizei, const GLuint*);
typedef void (*glDeleteVertexArraysType) (GLsizei, const GLuint*);
typedef void (*glDisableVertexAttribArrayType) (GLuint);
typedef void (*glDrawArraysType) (GLenum, GLint, GLsizei);
typedef void (*glEnableVertexAttribArrayType) (GLuint);
typedef void (*glGenBuffersType) (GLsizei, GLuint*);
typedef void (*glGenVertexArraysType) (GLsizei, GLuint*);
typedef void (*glVertexAttribPointerType) (GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);

#define FUNCTION_TABLE_ENTRY(FunctionName)  FunctionName##Type FunctionName

typedef struct _OpenGLFunctionTable {
    FUNCTION_TABLE_ENTRY(glBindBuffer);
    FUNCTION_TABLE_ENTRY(glBindFramebuffer);
    FUNCTION_TABLE_ENTRY(glBindVertexArray);
    FUNCTION_TABLE_ENTRY(glBufferData);
    FUNCTION_TABLE_ENTRY(glClear);
    FUNCTION_TABLE_ENTRY(glClearColor);
    FUNCTION_TABLE_ENTRY(glDeleteBuffers);
    FUNCTION_TABLE_ENTRY(glDeleteVertexArrays);
    FUNCTION_TABLE_ENTRY(glDisableVertexAttribArray);
    FUNCTION_TABLE_ENTRY(glDrawArrays);
    FUNCTION_TABLE_ENTRY(glEnableVertexAttribArray);
    FUNCTION_TABLE_ENTRY(glGenBuffers);
    FUNCTION_TABLE_ENTRY(glGenVertexArrays);
    FUNCTION_TABLE_ENTRY(glVertexAttribPointer);
} OpenGLFunctionTable;

#ifndef DISABLE_OPENGL_SHIMS
#define LOOKUP_GL_FUNCTION(Function)     openGLFunctionTable()->Function
#define glBindBuffer                     LOOKUP_GL_FUNCTION(glBindBuffer)
#define glBindFramebuffer                LOOKUP_GL_FUNCTION(glBindFramebuffer)
#define glBindVertexArray                LOOKUP_GL_FUNCTION(glBindVertexArray)
#define glBufferData                     LOOKUP_GL_FUNCTION(glBufferData)
#define glClear                          LOOKUP_GL_FUNCTION(glClear)
#define glClearColor                     LOOKUP_GL_FUNCTION(glClearColor)
#define glDeleteBuffers                  LOOKUP_GL_FUNCTION(glDeleteBuffers)
#define glDeleteVertexArrays             LOOKUP_GL_FUNCTION(glDeleteVertexArrays)
#define glDisableVertexAttribArray       LOOKUP_GL_FUNCTION(glDisableVertexAttribArray)
#define glDrawArrays                     LOOKUP_GL_FUNCTION(glDrawArrays)
#define glEnableVertexAttribArray        LOOKUP_GL_FUNCTION(glEnableVertexAttribArray)
#define glGenBuffers                     LOOKUP_GL_FUNCTION(glGenBuffers)
#define glGenVertexArrays                LOOKUP_GL_FUNCTION(glGenVertexArrays)
#define glVertexAttribPointer            LOOKUP_GL_FUNCTION(glVertexAttribPointer)
#endif

#endif
