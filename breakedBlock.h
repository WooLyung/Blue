#pragma once
#include "Entity.h"
class breakedBlock :
	public Entity
{
public:
	breakedBlock(float x, float y);
	~breakedBlock();

	void OnUpdate();
};

