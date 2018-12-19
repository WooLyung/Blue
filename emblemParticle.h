#pragma once
#include "Entity.h"
class emblemParticle :
	public Entity
{
public:
	emblemParticle(float x, float y, const string &path);
	~emblemParticle();

	void OnUpdate();
};

