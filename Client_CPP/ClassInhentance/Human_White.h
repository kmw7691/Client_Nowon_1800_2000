#pragma once
#include "Human.h"
class Human_White :
    public Human
{
public:
    void GoToTravel();
    // override
    // �θ��� ����Լ��� ������ �� ���ִ� ���
    void Breath();
    void Grow();
};

