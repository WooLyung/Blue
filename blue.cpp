#include "pch.h"
#include "blue.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"
#include "RigidBody.h"
#include "AABBCollider.h"
#include "Effect.h"
#include "UI.h"

blue::blue()
{
	AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Entities/blue/blue.png");

	Entity *back = new Entity();
	back->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/fade.png");
	back->SetPos(Vec2F(-1200, 0));
	AddChild(back);

	this->SetPos(Vec2F(0, 0));
	this->SetScale(Vec2F(100/16.f, 100/16.f));
}


blue::~blue()
{

}

void blue::OnUpdate()
{
}