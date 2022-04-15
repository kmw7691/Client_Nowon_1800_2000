#include "Debuffer.h"
#include "Warrior.h"
#include <iostream>
using namespace std;
void Debuffer::DecreaseHP(Warrior& target)
{
	cout << "플레이어의 체력을" << _damage << "만큼 깎을거야" << endl;
	target.SetHP(target.GetHP() - _damage);
}

void Debuffer::DecreaseHP()
{
	//Warrior& warrior = *(Warrior::GetInstance());
	//warrior.SetHP(warrior.GetHP() - DAMAGE);
	DecreaseHP(*(Warrior::GetInstance()));
}
