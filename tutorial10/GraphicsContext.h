#ifndef GraphicsContext_h
#define GraphicsContext_h

#include <stdio.h>

#include <GL/glx.h>
#include <X11/Xlib.h>

class GraphicsContext
{
public:
    GraphicsContext();
    ~GraphicsContext();

    bool makeCurrentContext();
    void swapBuffers();

private:
    bool acquireNativeSystem();
    void releaseNativeSystem();

    bool acquireGLSystem();
    void releaseGLSystem();

    Display* m_display;
    Colormap m_xColorMap;
    Window m_xWindow;

    GLXFBConfig* m_listConfigs;
    GLXFBConfig m_config;

    GLXContext m_context;
    GLXWindow m_window;
    GLXPbuffer m_pbuffer;
};

#endif /* GraphicsContext_h  */
