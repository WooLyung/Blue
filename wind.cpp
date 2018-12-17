#include "pch.h"
#include "wind.h"
#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "Particle.h"

wind::wind(float x, float y)
{
	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Particles/wind.png");
	AttachComponent<RigidBody>(false, true)->isTopview = true;
	AttachComponent<Particle>();
	this->pos = Vec2F(x, y);
	rotation = Random(0, 360);
	SetRotationCenter(Vec2F(128, 128));
}

wind::~wind()
{
}

void wind::OnUpdate()
{
	if (GetComponent<RigidBody>()->velocityX == 0
		&& GetComponent<RigidBody>()->velocityY == 0)
	{
		GetComponent<Particle>()->isDelete = true;
	}
	rotation += 360 * DT;
}