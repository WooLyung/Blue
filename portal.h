#pragma once
#include "IBlock.h"
class portal :
	public IBlock
{
public:
	portal(float x, float y);
	~portal();

	void OnUpdate();

	portal *target = NULL;
};

