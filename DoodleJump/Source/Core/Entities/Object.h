#pragma once
#include "Core/Base/Log.h"
#include <typeinfo>

#if ENABLE_LOG_LIFETIME == 1
	#define OBJECT_LOG_CONSTRUCTOR() LOG(("Object Constructor: " + std::string(DebugGetClassName())).c_str())
	#define OBJECT_LOG_DESTRUCTOR() LOG(("\033[33mObject Destructor: " + std::string(DebugGetClassName()) + "\033[0m").c_str())
#else
	#define OBJECT_LOG_CONSTRUCTOR()
	#define OBJECT_LOG_DESTRUCTOR()
#endif
class Object
{
public:
	virtual ~Object() {}

	virtual void Start() = 0;
	virtual void Tick(double deltaTime) = 0;
	virtual void Destroy() = 0;
protected:
	const char* DebugGetClassName()
	{
		return typeid(*this).name();
	}
};