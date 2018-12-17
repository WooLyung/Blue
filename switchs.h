#pragma once
#include "IBlock.h"

enum DIR2
{
	TOP = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 3
};

class switchs :
	public IBlock
{
public:
	bool isActive = false;
	bool isRelative = false;
	Entity *owner;
	Vec2F relativePos;
	DIR2 dir;
};

