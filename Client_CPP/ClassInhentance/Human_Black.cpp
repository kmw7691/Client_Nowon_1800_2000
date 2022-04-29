#include "Human_Black.h"
#include <iostream>
using namespace std;

void Human_Black::GoToGym()
{
	cout << "ÈæÀÎÀº Çï½ºÀå¿¡ °©´Ï´Ù" << endl;
}

void Human_Black::Grow()
{
	mass += 3;
	height += 3;
}

void Human_Black::Breath()
{
	age++;
	Grow();
}

