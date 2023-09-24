#pragma once

#include "LWEngine/Core/PlatformDetection.h"

#ifdef LWE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

//. Basics
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>

//#include <fstream>
//#include <chrono>
//#include <sys/types.h>
//#include <sys/stat.h>

//. Data structures
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>

//. Headers
#include "LWEngine/Core/Core.h"
#include "LWEngine/Core/Log.h"
#include "LWEngine/Dev/Instrumentor.h"

#ifdef LWE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // LWE_PLATFORM_WINDOWS

