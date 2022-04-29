#pragma once
#include "Human.h"
class Human_White :
    public Human
{
public:
    void GoToTravel();
    // override
    // 부모의 멤버함수를 재정의 할 수있는 기능
    void Breath();
    void Grow();
};

