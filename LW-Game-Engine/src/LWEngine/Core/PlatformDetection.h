#ifdef _WIN32
	#ifdef _WIN64
		#define LWE_PLATFORM_WINDOWS
	#else
		#error 'ERROR::BUILD::x64_IS_NOT_SUPPORTED'
#endif

#elif defined(__APPLE__) || defined(__MACH__)
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "ERROR::BUILD::IOS_SIMULATOR_IS_NOT_SUPPORTED"

	#elif TARGET_OS_IPHONE == 1
		#define LWE_PLATFORM_IOS
		#error "ERROR::BUILD::IOS_IS_NOT_SUPPORTED"

	#elif TARGET_OS_MAC == 1
		#define LWE_PLATFORM_MACOS
		#error "ERROR::BUILD::MACOS_IS_NOT_SUPPORTED"

	#else
		#error "ERROR::BUILD::UNKNOWN_APPLE_PLATFORM"
	#endif

#elif defined(__ANDROID__)
	#define LWE_PLATFORM_ANDROID
	#error "ERROR::BUILD::ANDROID_IS_NOT_SUPPORTED"

#elif defined(__linux__)
	#define LWE_PLATFORM_LINUX
	#error "ERROR::BUILD::LINUX_IS_NOT_SUPPORTED"

#else
	#error "ERROR::BUILD::UNKNOWN_PLATFORM"
#endif
