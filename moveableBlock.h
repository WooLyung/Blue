#pragma once
#include "IBlock.h"
#include "switchs.h"

class moveableBlock :
	public IBlock
{
public:
	moveableBlock(float x, float y, const string &path);
	~moveableBlock();

	void OnUpdate();

	bool isRelative = false;
	Entity *owner;
	Vec2F relativePos;
};

