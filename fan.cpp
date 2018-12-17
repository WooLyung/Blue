#pragma once
#include "pch.h"
#include "fan.h"

fan::fan(float x, float y, float angle, float power, float range)
{
	type = FAN;

	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/fan/fan_active.png");
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false);

	this->SetPos(Vec2F(x, y));
	this->angle = angle;
	this->power = power;
	this->range = range;
	this->defaultValue = false;
	this->isActive = false;
	this->allActive = true;

	switchList = new list<switchs*>;
}

fan::fan(float x, float y, float angle, float power, float range, bool defaultValue)
{
	type = FAN;

	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/fan/fan_active.png");
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false);

	this->SetPos(Vec2F(x, y));
	this->angle = angle;
	this->power = power;
	this->range = range;
	this->defaultValue = defaultValue;
	this->isActive = false;
	this->allActive = true;

	switchList = new list<switchs*>;
}

fan::~fan()
{
}

void fan::OnUpdate()
{
	if (allActive)
		isActive = true;
	else
		isActive = false;

	for each(switchs* obj in *switchList)
	{
		if (allActive)
			isActive = (isActive && obj->isActive);
		else
			isActive = (isActive || obj->isActive);
	}

	if (isActive != defaultValue)
	{
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/fan/fan_active.png");
	}
	else
	{
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/fan/fan_inactive.png");
	}
}