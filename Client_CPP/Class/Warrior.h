#pragma once
#include <iostream>
using namespace std;
class Warrior
{
// 클래스 내의 static 멤버	
// 객체라는건 클래스를 동적할당해서 생성하는건데.
// static 키워드는 동적할당이 불가능하다고 명시하는 키워드
// 그래서 크래스 안의 멤버가 static 이라고 선언되면
// 더이상 객체를 통해 접근 할 수없다.
private:
	static Warrior* _instance;

private:
	int _hp;

#include "Warrior.h"

public:
	Warrior() 
		:_hp(100)
	{		}
	static Warrior* GetInstance();
	void Attack();
	void SetHP(int hp);
	int GetHP();
};

