#pragma once
#include "Stage.h"
#include "Camera.h"
#include "Stage.h"
#include "TextRenderer.h"
#include "Scene.h"

class Intro :
	public Scene
{
public:
	Intro();
	~Intro();
	void OnUpdate();

	Camera *cam;
	Entity *fade;
	float fadeTime;
	int img = 0;

	Entity* imgEntity[8];
	float imgAppear[7] = { -1, -1, -1, -1, -1, -1, -1 };
};

