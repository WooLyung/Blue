#pragma once
#include "pch.h"
#include "jumper.h"

jumper::jumper(float x, float y, float power)
{
	type = JUMPER;

	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/jumper/jumper_pushed.png");
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false)->ignore = true;

	this->SetPos(Vec2F(x, y + 154));
	this->power = power;
	this->cooltime = 0;
}

jumper::~jumper()
{
}

void jumper::OnUpdate()
{
	if (isRelative)
	{
		pos.x = owner->pos.x + relativePos.x;
		pos.y = owner->pos.y + relativePos.y;
	}

	if (cooltime > 0)
	{
		cooltime -= DT;
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/jumper/jumper_pushed.png");
	}
	else
	{
		cooltime = 0;
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/jumper/jumper_up.png");
	}
}