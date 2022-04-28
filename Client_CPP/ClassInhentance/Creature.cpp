#include "Creature.h"

void Creature::Breath()
{
	age++;
	Grow();
}

void Creature::Grow()
{
	mass++;
	height++;
}
