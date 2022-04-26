#pragma once
#include "LinkedListTemplate.h"
#include <string>
using namespace std;

class HashTable
{
private:
	const int DEFAULT_SIZE = 100;
	LinkedList<string>** _bucket;
	int _tmpHash;
	int key;

public:
	HashTable();
	void Add(string value); // 인자 value의 해시키를 구해서 해당 bucket에 value를 추가하는 함수
	bool ContainsKey(int Key); // 해시키가 존재하는지 체크하는 함수
	bool ContainsKey(string value); // value에 해당하는 해시키가 존재하는지 체크하는 함수
	bool ContainsValue(string value); // 인자 value가 존재하는지 체크하는 함수
	bool RemoveKey(int Key); // 인자 key에 해당하는 bucket을 메모리해제 하는 함수
	bool RemoveKey(string value); // 인자 value에 해당하는 key에 해당하는 bucket을 메모리해제하는 함수
	bool RemoveValue(string value);  // 인자 value를 지우는 함수
	void Clear(); // 모든 bucket 메모리해제
	void Delete(); // hashtable 메모리해제

private:
	int Hash(string value); // 해시를 구하는 함수
};

