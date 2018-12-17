#pragma once
#include "pch.h"
#include "movingBlock.h"

movingBlock::movingBlock(float x, float y, const string &path, Vec2F pos1, Vec2F pos2, bool dir, float speed)
{
	type = MOVINGBLOCK;

	AttachComponent<SpriteRenderer>()->SetTexture(path);
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false);

	this->SetPos(Vec2F(x, y));
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->dir = dir;
	this->speed = speed;
	this->defaultValue = false;
	this->isActive = false;
	this->allActive = true;

	switchList = new list<switchs*>;
}

movingBlock::movingBlock(float x, float y, const string &path, Vec2F pos1, Vec2F pos2, bool dir, float speed, bool default)
{
	type = MOVINGBLOCK;

	AttachComponent<SpriteRenderer>()->SetTexture(path);
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false);

	this->SetPos(Vec2F(x, y));
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->dir = dir;
	this->speed = speed;
	this->defaultValue = default;
	this->isActive = false;
	this->allActive = true;

	switchList = new list<switchs*>;
}

movingBlock::~movingBlock()
{
}

void movingBlock::OnUpdate()
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

	if (isActive != this->defaultValue)
	{
		if (dir)
		{
			float angle = atan2(pos2.y - pos.y, pos2.x - pos.x);
			float velocityX = speed * cos(angle) * DT;
			float velocityY = speed * sin(angle) * DT;

			pos.x += velocityX;
			pos.y += velocityY;

			if ((velocityX >= 0 && pos.x >= pos2.x
				|| velocityX <= 0 && pos.x <= pos2.x) // 목표지점의 x보다 더 갔을 때
				&& (velocityY >= 0 && pos.y >= pos2.y
					|| velocityY <= 0 && pos.y <= pos2.y)) // 목표지점의 y보다 더 갔을 때
			{
				dir = POS1;
				pos = pos2;
			}
		}
		else
		{
			float angle = atan2(pos1.y - pos.y, pos1.x - pos.x);
			float velocityX = speed * cos(angle) * DT;
			float velocityY = speed * sin(angle) * DT;

			pos.x += velocityX;
			pos.y += velocityY;

			if ((velocityX >= 0 && pos.x >= pos1.x
				|| velocityX <= 0 && pos.x <= pos1.x) // 목표지점의 x보다 더 갔을 때
				&& (velocityY >= 0 && pos.y >= pos1.y
					|| velocityY <= 0 && pos.y <= pos1.y)) // 목표지점의 y보다 더 갔을 때
			{
				dir = POS2;
				pos = pos1;
			}
		}
	}
}