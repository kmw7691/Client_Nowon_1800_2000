#include <iostream>
#include "Human.h"

void Human::WearCloth(string cloth)
{
	clothes.Add(cloth);
}

void Human::PrintAllClothes()
{
	cout << "내가 입고있는 옷들이야 : ";
	for (int i = 0; i < clothes.Length(); i++)
	{
		cout << clothes[i] << endl;
	}
	cout << endl;
}

void Human::ITwoLeggedWalk()
{
	std::cout << "이족보행을 실시합니다" << std::endl;
}

void Human::FourLeggedWalk()
{
}

void Human::MakeDogFollowMe(Dog& dog)
{
	dog.followEnable = true;
}
