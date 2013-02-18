#include <dlfcn.h>

#define DISABLE_OPENGL_SHIMS
#include "OpenGLShims.h"


OpenGLFunctionTable* openGLFunctionTable()
{
    static OpenGLFunctionTable functionTable;
    return &functionTable;
}

typedef void* (*glGetProcAddressType) (const char *);

static void* getProcAddress (const char* procName)
{
    static bool initialized = false;
    static glGetProcAddressType getProcAddressFunction = 0;
    void* procAddressFunction = 0;

    if (!initialized) {
        getProcAddressFunction = reinterpret_cast<glGetProcAddressType>(dlsym(RTLD_DEFAULT, "glXGetProcAddress"));
        if (!getProcAddressFunction)
            getProcAddressFunction = reinterpret_cast<glGetProcAddressType>(dlsym(RTLD_DEFAULT, "glXGetProcAddressARB"));

        initialized = true;
    }

    procAddressFunction = dlsym(RTLD_DEFAULT, procName);
    if (!procAddressFunction && getProcAddressFunction)
        procAddressFunction = getProcAddressFunction(procName);

    return procAddressFunction;
}

static void* lookupOpenGLFunctionAddress (const char* functionName, bool functionCore, bool& success)
{
    if (!success)
        return 0;

    void* target = getProcAddress (functionName);
    if (target)
        return target;

    // A null address is still a failure case if it is core function.
    if (!target && functionCore)
        success = false;

    return target;
}

#define ASSIGN_FUNCTION_TABLE_ENTRY(FunctionName, success) \
    openGLFunctionTable()->FunctionName = reinterpret_cast<FunctionName##Type>(lookupOpenGLFunctionAddress(#FunctionName, true, success))

bool initializeOpenGLShims()
{
    static bool initialized = false;
    static bool success = true;

    if (initialized)
        return success;

    initialized = true;

    ASSIGN_FUNCTION_TABLE_ENTRY(glBindBuffer, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glBindFramebuffer, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glBufferData, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glClear, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glClearColor, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glDeleteBuffers, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glDisableVertexAttribArray, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glDrawArrays, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glEnableVertexAttribArray, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glGenBuffers, success);
    ASSIGN_FUNCTION_TABLE_ENTRY(glVertexAttribPointer, success);

    if (!success)
        fprintf(stderr, "Could not initialize OpenGL Shims\n");

    return success;
}

