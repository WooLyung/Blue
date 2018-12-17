#pragma once
#include "Component.h"

class Particle :
	public Component
{
public:
	bool isDelete = false;
public:
	Particle(Entity * owner);
	virtual ~Particle() override;

public:
	virtual std::type_index GetID(void) override { return typeid(Particle); }
	static std::type_index GetFamilyID(void) { return typeid(Particle); }

	void OnUpdate(void) override;
};

