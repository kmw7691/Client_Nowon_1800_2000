#include "DynamicArray.h"


int DynamicArray::Length()
{
	return 0;
}

void DynamicArray::Add(int item)
{
	// 배열의 크기가 충분하지 않으면 현재 길이의 두배로 늘린다.
	if (_length>=_capacity){
		_capacity *= 2;
		int* tmp = new int[_capacity];
		for (int i = 0; i < _length; i++)
			tmp[i] = _data[i];
		delete[] _data;               
		_data = new int[_capacity];
		for (int i = 0; i < _length; i++)
			_data[i] = tmp[i];
		delete[] tmp;
	}
	_data[_length] = item;
	_length++;
}

/// <summary>
/// 아이템 검색 성공시 해당 아이템 인 덱스 반환, 실패시 -1 반환
/// </summary>
int DynamicArray::Find(int item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return i;
	}
	return -1;
}

// Camel case : 각단어의 시작 알파벳은 대문자로 표현하는 방법
// 보통 변수이름 시작알파벳은 소문자, 그외 대문자로 표현

int DynamicArray::IsExist(int item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return true;
	}
	return false;
}

/// <summary>
/// 특정 아이템을 지우는 함수
/// 지우는데 성공하면 true, 실패하면 false반환
/// </summary>

bool DynamicArray::Remove(int item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return RemoveAt(i);
	}
	return false;
}

/// <summary>
/// 특정 인덱스를 지우는 함수
/// 지우는데 성공하면 true, 실패하면 false반환
/// </summary
bool DynamicArray::RemoveAt(int index)
{
	if (index < _length) {
		for (int i = index; i < _length - 1; i++)
		{
			_data[i] = _data[i + 1];
		}
		_length--;
		return true;
	}
	
	return false;
}

void DynamicArray::Delete()
{
}

DynamicArray::DynamicArray()
	: DEFAULT_SIZE(1)
	// 이니셜라이저, 생성자 함수 내용 실행 전에 멤버 초기화를 할때 사용한다.
{
	_length = 0;
	_capacity = DEFAULT_SIZE	  ;
	_data = new int[_capacity];
}

DynamicArray::~DynamicArray()
{
	delete[] _data;
}
