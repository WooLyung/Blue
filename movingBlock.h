#pragma once
#include "IBlock.h"
#include "switchs.h"

class movingBlock :
	public IBlock
{
public:
	movingBlock(float x, float y, const string &path, Vec2F pos1, Vec2F pos2, bool dir, float speed);
	movingBlock(float x, float y, const string &path, Vec2F pos1, Vec2F pos2, bool dir, float speed, bool default);
	~movingBlock();

	void OnUpdate();

	enum DIR
	{
		POS1 = 0, POS2 = 1
	};

	list<switchs*> *switchList;
	bool defaultValue;
	bool allActive;

private:
	Vec2F pos1, pos2;
	bool dir;
	bool isActive;
	float speed;
};

