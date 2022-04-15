#include "Warrior.h"

Warrior * Warrior::_instance = NULL;

Warrior* Warrior::GetInstance()
{
	if (_instance == nullptr)
		_instance = new Warrior();
	return _instance;
}

void Warrior::Attack()
{
	cout << "공격!" << endl;
}

void Warrior::SetHP(int hp)
{
	_hp = hp;
	cout << "내 체력은 현재" << _hp << "야" << endl;
}

int Warrior::GetHP()
{
	return _hp;
}
