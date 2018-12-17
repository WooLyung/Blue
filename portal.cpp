#include "pch.h"
#include "portal.h"


portal::portal(float x, float y)
{
	type = PORTAL;

	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Blocks/portal/portal.png");
	AttachComponent<AABBCollider>()->SetRect(GetComponent<SpriteRenderer>()->visibleRect)->SetOnCollisionListener([](Entity* other) {});
	AttachComponent<RigidBody>(true, false)->ignore = true;

	this->SetPos(Vec2F(x, y));
}


portal::~portal()
{
}

void portal::OnUpdate()
{

}