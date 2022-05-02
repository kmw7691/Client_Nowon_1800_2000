#pragma once
#include "Creature.h"

// 클래스 상속
// class 클래스이름 : 상속받을 클래스 이름 (부모클래스)


class Dog :
    public Creature
{
private:
    bool followEnable;

    // friend : friend class 클래스명
    // 이라고 선언된 클래스타입의 객체들은 접근제한자에 상관없이 멤버에 접근 가능하도록 해준다.
    // 코드 꼬이니까 웬만하면 사용x


    friend class Human;

public:
    int tailLength;

public:
    void Bite(Creature* creature);
};

