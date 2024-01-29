#pragma once

class Object
{
public:
	virtual void Start() = 0;
	virtual void Tick(double deltaTime) = 0;
	virtual void Destroy() = 0;

public:
	virtual ~Object() {}
};