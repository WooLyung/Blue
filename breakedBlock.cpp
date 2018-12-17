#include "pch.h"
#include "breakedBlock.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "Particle.h"

breakedBlock::breakedBlock(float x, float y)
{
	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Particles/breakedBlock.png");
	AttachComponent<RigidBody>(false, true)->isTopview = true;
	AttachComponent<Particle>();
	this->pos = Vec2F(x, y);
	rotation = Random(0, 360);
	SetRotationCenter(Vec2F(128, 128));
}

breakedBlock::~breakedBlock()
{
}

void breakedBlock::OnUpdate()
{
	if (GetComponent<RigidBody>()->velocityX == 0
		&& GetComponent<RigidBody>()->velocityY == 0)
	{
		GetComponent<Particle>()->isDelete = true;
	}
	rotation += 36 * DT;
}