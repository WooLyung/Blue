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
	Data data;
	Entity *fade;
	float fadeTime;
};

