#pragma once

#ifdef ME_PLATFORM_WINDOWS

#ifdef ME_BUILD_DLL
#define ME_API __declspec(dllexport)
#else
#define ME_API __declspec(dllimport)
#endif

#else
#error Mimou Engine only support Windows at this point

#endif

#define BIT(x) (1<<x)