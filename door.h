#pragma once
#include "IBlock.h"
#include "switchs.h"

class door :
	public IBlock
{
public:
	door(float x, float y, const string &path, Vec2F pos1, Vec2F pos2, float speed);
	~door();

	void OnUpdate();

	enum DIR
	{
		POS1 = 0, POS2 = 1
	};

	list<switchs*> *switchList;
	bool allActive;

private:
	Vec2F pos1, pos2;
	bool isActive;
	float speed;
};

