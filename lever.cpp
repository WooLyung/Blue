#pragma once
#include "pch.h"
#include "lever.h"

lever::lever(float x, float y, DIR2 dir)
{
	type = LEVER;

	switch (dir)
	{
		case TOP:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/top/lever_top_off.png");
			break;
		case BOTTOM:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/bottom/lever_bottom_off.png");
			break;
		case RIGHT:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/right/lever_right_off.png");
			break;
		case LEFT:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/left/lever_left_off.png");
			break;
	}
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false)->ignore = true;

	isActive = false;
	this->dir = dir;

	this->SetPos(Vec2F(x, y));
}

lever::lever(float x, float y, DIR2 dir, bool defaultValue)
{
	type = LEVER;

	switch (dir)
	{
		case TOP:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/top/lever_top_off.png");
			break;
		case BOTTOM:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/bottom/lever_bottom_off.png");
			break;
		case RIGHT:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/right/lever_right_off.png");
			break;
		case LEFT:
			AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/left/lever_left_off.png");
			break;
	}
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false)->ignore = true;

	isActive = defaultValue;
	this->dir = dir;

	this->SetPos(Vec2F(x, y));
}


lever::~lever()
{
}

void lever::OnUpdate()
{
	if (isRelative)
	{
		pos.x = owner->pos.x + relativePos.x;
		pos.y = owner->pos.y + relativePos.y;
	}

	if (isActive)
	{
		switch (dir)
		{
			case TOP:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/top/lever_top_on.png");
				break;
			case BOTTOM:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/bottom/lever_bottom_on.png");
				break;
			case RIGHT:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/right/lever_right_on.png");
				break;
			case LEFT:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/left/lever_left_on.png");
				break;
		}
	}
	else
	{
		switch (dir)
		{
			case TOP:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/top/lever_top_off.png");
				break;
			case BOTTOM:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/bottom/lever_bottom_off.png");
				break;
			case RIGHT:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/right/lever_right_off.png");
				break;
			case LEFT:
				GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/lever/left/lever_left_off.png");
				break;
		}
	}
}
