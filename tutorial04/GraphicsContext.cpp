#include "GraphicsContext.h"

GraphicsContext::GraphicsContext()
    : m_display(0)
    , m_xColorMap(0)
    , m_xWindow(0)
    , m_listConfigs(0)
    , m_config(0)
    , m_context(0)
    , m_window(0)
    , m_pbuffer(0)
{
    if (!acquireNativeSystem())
        goto RELEASE_NATIVE;

    if (!acquireGLSystem())
        goto RELEASE_GL;

    return;

RELEASE_GL:
    releaseGLSystem();
RELEASE_NATIVE:
    releaseNativeSystem();
}

GraphicsContext::~GraphicsContext()
{
    releaseGLSystem();

    releaseNativeSystem();
}

bool GraphicsContext::makeCurrentContext()
{
    if (m_context == glXGetCurrentContext())
        return true;
    return glXMakeContextCurrent(m_display, m_window, m_window, m_context);
}

void GraphicsContext::swapBuffers()
{
    makeCurrentContext();
    glXSwapBuffers(m_display, m_window);
}

static int * getConfigAttribList()
{
    static int attrib_list[] =
      {
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        GLX_DOUBLEBUFFER, true,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT | GLX_PBUFFER_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        None
      };

    return attrib_list;
}


bool GraphicsContext::acquireNativeSystem()
{
    XInitThreads();

    m_display = XOpenDisplay(0);
    if (!m_display) {
        printf("%s: %s (%i): ERROR - XOpenDisplay() \n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    int errno, extension;
    if (!glXQueryExtension(m_display, &errno, &extension)) {
        printf("%s: %s (%i): ERROR - GLX extension is not present for an X server\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    int numAvailableConfigs = 0;

    m_listConfigs = glXChooseFBConfig(m_display, DefaultScreen(m_display),
                                 getConfigAttribList(), &numAvailableConfigs);
    if (!m_listConfigs || !numAvailableConfigs) {
        printf("%s: %s (%i): ERROR - No matching glxConfig exists\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    XVisualInfo *scopedVisualInfo;
    for (int i = 0; i < numAvailableConfigs; i++) {
        scopedVisualInfo = glXGetVisualFromFBConfig(m_display, m_listConfigs[i]);
        if (!scopedVisualInfo)
            continue;

        if (scopedVisualInfo->depth == 32) {
            m_config = m_listConfigs[i];
            break;
        }

        XFree(scopedVisualInfo);
        scopedVisualInfo = NULL;
    }

    // Did not find any visual supporting alpha, select the first available config.
    if (!scopedVisualInfo) {
        scopedVisualInfo = glXGetVisualFromFBConfig(m_display, m_listConfigs[0]);
        m_config = m_listConfigs[0];
    }

    m_xColorMap = XCreateColormap(m_display, RootWindow(m_display, scopedVisualInfo->screen),
                                  scopedVisualInfo->visual, AllocNone);

    unsigned long valuemask = CWEventMask | CWColormap | CWBackPixel | CWBorderPixel;

    XSetWindowAttributes xAttributes;
    xAttributes.background_pixel = 0;
    xAttributes.border_pixel = 0;
    xAttributes.colormap = m_xColorMap;
    xAttributes.event_mask = ExposureMask | KeyPressMask | ButtonPress |
                             StructureNotifyMask | ButtonReleaseMask |
                             KeyReleaseMask | EnterWindowMask | LeaveWindowMask |
                             PointerMotionMask | Button1MotionMask |
                             VisibilityChangeMask | ColormapChangeMask;

    m_xWindow = XCreateWindow(m_display, RootWindow(m_display, scopedVisualInfo->screen),
                              0, 0, 600, 500, 0,
                              scopedVisualInfo->depth,
                              InputOutput,
                              scopedVisualInfo->visual,
                              valuemask, &xAttributes);
    if (!m_xWindow) {
        printf("%s: %s (%i): ERROR - Invalid X Window ID\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    XSetStandardProperties(m_display, m_xWindow, "Tutorial04 - Shaders", "Tutorial04",
                           None, NULL, 0, NULL);

    XMapWindow(m_display, m_xWindow);
    XFlush(m_display);

    XFree(scopedVisualInfo);
    return true;
}

void GraphicsContext::releaseNativeSystem()
{
    if (m_listConfigs)
        XFree(m_listConfigs);

    if (m_xColorMap)
        XFreeColormap(m_display, m_xColorMap);

    if (m_xWindow)
        XDestroyWindow(m_display, m_xWindow);

    if (m_display)
        XCloseDisplay(m_display);
}

bool GraphicsContext::acquireGLSystem()
{
    m_window = glXCreateWindow(m_display, m_config, m_xWindow, NULL);
    if (!m_window) {
        printf("%s: %s (%i): ERROR - Invalid glxWindow\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    const int pbuffer_attribs[] =
      {
        GLX_PBUFFER_WIDTH, 1,
        GLX_PBUFFER_HEIGHT, 1,
        None
      };

    m_pbuffer = glXCreatePbuffer(m_display, m_config, pbuffer_attribs);
    if (!m_window) {
        printf("%s: %s (%i): ERROR - Invalid glxPbuffer\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    m_context = glXCreateNewContext(m_display, m_config, GLX_RGBA_TYPE, NULL, true);
    if (!m_context) {
        printf("%s: %s (%i): ERROR - Invalid glxContext\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

void GraphicsContext::releaseGLSystem()
{
    glXMakeContextCurrent(m_display, None, None, NULL);

    if (m_context)
        glXDestroyContext(m_display, m_context);

    if (m_pbuffer)
        glXDestroyPbuffer(m_display, m_pbuffer);

    if (m_window)
        glXDestroyWindow(m_display, m_window);
}
