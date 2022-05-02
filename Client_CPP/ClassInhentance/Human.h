#pragma once
#include <string>
#include "Creature.h"
#include "DynamicArrayTemplate.h"
#include "ITwoLeggedWalker.h"
#include "Dog.h"
using namespace std;

class Human :
    public Creature, public ITwoLeggedWalker
{
private:
    friend class Dog;

private:
    int clothesNum;

public:
    DynamicArray<string> clothes;

public:
    void WearCloth(string cloth);
    void PrintAllClothes();
    void ITwoLeggedWalk();
    void FourLeggedWalk();
    void MakeDogFollowMe(Dog& dog);
};

