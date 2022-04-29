#include "Human_White.h"
#include <iostream>
using namespace std;

void Human_White::GoToTravel()
{
	cout << "백인은 여행을 떠납니다" << endl;
}

void Human_White::Breath()
{
	age++;
	Grow();
}

void Human_White::Grow()
{
	mass += 2;
	height += 2;
}
