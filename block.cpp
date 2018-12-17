#pragma once
#include "pch.h"
#include "block.h"
#include "Effect.h"

block::block(float x, float y, const string &path)
{
	type = BLOCK;

	AttachComponent<SpriteRenderer>()->SetTexture(path);
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false);
	AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0)))->SetEnabled(true);

	this->SetPos(Vec2F(x, y));
}
void block::OnUpdate() {
}

block::~block()
{
}
