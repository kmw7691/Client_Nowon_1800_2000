#include <iostream>
#include "Human.h"

void Human::WearCloth(string cloth)
{
	clothes.Add(cloth);
}

void Human::PrintAllClothes()
{
	cout << "���� �԰��ִ� �ʵ��̾� : ";
	for (int i = 0; i < clothes.Length(); i++)
	{
		cout << clothes[i] << endl;
	}
	cout << endl;
}

void Human::ITwoLeggedWalk()
{
	std::cout << "���������� �ǽ��մϴ�" << std::endl;
}

void Human::FourLeggedWalk()
{
}

void Human::MakeDogFollowMe(Dog& dog)
{
	dog.followEnable = true;
}
