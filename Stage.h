#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <string>

#include "Scene.h"
#include "IBlock.h"

#include "pch.h"
#include "Camera.h"
#include "End.h"

#include "player.h"
#include "Button.h"
#include "blue.h"

#include "block.h"
#include "moveableBlock.h"
#include "movingBlock.h"
#include "foothold.h"
#include "lever.h"
#include "door.h"
#include "jumper.h"
#include "fan.h"
#include "button.h"
#include "portal.h"

#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"
#include "AABBCollider.h"
#include "TextRenderer.h"
#include "UI.h"
#include "Particle.h"

#include "wind.h"

class Stage :
	public Scene
{
public:
	virtual void OnUpdate() override;
	virtual void GiveUp() = 0;
	virtual void ReGame() = 0;
	virtual void ChangeScene() = 0;
	virtual bool CanRegame() = 0;

	list<IBlock*> *blocks;
	list<Entity*> *particles;
	Player *player;
	blue *blueEntity;
	Camera *cam;

	Data data;
	Entity *fade;
	Entity *text;
	Entity *debug;
	Entity *background[7];
	Entity *frontground[2];
	float fadeTime = 0;
	bool isGiveup = false;
	bool isGameover = false;
	bool isNextstage = false;
	float endPos;
};