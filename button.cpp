#pragma once
#include "pch.h"
#include "button.h"

button::button(float x, float y, DIR2 dir, float dur)
{
	type = BUTTON;

	switch (dir)
	{
	case TOP:
		AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/top/button_top_normal.png");
		this->SetPos(Vec2F(x, y));
		break;
	case BOTTOM:
		AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/bottom/button_bottom_normal.png");
		this->SetPos(Vec2F(x, y + 205));
		break;
	case RIGHT:
		AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/right/button_right_normal.png");
		this->SetPos(Vec2F(x + 205, y));
		break;
	case LEFT:
		AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/left/button_left_normal.png");
		this->SetPos(Vec2F(x, y));
		break;
	}
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false)->ignore = true;
	this->dir = dir;
	this->dur = dur;
	this->cooltime = 0;
}

button::~button()
{
}

void button::OnUpdate()
{
	if (isRelative)
	{
		pos.x = owner->pos.x + relativePos.x;
		pos.y = owner->pos.y + relativePos.y;
	}

	if (cooltime > 0)
	{
		cooltime -= DT;
		if (cooltime <= 0)
		{
			cooltime = 0;
			isActive = false;
		}
	}

	if (this->dir == BOTTOM && GetComponent<RigidBody>()->isTouchingTop
		|| this->dir == LEFT && GetComponent<RigidBody>()->isTouchingRight
		|| this->dir == RIGHT && GetComponent<RigidBody>()->isTouchingLeft
		|| this->dir == TOP && GetComponent<RigidBody>()->isTouchingBottom)
	{
		cooltime = dur;
		isActive = true;
		switch (this->dir)
		{
		case TOP:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/top/button_top_pushed.png");
			break;
		case BOTTOM:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/bottom/button_bottom_pushed.png");
			break;
		case RIGHT:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/right/button_right_pushed.png");
			break;
		case LEFT:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/left/button_left_pushed.png");
			break;
		}
	}
	else if (!isActive)
	{
		switch (this->dir)
		{
		case TOP:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/top/button_top_normal.png");
			break;
		case BOTTOM:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/bottom/button_bottom_normal.png");
			break;
		case RIGHT:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/right/button_right_normal.png");
			break;
		case LEFT:
			GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/button/left/button_left_normal.png");
			break;
		}
	}
}
