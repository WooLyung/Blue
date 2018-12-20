#pragma once
#include "pch.h"
#include "foothold.h"

foothold::foothold(float x, float y, DIR2 dir)
{
	type = FOOTHOLD;

	switch (dir)
	{
		case TOP:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/top/foothold_top_normal.png");
			this->SetPos(Vec2F(x, y));
			break;
		case BOTTOM:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/bottom/foothold_bottom_normal.png");
			this->SetPos(Vec2F(x, y + 213));
			break;
		case RIGHT:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/right/foothold_right_normal.png");
			this->SetPos(Vec2F(x + 213, y));
			break;
		case LEFT:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/left/foothold_left_normal.png");
			this->SetPos(Vec2F(x, y));
			break;
	}
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false)->ignore = true;
	this->dir = dir;
}

foothold::~foothold()
{
}

void foothold::OnUpdate()
{
	bool lasted = isActive;

	if (isRelative)
	{
		pos.x = owner->pos.x + relativePos.x;
		pos.y = owner->pos.y + relativePos.y;
	}

	if (this->dir == BOTTOM && GetComponent<RigidBody>()->isTouchingTop
		|| this->dir == LEFT && GetComponent<RigidBody>()->isTouchingRight
		|| this->dir == RIGHT && GetComponent<RigidBody>()->isTouchingLeft
		|| this->dir == TOP && GetComponent<RigidBody>()->isTouchingBottom)
	{
		isActive = true;
		switch (this->dir)
		{
			case TOP:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/top/foothold_top_pushed.png");
				break;
			case BOTTOM:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/bottom/foothold_bottom_pushed.png");
				break;
			case RIGHT:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/right/foothold_right_pushed.png");
				break;
			case LEFT:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/left/foothold_left_pushed.png");
				break;
		}
	}
	else
	{
		isActive = false;
		switch (this->dir)
		{
		case TOP:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/top/foothold_top_normal.png");
			break;
		case BOTTOM:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/bottom/foothold_bottom_normal.png");
			break;
		case RIGHT:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/right/foothold_right_normal.png");
			break;
		case LEFT:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/foothold/left/foothold_left_normal.png");
			break;
		}
	}

	if (isActive != lasted)
	{
		if (isActive)
			RG2SoundManager->Play(SoundID::sButtonDown, false, false);
		else
			RG2SoundManager->Play(SoundID::sButtonUp, false, false);
	}
}
