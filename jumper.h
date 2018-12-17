#pragma once
#include "IBlock.h"
#include "switchs.h"

class jumper :
	public IBlock
{
public:
	jumper(float x, float y, float power);
	~jumper();

	void OnUpdate();

	bool isRelative = false;
	Entity *owner;
	Vec2F relativePos;
	float power;
	float cooltime = 0;
};

