#pragma once
#include "Entity.h"
#include "MoveState.h"
#include "IBlock.h"

class Player :
	public Entity
{
public:
	Player();
	~Player();

	MoveState *moveState;
	IBlock *grappedBlock;

	void OnUpdate();
	void Move();
};