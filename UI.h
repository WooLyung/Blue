#pragma once
#include "Component.h"
#include "Camera.h"

class UI :
	public Component
{
public:
	enum DIR
	{
		LEFT_TOP, LEFT_MIDDLE, LEFT_BOTTOM,
		MIDDLE_TOP, CENTER, MIDDLE_BOTTOM,
		RIGHT_TOP, RIGHT_MIDDLE, RIGHT_BOTTOM
	};

	Vec2F pos;
	DIR dir;
	Camera *cam;

public:
	UI(Entity* owner, Vec2F pos, DIR dir, Camera *cam);
	virtual ~UI() override;

public:
	virtual std::type_index GetID(void) override { return typeid(UI); }
	static std::type_index GetFamilyID(void) { return typeid(UI); }

	void OnUpdate(void) override;
};

