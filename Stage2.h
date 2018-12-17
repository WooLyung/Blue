#pragma once
#include "Stage.h"
#include "IBlock.h"

class Stage2 :
	public Stage
{
public:
	Stage2(Data data);
	~Stage2();
	void GiveUp();
	void ReGame();
	void ChangeScene();
	bool CanRegame();

	void OnUpdate();
};