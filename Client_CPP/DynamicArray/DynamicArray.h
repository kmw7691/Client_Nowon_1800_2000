#pragma once
class DynamicArray
{
private:
	int* _data;
	int _length; 
	int _capacity;
	const int DEFAULT_SIZE;

public:
	int Length();
	void Add(int item);
	int Find(int item); // 아이템 찾으면 해당 아이템의 인덱스를 반환

	// bool 자료형 (논리형) : 보통 true와 false 키워드로 값을 표현함
	// true : 1, false : 0
	// bool 변수에다가 값을 대입할때 만약 0이면 bool변수는 해당 값을 false로 저장    
	// 0이 아니면 true로 저장
	int IsExist(int item); // 아이템 찾으면 1을 반환 아니면             
	bool Remove(int item); // 아이템 삭제 성공시 true반환 아니면 false반환
	bool RemoveAt(int index); // 해당 인덱스 삭제 성공시 true반환 아니면 false반환
	void Delete();

	DynamicArray();
	~DynamicArray();
};

