#include "pch.h"
#include "MoveState.h"

MoveState::MoveState(Entity *owner)
{
	this->owner = owner;
}

MoveState::~MoveState()
{
}

void MoveState::OnUpdate(Entity *grappedBlock)
{
	if (RG2Input->GetKeyState(KeyCode::KEY_RIGHT) == KeyState::KEYSTATE_STAY)
	{
		isRightDir = !(isNextBlock && owner->pos.x >= grappedBlock->pos.x);
		
		if ((standTime <= 0.2f && state == STAND || state == RUN) && !isPush)
			state = RUN;
		else
			state = WALK;

		standTime = 0;
	}
	else if (RG2Input->GetKeyState(KeyCode::KEY_LEFT) == KeyState::KEYSTATE_STAY)
	{
		isRightDir = (isNextBlock && owner->pos.x <= grappedBlock->pos.x);

		if ((standTime <= 0.2f && state == STAND || state == RUN) && !isPush)
			state = RUN;
		else
			state = WALK;

		standTime = 0;
	}
	else
	{
		standTime += DT;
		state = STAND;
	}

	if (RG2Input->GetKeyState(KeyCode::KEY_LCONTROL) == KeyState::KEYSTATE_STAY)
		isGrap = true;
	else
		isGrap = false;
}