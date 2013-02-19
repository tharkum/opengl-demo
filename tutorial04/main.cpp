#include "GraphicsTimer.h"
#include "GraphicsContext.h"
#include "OpenGLShims.h"
#include "ShaderProgram.h"
#include "Vertex.h"

#include <fstream>
using namespace std;

// Global variable
GLuint VBO;
ShaderProgram shaderProgram;

void render_cb (union sigval arg)
{
    static int count = 0;
    static float alpha = 0.0;

    GraphicsContext* context = reinterpret_cast<GraphicsContext*>(arg.sival_ptr);

    context->makeCurrentContext();

    alpha = ((count++ * 25) % 255) / 255.0;

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    GL_CHECK(glClearColor(0.0, 0.0, 0.0, alpha));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glDisableVertexAttribArray(0));

    context->swapBuffers();
}

static void createVertexBufferObject(GraphicsContext *context)
{
    Vertex3f vertices[3];
    vertices[0] = Vertex3f(-1.0f, -1.0f, 0.0f);
    vertices[1] = Vertex3f(1.0f, -1.0f, 0.0f);
    vertices[2] = Vertex3f(0.0f, 1.0f, 0.0f);

    context->makeCurrentContext();

    GL_CHECK(glGenBuffers(1, &VBO));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

static void deleteVertexBufferObject(GraphicsContext *context)
{
    context->makeCurrentContext();
    GL_CHECK(glDeleteBuffers(1, &VBO));
}

static void addShader(Shader *shader, const char *fileName, GLenum shaderType)
{
    GL_CHECK(shader->shader = glCreateShader(shaderType));
    if (!shader->shader) {
        fprintf(stderr, "Error creating shader type : %#x\n", shaderType);
        exit(1);
    }

    int length;
    char *shaderSource;

    ifstream is;
    is.open(fileName, ios::binary);

    is.seekg(0, ios::end);
    length = is.tellg();
    is.seekg(0, ios::beg);

    shaderSource = new char[length + 1];

    is.read(shaderSource, length);
    shaderSource[length] = '\0';

    GL_CHECK(glShaderSource(shader->shader, 1, (const char **)&shaderSource, 0));
    GL_CHECK(glCompileShader(shader->shader));
    GL_CHECK(glGetShaderiv(shader->shader, GL_COMPILE_STATUS, &shader->compile_status));

    delete [] shaderSource;

    if (!shader->compile_status) {
        GLchar infoLog[1024];
        GL_CHECK(glGetShaderInfoLog(shader->shader, 1024, NULL, infoLog));
        fprintf(stderr, "Error compiling shader type (%#x):\n%s\n", shaderType, infoLog);
        exit(1);
    }
}

static void createShaderProgram(GraphicsContext *context)
{
    context->makeCurrentContext();

    GL_CHECK(shaderProgram.program = glCreateProgram());
    if (!shaderProgram.program) {
        fprintf(stderr, "Error creating program\n");
        exit(1);
    }

    addShader(&shaderProgram.vertex, "vertex.shader", GL_VERTEX_SHADER);
    addShader(&shaderProgram.fragment, "fragment.shader", GL_FRAGMENT_SHADER);

    GL_CHECK(glAttachShader(shaderProgram.program, shaderProgram.vertex.shader));
    GL_CHECK(glAttachShader(shaderProgram.program, shaderProgram.fragment.shader));

    GL_CHECK(glBindAttribLocation(shaderProgram.program, 0, "Vertex"));

    GL_CHECK(glLinkProgram(shaderProgram.program));
    GL_CHECK(glGetProgramiv(shaderProgram.program, GL_LINK_STATUS, &shaderProgram.link_status));

    if (!shaderProgram.link_status) {
        GLchar infoLog[1024];
        GL_CHECK(glGetProgramInfoLog(shaderProgram.program, 1024, NULL, infoLog));
        fprintf(stderr, "Error linking program:\n%s\n", infoLog);
        exit(1);
    }

    GL_CHECK(glValidateProgram(shaderProgram.program));
    GL_CHECK(glGetProgramiv(shaderProgram.program, GL_VALIDATE_STATUS, &shaderProgram.validate_status));
    if (!shaderProgram.validate_status) {
        fprintf(stderr, "Error validating program:\n");
        exit(1);
    }

    GL_CHECK(glUseProgram(shaderProgram.program));
}

static void deleteShaderProgram(GraphicsContext *context)
{
    context->makeCurrentContext();

    GL_CHECK(glUseProgram(0));

    GL_CHECK(glDetachShader(shaderProgram.program, shaderProgram.vertex.shader));
    GL_CHECK(glDetachShader(shaderProgram.program, shaderProgram.fragment.shader));

    GL_CHECK(glDeleteShader(shaderProgram.vertex.shader));
    GL_CHECK(glDeleteShader(shaderProgram.fragment.shader));

    GL_CHECK(glDeleteProgram(shaderProgram.program));
}

int main (int argc, char* argv[])
{
    if (!initializeOpenGLShims())
        return 1;

    GraphicsContext context;

    createVertexBufferObject(&context);
    createShaderProgram(&context);

    GraphicsTimer* timer = new GraphicsTimer(500, render_cb, &context);

    getchar();   // press a key to stop

    delete timer;

    deleteShaderProgram(&context);
    deleteVertexBufferObject(&context);

    return 0;
}
