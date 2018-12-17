#pragma once
#include "Stage.h"
#include "IBlock.h"

class Stage4 :
	public Stage
{
public:
	Stage4(Data data);
	~Stage4();
	void GiveUp();
	void ReGame();
	void ChangeScene();
	bool CanRegame();

	void OnUpdate();
};