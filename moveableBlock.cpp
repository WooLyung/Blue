#pragma once
#include "pch.h"
#include "moveableBlock.h"

moveableBlock::moveableBlock(float x, float y, const string &path)
{
	type = MOVEABLEBLOCK;

	AttachComponent<SpriteRenderer>()->SetTexture(path);
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(false, true);

	this->SetPos(Vec2F(x, y));
}
void moveableBlock::OnUpdate() {
	if (isRelative)
	{
		pos.x = owner->pos.x + relativePos.x;
		pos.y = owner->pos.y + relativePos.y;
	}
}

moveableBlock::~moveableBlock()
{
}
