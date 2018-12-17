#pragma once
#include "Entity.h"

class MoveState
{
public:
	MoveState(Entity *owner);
	~MoveState();

	void OnUpdate(Entity *grappedBlock);

	Entity *owner;
	bool isRightDir = true;
	bool isPush = false;
	bool isGrap = false;
	bool isNextBlock = false;
	float standTime = 0;
	int animation = IDLE_RIGHT;
	int state = STAND;

	enum ANIMATION
	{
		RUN_RIGHT, IDLE_RIGHT, WALK_RIGHT, PUSH_RIGHT, GRAP_RIGHT, JUMP_RIGHT, DOWN_RIGHT, PULL_RIGHT, FORCE_RIGHT,
		RUN_LEFT, IDLE_LEFT, WALK_LEFT, PUSH_LEFT, GRAP_LEFT, JUMP_LEFT, DOWN_LEFT, PULL_LEFT, FORCE_LEFT
	};

	enum STATE
	{
		STAND, WALK, RUN
	};
};

