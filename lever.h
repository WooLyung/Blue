#pragma once
#include "switchs.h"

class lever :
	public switchs
{
public:
	lever(float x, float y, DIR2 dir);
	lever(float x, float y, DIR2 dir, bool defaultValue);
	~lever();

	void OnUpdate();
};

