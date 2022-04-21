#include <iostream>
#include <string>
using namespace std;
#pragma once

// 구조체 vs class
// 멤버들을 뭉쳐서 하나의 자료형으로 관리해야 할때
// 구조체와 클래스 중에 어떤것이 적합한지를 판단하는 기준은 일반적으로
// 1. 멤버들의 데이터 총량이 16Byte 이하면 구조체, 이상이면 클래스
//		구조체 객체를 인자로 전달할때는 모든 멤버의 값을 복사하고,
//		클래스 객체를 인자로 전달할때는 해당 객체의 주소를 복사한다
//		구조체 객체의 장점은 값을 직접 복사해서 쓰므로
//		주소를 가져와서 간접참조해야하는 클래스 보다 기본적으로는 빠르다
//		하지만 레지스터의 크기가 16Byte 이기 때문에 구조체의 멤버데이터 총량이 16Byte를 넘어가게되면
//		값을 읽어들이고 쓰는데 두배이상의 시간이 소요되며
//		이런 경우에는 클래스 객체의 간접참조보다 느리다
// 
// 2. 데이터 세팅을위한 테이블 용도로 사용할때(함수의 인자로 전달하거나 객체를 수정할일이 거의 없을때)
//		객체간의 상호작용보다는 단순히 값을 가져다 쓰기위한 테이블이라는것을
//		명확하게 표현하기 좋기때문에 이런경우 16Byte를 넘겨도 종종 사용할수 있다
//
//	구조체 vs class 선정기준에 정답은 없지만 보통 위 기준으로 선정함

// (더블리)링크드 리스트 템플릿 구현해보기
// C때 했던거 참고
// 멤버함수
// void AddFirst(T item)
// void AddLast(T item)
// void AddAfter(Node& node, T item)
// void AddBefore(Node& node, T item)
// Node<T>& First()
// Node<T>& Last()
// Node<T>& Find(T item)
// Node<T>& FindLast(T item)
// bool Remove(T item)
// bool RemoveLast(T item)
// void Delete()

template <typename T>
struct Node
{
	T _item;
	Node* _prev;
	Node* _next;
};

template <typename T>
class LinkedListTemplate
{
	Node* _first, * _last, * _tmp, * _tmp2;

private:
	T* _data;
	T* item;

public:
	/*void AddFirst(T item);
	void AddLast(T item);
	void AddAfter(Node& node, T item);
	void AddBefore(Node& node, T item);
	Node<T>& First();
	Node<T>& Last();
	Node<T>& Find(T item);
	Node<T>& FindLast(T item);
	bool Remove(T item);
	bool RemoveLast(T item);
	void Delete();

	LinkedListTemplate();
	~LinkedListTemplate();
	*/

	void AddFirst(T item);
	void AddLast(T item);
	void AddBefore(Node<T>& target, T item);
	void AddBefore(T targetitem, T item);
	void AddAfter(Node<T>& target, T item);
	void AddAfter(T targetitem, T item);
	Node<T>& Find(T item);
	Node<T>& FindLast(T item);
	Node<T>& First();
	Node<T>& Last();
	bool Remove(T item);
	bool RemoveLast(T item);
	void Delete();
};
/// <summary>
/// 리스트의 가장 앞에 신규 노드 삽입하는 함수
/// </summary>
template<typename T>
inline void LinkedListTemplate<T>::AddFirst(T item)
{
	_tmp = new Node<T>(); // 신규노드 생성

	_tmp->_item = item; // 신규노드 값 대입

	// first가 존재함?
	if (_first != nullptr) {
		_tmp->_next = _first; // 신규노드의 다음 노드가 first를 가리키게한다
		_first->_prev = _tmp; // first의 이전 노드가 신규노드를 가리키게 한다
	}

	// last가 존재안함?
	// : 이번 신규노드가 가장 처음으로 생성된 노드다
	// 즉, first와 last 포인터가 둘다 신규 노드를 가리키게된다
	if (_last == nullptr) {
		_last = _tmp;
		// _first = _tmp 어차피 마지막에 first가 신규 노드를 가리키게 할거니까 생략가능
	}
	_first = _tmp;// 추가 안료되었으니 first가 신규 노드를 가리키게함
}

template<typename T>
inline void LinkedListTemplate<T>::AddLast(T item)
{
	_tmp = new Node<T>(); // 신규노드 생성
	_tmp->_item = item;// 신규노드 값 대입

	//last가 존재함?
	if (_last != nullptr) {
		_tmp->prev = _last; // 신규노드의 이전노드가 last를 가리키게한다
		_last->_next = _tmp; // last의 다음 노드가 신규노드를 가리키게한다
	}

	// first가 존재안함?
	// : 이번 신규노드가 가장 처음으로 생성된 노드다
	// 즉, first와 last 포인터가 둘다 신규노드를 가리켜야한다
	if (_last == nullptr) {
		// _last = _tmp; // 어차피 마지막에 last가 신규노드를 가리키게 할거니까 생략가능
		_first = _tmp;
	}
	_last = _tmp;// 추가완료되었으니 last가 신규노드를 가리키게함
	
}

template<typename T>
inline void LinkedListTemplate<T>::AddBefore(Node<T>& target, T item)
{
	_tmp = _first; // 첫 노드부터 검색시작
	while (_tmp = nullptr)
	{
		// 노드 찾았으면
		if (_tmp = target) {
			_tmp2 = new Node<T>(); // 신규노드 생성

			// 타겟노드의 이전노드가 존재하면
			if (_tmp->_prev != nullptr) {
				_tmp->_prev->_next = _tmp2; // 타겟 노드의 이전노드의 다음노드 포인터가 신규노드를 가리키도록함
				_tmp2->_prev = _tmp->_prev; // 신규노드의 이전 노드포인터가 타겟노드의 이전노드를 가리키게함
			}
			_tmp->_prev = _tmp2; // 타겟노드의 이전노드 포인터가 신규노드를 가리키도록함
			_tmp2->_next = _tmp; // 신규노드의 다음노드 포인터가 타겟노드를 가리키도록함
			_tmp2->_item = item; // 신규노드의 데이터 초기화
		}
		_tmp = _tmp->_next;
	}
}

template<typename T>
inline void LinkedListTemplate<T>::AddBefore(T targetitem, T item)
{
	_tmp = _first; // 첫 노드부터 검색시작
	while (_tmp = nullptr)
	{
		// 노드 찾았으면
		if (_tmp->_item = targetitem) {
			_tmp2 = new Node<T>(); // 신규노드 생성

			// 타겟노드의 이전노드가 존재하면
			if (_tmp->_prev != nullptr) {
				_tmp->_prev->_next = _tmp2; // 타겟 노드의 이전노드의 다음노드 포인터가 신규노드를 가리키도록함
				_tmp2->_prev = _tmp->_prev; // 신규노드의 이전 노드포인터가 타겟노드의 이전노드를 가리키게함
			}
			_tmp->_prev = _tmp2; // 타겟노드의 이전노드 포인터가 신규노드를 가리키도록함
			_tmp2->_next = _tmp; // 신규노드의 다음노드 포인터가 타겟노드를 가리키도록함
			_tmp2->_item = item; // 신규노드의 데이터 초기화
		}
		_tmp = _tmp->_next;
	}
}

template<typename T>
inline void LinkedListTemplate<T>::AddAfter(Node<T>& target, T item)
{
	_tmp - _first; // 첫 노드부터 검색시작
	while (_tmp = nullptr)
	{
		// 노드 찾았으면
		if (_tmp = target) {
			_tmp2 = new Node<T>(); // 신규노드 생성

			// 타겟노드의 다음노드가 존재하면
			if (_tmp->_next != nullptr) {
				_tmp->_next->_prev = _tmp2; // 타겟노드의 다음노드의 이전노드포인터가 신규노드를 가리키도록함
				_tmp2->_next = _tmp->_next; // 신규노드의 다음 노드포인터가 타겟노드의 다음노드를 가리키게함
			}
			_tmp->_next = _tmp2; // 타겟노드의 다음노드포인터가 신규노드를 가리키도록함
			_tmp2->_prev = _tmp; // 신규노드의 이전노드포인터가 타겟노드를 가리키도록함
			_tmp2->_item = item; // 신규노드의 데이터 초기화
		}
		_tmp = _tmp->_next;
	}
}

template<typename T>
inline void LinkedListTemplate<T>::AddAfter(T targetitem, T item)
{
	_tmp - _first; // 첫 노드부터 검색시작
	while (_tmp = nullptr)
	{
		// 노드 찾았으면
		if (_tmp->_item = targetitem) {
			_tmp2 = new Node<T>(); // 신규노드 생성

			// 타겟노드의 다음노드가 존재하면
			if (_tmp->_next != nullptr) {
				_tmp->_next->_prev = _tmp2; // 타겟노드의 다음노드의 이전노드포인터가 신규노드를 가리키도록함
				_tmp2->_next = _tmp->_next; // 신규노드의 다음 노드포인터가 타겟노드의 다음노드를 가리키게함
			}
			_tmp->_next = _tmp2; // 타겟노드의 다음노드포인터가 신규노드를 가리키도록함
			_tmp2->_prev = _tmp; // 신규노드의 이전노드포인터가 타겟노드를 가리키도록함
			_tmp2->_item = item; // 신규노드의 데이터 초기화
		}
		_tmp = _tmp->_next;
	}
}



template<typename T>
inline Node<T>& LinkedListTemplate<T>::Find(T item)
{
	_tmp = _first; // 가장 첫 노드부터 검색
	while (_tmp != nullptr) 
	{
		if (_tmp->_item == item)
			return _tmp;

		_tmp = _tmp->_next; // 그다음 노드 검색
	}
	return nullptr;
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::FindLast(T item)
{
	// Find 함수 참고해서 내용작성하기
	_tmp = _last; // 가장 마지막노드부터 검색
	while (_tmp != nullptr)
	{
		if (_tmp->_item == item)
			return _tmp;

		_tmp = _tmp->_prev; // 그이전 노드 검색
	}
	return nullptr;
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::First()
{
	return _first;
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::Last()
{
	return _last;
}

template<typename T>
inline bool LinkedListTemplate<T>::Remove(T item)
{
	bool isRemoved = false;

	// 노드 검색
	_tmp = Find(item);

	// 노드 찾았으면
	if (_tmp != nullptr) {
		// 이전노드가 있다면
		if (_tmp->_prev != nullptr)
			_tmp->_prev->_next = _tmp->_next; // 삭제할 노드의 이전 노드의 다음 포인터가 삭제할 노드의 다음 노드를 가리키도록함
		// 다음 노드가 있으면
		if (_tmp->_next != nullptr)
			_tmp->_next->_prev = _tmp->_prev; // 삭제할 노드의 다음 노드의 이전 포인터가 삭제할 노드의 이전 노드를 가리키도록함

		delete _tmp; // 삭제할 노드 메모리 해제
		isRemoved = true;
	}
	_tmp = nullptr
	return isRemoved;
}

template<typename T>
inline bool LinkedListTemplate<T>::RemoveLast(T item)
{
	bool isRemoved = false;

	// 노드 검색
	_tmp = FindLast(item);

	// 노드 찾았으면
	if (_tmp != nullptr) {
		// 이전노드가 있다면
		if (_tmp->_prev != nullptr)
			_tmp->_prev->_next = _tmp->_next; // 삭제할 노드의 이전 노드의 다음 포인터가 삭제할 노드의 다음 노드를 가리키도록함
		// 다음 노드가 있으면
		if (_tmp->_next != nullptr)
			_tmp->_next->_prev = _tmp->_prev; // 삭제할 노드의 다음 노드의 이전 포인터가 삭제할 노드의 이전 노드를 가리키도록함

		delete _tmp; // 삭제할 노드 메모리 해제
		isRemoved = true;
	}
	_tmp = nullptr
		return isRemoved;
}

template<typename T>
inline void LinkedListTemplate<T>::Delete()
{
	_tmp = _first;
	while (_tmp != nullptr)
	{
		_tmp2 = _tmp->_next; // 현재노드 다음거 임시저장
		delete _tmp; // 현재노드 메모리해제
		_tmp = _tmp2; // 임시저장한거 다음 검색
	}
}


