#pragma once
#include "IBlock.h"
#include "switchs.h"

class fan :
	public IBlock
{
public:
	fan(float x, float y, float angle, float power, float range);
	fan(float x, float y, float angle, float power, float range, bool default);
	~fan();

	void OnUpdate();

	float angle;
	float power;
	float range;
	bool defaultValue = false;
	bool isActive;
	bool allActive;

	list<switchs*> *switchList;
};

