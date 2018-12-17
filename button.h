#pragma once
#include "switchs.h"

class button :
	public switchs
{
public:
	button(float x, float y, DIR2 dir, float dur);
	~button();

	float dur;
	float cooltime;

	void OnUpdate();
};

