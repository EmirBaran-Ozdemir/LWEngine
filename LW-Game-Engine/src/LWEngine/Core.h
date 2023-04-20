#pragma once

#ifdef LWE_PLATFORM_WINDOWS
	#ifdef LWE_BUILD_DLL
		#define LWE_API __declspec(dllexport)
	#else		
		#define LWE_API __declspec(dllimport)
	#endif
#else
	#error LWEngine only supports Windows
#endif

#define BIT(x) (1<<x)