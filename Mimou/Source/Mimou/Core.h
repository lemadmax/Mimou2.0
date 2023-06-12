#pragma once

#ifdef ME_PLATFORM_WINDOWS
	#ifdef ME_BUILD_DLL
		#define ME_API __declspec(dllexport)
	#else
		#define ME_API __declspec(dllimport)
	#endif
#else
	#error Mimou only support Windows!
#endif