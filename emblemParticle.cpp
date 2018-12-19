#include "pch.h"
#include "emblemParticle.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "Particle.h"

emblemParticle::emblemParticle(float x, float y, const string &path)
{
	AttachComponent<SpriteRenderer>()->SetTexture(path);
	AttachComponent<RigidBody>(false, true)->isTopview = true;
	AttachComponent<Particle>();
	this->pos = Vec2F(x, y);
	rotation = Random(0, 360);
	SetRotationCenter(Vec2F(128, 128));
}

emblemParticle::~emblemParticle()
{
}

void emblemParticle::OnUpdate()
{
	if (GetComponent<RigidBody>()->velocityX == 0
		&& GetComponent<RigidBody>()->velocityY == 0)
	{
		GetComponent<Particle>()->isDelete = true;
	}
	rotation += 36 * DT;
}