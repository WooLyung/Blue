#pragma once
#include "Entity.h"
class EndButton :
	public Entity
{
public:
	EndButton(Scene *mainmenu);
	~EndButton();

	void SetOnClickListener(std::function<void()> callback);
	Scene *mainmenu;
};