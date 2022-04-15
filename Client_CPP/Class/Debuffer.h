#pragma warning(disable : 4996)
#pragma once
#include <cstring>
#include "Warrior.h"
// 생성시 플레이어 체력깎는 친구
class Debuffer
{
public:
	int _damage = 10;
	char* _name;
public:
	void DecreaseHP(Warrior& target);
	void DecreaseHP();

	const Debuffer& operator = (Debuffer& _other){
		this->_damage = _other._damage;
		this->_name = _other._name;
		return *this;
	}

	Debuffer() {
		_name = new char[20];
	}

	Debuffer(const Debuffer& origin) {
		_damage = origin._damage;
		_name = new char[strlen(origin._name) + 1];
		strcpy(_name, origin._name);
	}

	~Debuffer() {
		delete[] _name;
	}
};

