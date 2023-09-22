#pragma once

//. Basics
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

//. Data structures
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>

//. Headers
#include "LWEngine/Core/Log.h"
#include "LWEngine/Dev/Instrumentor.h"

#ifdef LWE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // LWE_PLATFORM_WINDOWS

