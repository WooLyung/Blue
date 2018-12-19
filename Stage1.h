#pragma once
#include "Stage.h"
#include "IBlock.h"

class Stage1 :
	public Stage
{
public:
	Stage1(Data data);
	~Stage1();
	void GiveUp();
	void ReGame();
	void ChangeScene();
	bool CanRegame();

	void OnUpdate();

	Entity* hints[17];
	bool hint = false;
};