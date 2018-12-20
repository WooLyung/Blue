#pragma once
#include "Stage.h"
#include "Camera.h"
#include "Stage.h"
#include "TextRenderer.h"
#include "Scene.h"

class End :
	public Scene
{
public:
	End(Data data);
	~End();
	void OnUpdate();

	Camera *cam;
	Entity *fade;
	float fadeTime;
	int img = 0;
	char rank;

	Entity* imgEntity[11];
	float imgAppear[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
};

