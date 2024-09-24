#pragma once
#include <iostream>
#include <string>

#ifdef D_DEBUG
	#ifndef ENABLE_LOG_LIFETIME
		#define ENABLE_LOG_LIFETIME 1
	#endif
#endif

#ifdef D_DEBUG
	#define LOG(x) std::cout << "LOG: " << x << "\n";
#else
	#define LOG(x)
#endif