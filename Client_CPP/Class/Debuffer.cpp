#include "Debuffer.h"
#include "Warrior.h"
#include <iostream>
using namespace std;
void Debuffer::DecreaseHP(Warrior& target)
{
	cout << "�÷��̾��� ü����" << _damage << "��ŭ �����ž�" << endl;
	target.SetHP(target.GetHP() - _damage);
}

void Debuffer::DecreaseHP()
{
	//Warrior& warrior = *(Warrior::GetInstance());
	//warrior.SetHP(warrior.GetHP() - DAMAGE);
	DecreaseHP(*(Warrior::GetInstance()));
}
