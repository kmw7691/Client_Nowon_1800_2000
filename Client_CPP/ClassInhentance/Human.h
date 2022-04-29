#pragma once
#include <string>
#include "Creature.h"
#include "DynamicArrayTemplate.h"
#include "ITwoLeggedWalker.h"
using namespace std;

class Human :
    public Creature, public ITwoLeggedWalker
{
private:
    int clothesNum;

public:
    DynamicArray<string> clothes;

public:
    void WearCloth(string cloth);
    void PrintAllClothes();
    void ITwoLeggedWalk();
};

