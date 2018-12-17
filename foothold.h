#pragma once
#include "switchs.h"

class foothold :
	public switchs
{
public:
	foothold(float x, float y, DIR2 dir);
	~foothold();

	void OnUpdate();
};

