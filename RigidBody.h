#pragma once
#include "Component.h"
//중력가속도(1초당)
#define AG (45.f)
//중력가속도(1프레임당)
#define AG_PER_DT (AG*DT)
class RigidBody :
	public Component
{
public:
	float velocityX;
	float velocityY;
	float airResistance;
	bool isFixed;
	bool isGravityEnabled;
	bool isTouchingBottom;
	bool isTouchingTop;
	bool isTouchingRight;
	bool isTouchingLeft;
	bool ignore = false;
	bool isTopview = false;

public:
	RigidBody(Entity* owner, bool isFixed = false, bool isGravityEnabled = true);
	virtual ~RigidBody() override;

public:
	virtual std::type_index GetID(void) override { return typeid(RigidBody); }
	static std::type_index GetFamilyID(void) { return typeid(RigidBody); }

	void OnUpdate(void) override;
};

