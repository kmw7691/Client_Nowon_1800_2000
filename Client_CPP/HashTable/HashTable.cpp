#include "HashTable.h"

HashTable::HashTable()
    :DEFAULT_SIZE(100)
{
    int arr[100];
    int* a = arr;
    _bucket = new LinkedList<string>*[DEFAULT_SIZE];
    for (int i = 0; i < DEFAULT_SIZE; i++)
        _bucket[i] = nullptr;
    
    _tmpHash = 0;
}

void HashTable::Add(string value)
{
    _tmpHash = Hash(value); // �߰��Ϸ��� value�� �ؽ� ���ϱ�

    // bucket����  �ش� �ؽÿ� ����  ��ũ�帮��Ʈ�� ������ ����
    if (_bucket[_tmpHash] == nullptr)
        _bucket[_tmpHash] = new LinkedList<string>();

    _bucket[_tmpHash]->AddLast(value); // bucket���� �ش� �ؽÿ� �ش��ϴ� ��ũ�帮��Ʈ�� ���� �߰� 
}

bool HashTable::ContainsKey(int Key)
{
    if ((_bucket[key] == nullptr) || (key >= DEFAULT_SIZE - 1))
        return false;
    else
        return true;
}

bool HashTable::ContainsKey(string value)
{
    return ContainsKey(Hash(value));
}

bool HashTable::ContainsValue(string value)
{
    int key = Hash(value);
    if (_bucket[key] != nullptr) {
        // ��ũ�帮��Ʈ���� ���� �˻��� ������ false, ������ true��ȯ
        return (&_bucket[key]->Find(value) == nullptr) ? false : true;
    }

    return false;
}

bool HashTable::RemoveKey(int Key)
{
    // ���� Ű�� �ش��ϴ� ��ũ�帮��Ʈ�� ������
    if (_bucket[key] != nullptr) {
        _bucket[key]->Delete(); // ��ũ�帮��Ʈ�� ��带 ����
        delete _bucket[key]; // ��ũ�帮��Ʈ ����
        return true;
    }
    return false;
}

bool HashTable::RemoveKey(string value)
{
    return RemoveKey(Hash(value));
}

bool HashTable::RemoveValue(string value)
{
    int key = Hash(value); // ���ڷ� �ؽ� ����
    if (_bucket[key] != nullptr) {

        // ���ڿ� ���� �����͸� ���� ��� ����
        bool isRemoved = _bucket[key]->RemoveLast(value);

        // �����ߴµ� ��ũ�帮��Ʈ�� ��尡 ������ ��ũ�帮��Ʈ ����
        if (isRemoved && _bucket[key]->Count() <= 0)
            delete _bucket[key];

        return isRemoved;
    }
    return false;
}

void HashTable::Clear()
{
    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        if (_bucket[i] != nullptr)
        {
            _bucket[i]->Delete();
            delete _bucket[i];
        }
    }
}

void HashTable::Delete()
{
    Clear();
    delete[] _bucket;
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