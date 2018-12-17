#pragma once
#include "Entity.h"
#include "MoveState.h"

class blue :
	public Entity
{
public:
	blue();
	~blue();

	void OnUpdate();
};