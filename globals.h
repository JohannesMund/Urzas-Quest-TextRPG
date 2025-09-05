#pragma once
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#define _USE_WINDOWS
#else
#define _USE_UNIX
#endif