#ifndef YMSE_GL_H
#define YMSE_GL_H

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif

#define GLEW_STATIC
#include <GL/glew.h>


#ifdef __MACH__

#include <OpenGL/gl.h>

#elif defined(_WIN32)

#include "lean_windows.h"
#include <GL/gl.h>

#else

#include <GL/gl.h>

#endif

#endif
