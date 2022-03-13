#pragma once
#include <GL/glew.h>

// #ifdef _DEBUG
#define CheckedGLCall(x)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        PrintOpenGLErrors(">>BEFORE<< " #x, __FILE__, __LINE__);                                                       \
        (x);                                                                                                           \
        PrintOpenGLErrors(#x, __FILE__, __LINE__);                                                                     \
    } while (0)
#define CheckedGLResult(x)                                                                                             \
    (x);                                                                                                               \
    PrintOpenGLErrors(#x, __FILE__, __LINE__);
#define CheckExistingErrors(x) PrintOpenGLErrors(">>BEFORE<< " #x, __FILE__, __LINE__);
// #else
// #define CheckedGLCall(x) (x)
// #define CheckExistingErrors(x)
// #endif

void PrintOpenGLErrors(char const *const Function, char const *const File, int const Line);

void PrintShaderInfoLog(GLint const Shader);
