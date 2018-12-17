#pragma once
#include "Entity.h"
class wind :
	public Entity
{
public:
	wind(float x, float y);
	~wind();

	void OnUpdate();
};

