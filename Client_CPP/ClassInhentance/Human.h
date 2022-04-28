#pragma once
#include <string>
#include "Creature.h"
#include "DynamicArrayTemplate.h"
using namespace std;

class Human :
    public Creature
{
private:
    int clothesNum;

public:
    DynamicArray<string> clothes;

public:
    void WearCloth(string cloth);
    void PrintAllClothes();
};

