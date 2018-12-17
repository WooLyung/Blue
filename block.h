#pragma once
#include "IBlock.h"
#include "switchs.h"
#include <string>

class block :
	public IBlock
{
public:
	block(float x, float y, const string &path);
	~block();

	void OnUpdate();
};

