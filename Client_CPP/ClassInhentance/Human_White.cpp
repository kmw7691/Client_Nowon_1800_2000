#include "Human_White.h"
#include <iostream>
using namespace std;

void Human_White::GoToTravel()
{
	cout << "������ ������ �����ϴ�" << endl;
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
