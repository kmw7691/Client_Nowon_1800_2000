#include "HashTable.h"

HashTable::HashTable()
    :DEFAULT_SIZE(100)
{
    *_bucket = new LinkedList<string>[DEFAULT_SIZE];
}

void HashTable::Add(string value)
{
    _tmpHash = Hash(value); // 추가하려는 value의 해시 구하기

    // bucket내에  해당 해시에 대한  링크드리스트가 없으면 생성
    if (_bucket[_tmpHash] == nullptr)
        _bucket[_tmpHash] = new LinkedList<string>();

    _bucket[_tmpHash]->AddLast(value); // bucket내의 해당 해시에 해당하는 링크드리스트에 인자 추가 
}

bool HashTable::ContainsKey(int Key)
{
    return false;
}

void HashTable::ContainsKey(string value)
{
}

bool HashTable::ContainsValue(string value)
{
    return false;
}

bool HashTable::RemoveKey(int Key)
{
    return false;
}

bool HashTable::RemoveKey(string value)
{
    return false;
}

bool HashTable::RemoveValue(string value)
{
    return false;
}

bool HashTable::Clear()
{
    return false;
}

bool HashTable::Delete()
{
    return false;
}

int HashTable::Hash(string value)
{
    _tmpHash = 0;
    for (int i = 0; i < value.length(); i++)
    {
        _tmpHash += value[i];
    }
    _tmpHash %= DEFAULT_SIZE;
    return _tmpHash;
}
