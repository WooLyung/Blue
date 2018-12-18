#pragma once
#include "Stage.h"
#include "Camera.h"
#include "Stage.h"
#include "TextRenderer.h"
#include "Scene.h"

class Mainmenu :
	public Scene
{
public:
	Mainmenu();
	~Mainmenu();
	void OnUpdate();

	Camera *cam;
	Entity *fade;
	float fadeTime;
};
