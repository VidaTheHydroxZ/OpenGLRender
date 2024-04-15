#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) // # before x turns the x into a string, __FILE__ and __LINE__ are for all compilers

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
