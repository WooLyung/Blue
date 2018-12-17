#pragma once
#include "Entity.h"
class StartButton :
	public Entity
{
public:
	StartButton(Scene *mainmenu);
	~StartButton();

	void SetOnClickListener(std::function<void()> callback);
	Scene *mainmenu;
};