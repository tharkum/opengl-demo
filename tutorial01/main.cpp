#include "GraphicsTimer.h"
#include "GraphicsContext.h"


void render_cb (union sigval arg) {
    static int count = 0;
    static float alpha = 0.0;

    GraphicsContext* context = reinterpret_cast<GraphicsContext*>(arg.sival_ptr);

    context->makeCurrentContext();

    alpha = ((count++ * 25) % 255) / 255.0;

    glClearColor(0.0, 1.0, 0.0, alpha);
    glClear(GL_COLOR_BUFFER_BIT);

    context->swapBuffers();
}

int main (int argc, char* argv[])
{
    GraphicsContext context;

    GraphicsTimer timer(500, render_cb, &context);

    getchar();   // press a key to stop

    return 0;
}
