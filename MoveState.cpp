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
	if (animation == ANIMATION::PULL_LEFT || animation == ANIMATION::PULL_RIGHT)
	{
		RG2SoundManager->Play(SoundID::sDrag, true, false);
		RG2SoundManager->Play(SoundID::sWalk, true, false);
		RG2SoundManager->Stop(SoundID::sPush);
		RG2SoundManager->Stop(SoundID::sRun);
	}
	else if (animation == ANIMATION::PUSH_LEFT || animation == ANIMATION::PUSH_RIGHT)
	{
		RG2SoundManager->Play(SoundID::sPush, true, false);
		RG2SoundManager->Play(SoundID::sWalk, true, false);
		RG2SoundManager->Stop(SoundID::sDrag);
		RG2SoundManager->Stop(SoundID::sRun);
	}
	else if (animation == ANIMATION::WALK_LEFT || animation == ANIMATION::WALK_RIGHT)
	{
		RG2SoundManager->Play(SoundID::sWalk, true, false);
		RG2SoundManager->Stop(SoundID::sPush);
		RG2SoundManager->Stop(SoundID::sRun);
		RG2SoundManager->Stop(SoundID::sDrag);
	}
	else if (animation == ANIMATION::RUN_LEFT || animation == ANIMATION::RUN_RIGHT)
	{
		RG2SoundManager->Play(SoundID::sRun, true, false);
		RG2SoundManager->Stop(SoundID::sPush);
		RG2SoundManager->Stop(SoundID::sDrag);
		RG2SoundManager->Stop(SoundID::sWalk);
	}
	else
	{
		RG2SoundManager->Stop(SoundID::sRun);
		RG2SoundManager->Stop(SoundID::sPush);
		RG2SoundManager->Stop(SoundID::sDrag);
		RG2SoundManager->Stop(SoundID::sWalk);
	}
}