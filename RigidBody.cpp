#include "pch.h"
#include "RigidBody.h"

RigidBody::RigidBody(Entity * owner, bool isFixed, bool isGravityEnabled)
	:Component(owner), isFixed(isFixed), isGravityEnabled(isGravityEnabled),
	airResistance(30.f), velocityX(0.f), velocityY(0.f),
	isTouchingBottom(false),
	isTouchingTop(false),
	isTouchingRight(false),
	isTouchingLeft(false)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::OnUpdate(void)
{
	if (!isFixed)
	{
		if (!isTopview)
		{
			if (isGravityEnabled)
			{
				velocityY += AG_PER_DT;
			}
			if (velocityX > 0)
			{
				velocityX -= airResistance * DT;
				if (velocityX < 0)
					velocityX = 0;
			}
			else if (velocityX < 0)
			{
				velocityX += airResistance * DT;
				if (velocityX > 0)
					velocityX = 0;
			}
		}
		else
		{
			float angle = atan2(velocityY, velocityX);
			if (velocityX > 0)
			{
				velocityX -= airResistance * DT * cos(angle);
				if (velocityX < 0)
					velocityX = 0;
			}
			else if (velocityX < 0)
			{
				velocityX -= airResistance * DT * cos(angle);
				if (velocityX > 0)
					velocityX = 0;
			}
			if (velocityY > 0)
			{
				velocityY -= airResistance * DT * sin(angle);
				if (velocityY < 0)
					velocityY = 0;
			}
			else if (velocityY < 0)
			{
				velocityY -= airResistance * DT * sin(angle);
				if (velocityY > 0)
					velocityY = 0;
			}
		}
	}
	if (velocityX >= 100)
		velocityX = 100;
	else if (velocityX <= -100)
		velocityX = -100;
	if (velocityY >= 100)
		velocityY = 100;
	else if (velocityY <= -100)
		velocityY = -100;

	GetOwner()->pos.x += velocityX;
	GetOwner()->pos.y += velocityY;
}

