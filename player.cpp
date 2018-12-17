#include "pch.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"
#include "RigidBody.h"
#include "AABBCollider.h"
#include "Effect.h"

Player::Player()
{
	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Entities/player/go/left/0.png")->SetEnabled(false);
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(false, true);
	AttachComponent<AnimationRenderer>();
	
	moveState = new MoveState(this);

	this->SetPos(Vec2F(0, 0));
}
void Player::OnUpdate()
{
	moveState->OnUpdate(grappedBlock);
	Move();
}

Player::~Player()
{
}

void Player::Move()
{
	if (moveState->state == MoveState::WALK) // 걸을 때
	{
		if (moveState->isRightDir) // 오른쪽으로 걸어가기
		{
			if (Abs(GetComponent<RigidBody>()->velocityY) <= 4.f && GetComponent<RigidBody>()->isTouchingBottom) // 높이의 변화가 없을 때
			{
				GetComponent<AnimationRenderer>()->Reset();
				GetComponent<AnimationRenderer>()->SetFPS(25);
				GetComponent<AnimationRenderer>()->SetLoop(true);
				if (moveState->isNextBlock)
				{
					GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/pull/right", 5, true);
					moveState->animation = MoveState::PULL_RIGHT;
					grappedBlock->pos.x -= 600 * DT;
					pos.x -= 100 * DT;
					return;
				}
				else if (moveState->isPush)
				{
					GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/push/right", 6, true);
					moveState->animation = MoveState::PUSH_RIGHT;
				}
				else
				{
;					GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/go/right", 14, true);
					moveState->animation = MoveState::WALK_RIGHT;
				}
			}

			if (GetComponent<RigidBody>()->isTouchingBottom)
				this->pos.x += 600 * DT;
			else
				this->pos.x += 500 * DT;
		}
		else // 왼쪽으로 걸어가기
		{
			if (Abs(GetComponent<RigidBody>()->velocityY) <= 4.f && GetComponent<RigidBody>()->isTouchingBottom) // 높이의 변화가 없을 때
			{
				GetComponent<AnimationRenderer>()->Reset();
				GetComponent<AnimationRenderer>()->SetFPS(25);
				GetComponent<AnimationRenderer>()->SetLoop(true);
				if (moveState->isNextBlock)
				{
					GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/pull/left", 5, true);
					moveState->animation = MoveState::PULL_LEFT;
					grappedBlock->pos.x += 600 * DT;
					pos.x += 100 * DT;
					return;
				}
				else if (moveState->isPush)
				{
					GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/push/left", 6, true);
					moveState->animation = MoveState::PUSH_LEFT;
				}
				else
				{
					GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/go/left", 14, true);
					moveState->animation = MoveState::WALK_LEFT;
				}
			}

			if (GetComponent<RigidBody>()->isTouchingBottom)
				this->pos.x -= 600 * DT;
			else
				this->pos.x -= 500 * DT;
		}
	}
	else if (moveState->state == MoveState::STAND) // 서있을 때
	{
		if (moveState->isRightDir) // 오른쪽으로 서있기
		{
			if (Abs(GetComponent<RigidBody>()->velocityY) <= 4.f && GetComponent<RigidBody>()->isTouchingBottom) // 높이의 변화가 없을 때
			{
				if (moveState->animation != MoveState::FORCE_RIGHT || GetComponent<AnimationRenderer>()->GetCurrentFrame() > 23)
				{
					GetComponent<AnimationRenderer>()->Reset();
					GetComponent<AnimationRenderer>()->SetFPS(5);
					GetComponent<AnimationRenderer>()->SetLoop(true);
					if (moveState->isNextBlock)
					{
						GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/grap/right", 1, true);
						moveState->animation = MoveState::GRAP_RIGHT;
					}
					else
					{
						moveState->animation = MoveState::IDLE_RIGHT;
						GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/idle/right", 2, true);
					}
				}
			}
		}
		else // 왼쪽으로 서있기
		{
			if (Abs(GetComponent<RigidBody>()->velocityY) <= 4.f && GetComponent<RigidBody>()->isTouchingBottom) // 높이의 변화가 없을 때
			{
				if (moveState->animation != MoveState::FORCE_LEFT || GetComponent<AnimationRenderer>()->GetCurrentFrame() > 23)
				{
					GetComponent<AnimationRenderer>()->Reset();
					GetComponent<AnimationRenderer>()->SetFPS(5);
					GetComponent<AnimationRenderer>()->SetLoop(true);
					if (moveState->isNextBlock)
					{
						GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/grap/left", 1, true);
						moveState->animation = MoveState::GRAP_LEFT;
					}
					else
					{
						moveState->animation = MoveState::IDLE_LEFT;
						GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/idle/left", 2, true);
					}
				}
			}
		}
	}
	else if (moveState->state == MoveState::RUN) // 뛸 때
	{
		if (moveState->isRightDir) // 오른쪽으로 뛰어가기
		{
			if (Abs(GetComponent<RigidBody>()->velocityY) <= 4.f && GetComponent<RigidBody>()->isTouchingBottom) // 높이의 변화가 없을 때
			{
				moveState->animation = MoveState::RUN_RIGHT;
				GetComponent<AnimationRenderer>()->Reset();
				GetComponent<AnimationRenderer>()->SetFPS(25);
				GetComponent<AnimationRenderer>()->SetLoop(true);
				GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/run/right", 8, true);
			}

			if (GetComponent<RigidBody>()->isTouchingBottom)
				this->pos.x += 1200 * DT;
			else
				this->pos.x += 800 * DT;
		}
		else // 왼쪽으로 뛰어가기
		{
			if (Abs(GetComponent<RigidBody>()->velocityY) <= 4.f && GetComponent<RigidBody>()->isTouchingBottom) // 높이의 변화가 없을 때
			{
				moveState->animation = MoveState::RUN_LEFT;
				GetComponent<AnimationRenderer>()->Reset();
				GetComponent<AnimationRenderer>()->SetFPS(25);
				GetComponent<AnimationRenderer>()->SetLoop(true);
				GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/run/left", 8, true);
			}

			if (GetComponent<RigidBody>()->isTouchingBottom)
				this->pos.x -= 1200 * DT;
			else
				this->pos.x -= 800 * DT;
		}
	}

	if (RG2Input->GetKeyState(KeyCode::KEY_LSHIFT) == KeyState::KEYSTATE_STAY && GetComponent<RigidBody>()->isTouchingBottom) // 점프
	{
		GetComponent<RigidBody>()->velocityY = -25;
	}
	if (RG2Input->GetKeyState(KeyCode::KEY_Z) == KeyState::KEYSTATE_ENTER && grappedBlock != NULL) // 밀치기
	{
		if (moveState->isRightDir)
		{
			grappedBlock->GetComponent<RigidBody>()->velocityX = 36;
			GetComponent<AnimationRenderer>()->Reset();
			GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/force/right", 24, true);
			GetComponent<AnimationRenderer>()->SetLoop(false);
			GetComponent<AnimationRenderer>()->SetFPS(60);
			moveState->animation = MoveState::FORCE_RIGHT;
		}
		else
		{
			grappedBlock->GetComponent<RigidBody>()->velocityX = -36;
			GetComponent<AnimationRenderer>()->Reset();
			GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/force/left", 24, true);
			GetComponent<AnimationRenderer>()->SetLoop(false);
			GetComponent<AnimationRenderer>()->SetFPS(60);
			moveState->animation = MoveState::FORCE_LEFT;
		}

		grappedBlock = NULL;
	}
	if (GetComponent<RigidBody>()->velocityY >= 4.f && (moveState->animation != MoveState::FORCE_RIGHT || GetComponent<AnimationRenderer>()->GetCurrentFrame() > 23)) // 추락
	{
		if (moveState->isRightDir) // 오른쪽으로 추락
		{
			moveState->animation = MoveState::DOWN_RIGHT;
			GetComponent<AnimationRenderer>()->Reset();
			GetComponent<AnimationRenderer>()->SetLoop(true);
			GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/down/right", 1, true);
		}
		else // 왼쪽으로 추락
		{
			moveState->animation = MoveState::DOWN_LEFT;
			GetComponent<AnimationRenderer>()->Reset();
			GetComponent<AnimationRenderer>()->SetLoop(true);
			GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/down/left", 1, true);
		}
	}
	else if (GetComponent<RigidBody>()->velocityY <= -4.f && (moveState->animation != MoveState::FORCE_RIGHT || GetComponent<AnimationRenderer>()->GetCurrentFrame() > 23)) // 상승
	{
		if (moveState->isRightDir) // 오른쪽으로 점프
		{
			moveState->animation = MoveState::JUMP_RIGHT;
			GetComponent<AnimationRenderer>()->Reset();
			GetComponent<AnimationRenderer>()->SetFPS(15);
			GetComponent<AnimationRenderer>()->SetLoop(false);
			GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/jump/right", 3, true);
		}
		else // 왼쪽으로 점프
		{
			moveState->animation = MoveState::JUMP_LEFT;
			GetComponent<AnimationRenderer>()->Reset();
			GetComponent<AnimationRenderer>()->SetFPS(15);
			GetComponent<AnimationRenderer>()->SetLoop(false);
			GetComponent<AnimationRenderer>()->PushTextures("Sprites/Entities/player/jump/left", 3, true);
		}
	}
}