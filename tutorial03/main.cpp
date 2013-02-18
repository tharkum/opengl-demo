#include "GraphicsTimer.h"
#include "GraphicsContext.h"
#include "OpenGLShims.h"
#include "Vertex.h"

// Global variable
GLuint VBO;

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

int main (int argc, char* argv[])
{
    if (!initializeOpenGLShims())
        return 1;

    GraphicsContext context;

    createVertexBufferObject(&context);

    GraphicsTimer* timer = new GraphicsTimer(500, render_cb, &context);

    getchar();   // press a key to stop

    delete timer;

    deleteVertexBufferObject(&context);

    return 0;
}
