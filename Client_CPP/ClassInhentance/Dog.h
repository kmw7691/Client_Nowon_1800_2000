#pragma once
#include "Creature.h"

// 클래스 상속
// class 클래스이름 : 상속받을 클래스 이름 (부모클래스)


class Dog :
    public Creature
{
public:
    int tailLength;

public:
    void Bite(Creature* creature);
};

