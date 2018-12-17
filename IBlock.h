#pragma once
#include "Entity.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "AABBCollider.h"
#include "Effect.h"
#include <list>

enum TYPE
{
	BLOCK,
	MOVEABLEBLOCK,
	MOVINGBLOCK,
	FOOTHOLD,
	DOOR,
	LEVER,
	JUMPER,
	FAN,
	BUTTON,
	PORTAL
};

class IBlock :
	public Entity
{
public:
	void OnUpdate() = 0;
	int type;
};
