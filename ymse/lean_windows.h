#ifndef YMSE_LEAN_WINDOWS_H
#define YMSE_LEAN_WINDOWS_H

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>

#endif

#endif
