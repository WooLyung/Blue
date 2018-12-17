#pragma once
#include "Stage.h"
#include "IBlock.h"

class Stage3 :
	public Stage
{
public:
	Stage3(Data data);
	~Stage3();
	void GiveUp();
	void ReGame();
	void ChangeScene();
	bool CanRegame();

	void OnUpdate();

	Entity* darkness;
};