#include "pch.h"
#include "Particle.h"

Particle::Particle(Entity * owner)
	:Component(owner)
{
}

Particle::~Particle()
{
}

void Particle::OnUpdate(void)
{
}