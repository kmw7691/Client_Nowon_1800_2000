#include <iostream>
#include <string>
using namespace std;
#pragma once

// ����ü vs class
// ������� ���ļ� �ϳ��� �ڷ������� �����ؾ� �Ҷ�
// ����ü�� Ŭ���� �߿� ����� ���������� �Ǵ��ϴ� ������ �Ϲ�������
// 1. ������� ������ �ѷ��� 16Byte ���ϸ� ����ü, �̻��̸� Ŭ����
//		����ü ��ü�� ���ڷ� �����Ҷ��� ��� ����� ���� �����ϰ�,
//		Ŭ���� ��ü�� ���ڷ� �����Ҷ��� �ش� ��ü�� �ּҸ� �����Ѵ�
//		����ü ��ü�� ������ ���� ���� �����ؼ� ���Ƿ�
//		�ּҸ� �����ͼ� ���������ؾ��ϴ� Ŭ���� ���� �⺻�����δ� ������
//		������ ���������� ũ�Ⱑ 16Byte �̱� ������ ����ü�� ��������� �ѷ��� 16Byte�� �Ѿ�ԵǸ�
//		���� �о���̰� ���µ� �ι��̻��� �ð��� �ҿ�Ǹ�
//		�̷� ��쿡�� Ŭ���� ��ü�� ������������ ������
// 
// 2. ������ ���������� ���̺� �뵵�� ����Ҷ�(�Լ��� ���ڷ� �����ϰų� ��ü�� ���������� ���� ������)
//		��ü���� ��ȣ�ۿ뺸�ٴ� �ܼ��� ���� ������ �������� ���̺��̶�°���
//		��Ȯ�ϰ� ǥ���ϱ� ���⶧���� �̷���� 16Byte�� �Ѱܵ� ���� ����Ҽ� �ִ�
//
//	����ü vs class �������ؿ� ������ ������ ���� �� �������� ������

// (����)��ũ�� ����Ʈ ���ø� �����غ���
// C�� �ߴ��� ����
// ����Լ�
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
/// ����Ʈ�� ���� �տ� �ű� ��� �����ϴ� �Լ�
/// </summary>
template<typename T>
inline void LinkedListTemplate<T>::AddFirst(T item)
{
	_tmp = new Node<T>(); // �űԳ�� ����

	_tmp->_item = item; // �űԳ�� �� ����

	// first�� ������?
	if (_first != nullptr) {
		_tmp->_next = _first; // �űԳ���� ���� ��尡 first�� ����Ű���Ѵ�
		_first->_prev = _tmp; // first�� ���� ��尡 �űԳ�带 ����Ű�� �Ѵ�
	}

	// last�� �������?
	// : �̹� �űԳ�尡 ���� ó������ ������ ����
	// ��, first�� last �����Ͱ� �Ѵ� �ű� ��带 ����Ű�Եȴ�
	if (_last == nullptr) {
		_last = _tmp;
		// _first = _tmp ������ �������� first�� �ű� ��带 ����Ű�� �ҰŴϱ� ��������
	}
	_first = _tmp;// �߰� �ȷ�Ǿ����� first�� �ű� ��带 ����Ű����
}

template<typename T>
inline void LinkedListTemplate<T>::AddLast(T item)
{
	_tmp = new Node<T>(); // �űԳ�� ����
	_tmp->_item = item;// �űԳ�� �� ����

	//last�� ������?
	if (_last != nullptr) {
		_tmp->prev = _last; // �űԳ���� ������尡 last�� ����Ű���Ѵ�
		_last->_next = _tmp; // last�� ���� ��尡 �űԳ�带 ����Ű���Ѵ�
	}

	// first�� �������?
	// : �̹� �űԳ�尡 ���� ó������ ������ ����
	// ��, first�� last �����Ͱ� �Ѵ� �űԳ�带 �����Ѿ��Ѵ�
	if (_last == nullptr) {
		// _last = _tmp; // ������ �������� last�� �űԳ�带 ����Ű�� �ҰŴϱ� ��������
		_first = _tmp;
	}
	_last = _tmp;// �߰��Ϸ�Ǿ����� last�� �űԳ�带 ����Ű����
	
}

template<typename T>
inline void LinkedListTemplate<T>::AddBefore(Node<T>& target, T item)
{
	_tmp = _first; // ù ������ �˻�����
	while (_tmp = nullptr)
	{
		// ��� ã������
		if (_tmp = target) {
			_tmp2 = new Node<T>(); // �űԳ�� ����

			// Ÿ�ٳ���� ������尡 �����ϸ�
			if (_tmp->_prev != nullptr) {
				_tmp->_prev->_next = _tmp2; // Ÿ�� ����� ��������� ������� �����Ͱ� �űԳ�带 ����Ű������
				_tmp2->_prev = _tmp->_prev; // �űԳ���� ���� ��������Ͱ� Ÿ�ٳ���� ������带 ����Ű����
			}
			_tmp->_prev = _tmp2; // Ÿ�ٳ���� ������� �����Ͱ� �űԳ�带 ����Ű������
			_tmp2->_next = _tmp; // �űԳ���� ������� �����Ͱ� Ÿ�ٳ�带 ����Ű������
			_tmp2->_item = item; // �űԳ���� ������ �ʱ�ȭ
		}
		_tmp = _tmp->_next;
	}
}

template<typename T>
inline void LinkedListTemplate<T>::AddBefore(T targetitem, T item)
{
	_tmp = _first; // ù ������ �˻�����
	while (_tmp = nullptr)
	{
		// ��� ã������
		if (_tmp->_item = targetitem) {
			_tmp2 = new Node<T>(); // �űԳ�� ����

			// Ÿ�ٳ���� ������尡 �����ϸ�
			if (_tmp->_prev != nullptr) {
				_tmp->_prev->_next = _tmp2; // Ÿ�� ����� ��������� ������� �����Ͱ� �űԳ�带 ����Ű������
				_tmp2->_prev = _tmp->_prev; // �űԳ���� ���� ��������Ͱ� Ÿ�ٳ���� ������带 ����Ű����
			}
			_tmp->_prev = _tmp2; // Ÿ�ٳ���� ������� �����Ͱ� �űԳ�带 ����Ű������
			_tmp2->_next = _tmp; // �űԳ���� ������� �����Ͱ� Ÿ�ٳ�带 ����Ű������
			_tmp2->_item = item; // �űԳ���� ������ �ʱ�ȭ
		}
		_tmp = _tmp->_next;
	}
}

template<typename T>
inline void LinkedListTemplate<T>::AddAfter(Node<T>& target, T item)
{
	_tmp - _first; // ù ������ �˻�����
	while (_tmp = nullptr)
	{
		// ��� ã������
		if (_tmp = target) {
			_tmp2 = new Node<T>(); // �űԳ�� ����

			// Ÿ�ٳ���� ������尡 �����ϸ�
			if (_tmp->_next != nullptr) {
				_tmp->_next->_prev = _tmp2; // Ÿ�ٳ���� ��������� ������������Ͱ� �űԳ�带 ����Ű������
				_tmp2->_next = _tmp->_next; // �űԳ���� ���� ��������Ͱ� Ÿ�ٳ���� ������带 ����Ű����
			}
			_tmp->_next = _tmp2; // Ÿ�ٳ���� ������������Ͱ� �űԳ�带 ����Ű������
			_tmp2->_prev = _tmp; // �űԳ���� ������������Ͱ� Ÿ�ٳ�带 ����Ű������
			_tmp2->_item = item; // �űԳ���� ������ �ʱ�ȭ
		}
		_tmp = _tmp->_next;
	}
}

template<typename T>
inline void LinkedListTemplate<T>::AddAfter(T targetitem, T item)
{
	_tmp - _first; // ù ������ �˻�����
	while (_tmp = nullptr)
	{
		// ��� ã������
		if (_tmp->_item = targetitem) {
			_tmp2 = new Node<T>(); // �űԳ�� ����

			// Ÿ�ٳ���� ������尡 �����ϸ�
			if (_tmp->_next != nullptr) {
				_tmp->_next->_prev = _tmp2; // Ÿ�ٳ���� ��������� ������������Ͱ� �űԳ�带 ����Ű������
				_tmp2->_next = _tmp->_next; // �űԳ���� ���� ��������Ͱ� Ÿ�ٳ���� ������带 ����Ű����
			}
			_tmp->_next = _tmp2; // Ÿ�ٳ���� ������������Ͱ� �űԳ�带 ����Ű������
			_tmp2->_prev = _tmp; // �űԳ���� ������������Ͱ� Ÿ�ٳ�带 ����Ű������
			_tmp2->_item = item; // �űԳ���� ������ �ʱ�ȭ
		}
		_tmp = _tmp->_next;
	}
}



template<typename T>
inline Node<T>& LinkedListTemplate<T>::Find(T item)
{
	_tmp = _first; // ���� ù ������ �˻�
	while (_tmp != nullptr) 
	{
		if (_tmp->_item == item)
			return _tmp;

		_tmp = _tmp->_next; // �״��� ��� �˻�
	}
	return nullptr;
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::FindLast(T item)
{
	// Find �Լ� �����ؼ� �����ۼ��ϱ�
	_tmp = _last; // ���� ������������ �˻�
	while (_tmp != nullptr)
	{
		if (_tmp->_item == item)
			return _tmp;

		_tmp = _tmp->_prev; // ������ ��� �˻�
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

	// ��� �˻�
	_tmp = Find(item);

	// ��� ã������
	if (_tmp != nullptr) {
		// ������尡 �ִٸ�
		if (_tmp->_prev != nullptr)
			_tmp->_prev->_next = _tmp->_next; // ������ ����� ���� ����� ���� �����Ͱ� ������ ����� ���� ��带 ����Ű������
		// ���� ��尡 ������
		if (_tmp->_next != nullptr)
			_tmp->_next->_prev = _tmp->_prev; // ������ ����� ���� ����� ���� �����Ͱ� ������ ����� ���� ��带 ����Ű������

		delete _tmp; // ������ ��� �޸� ����
		isRemoved = true;
	}
	_tmp = nullptr
	return isRemoved;
}

template<typename T>
inline bool LinkedListTemplate<T>::RemoveLast(T item)
{
	bool isRemoved = false;

	// ��� �˻�
	_tmp = FindLast(item);

	// ��� ã������
	if (_tmp != nullptr) {
		// ������尡 �ִٸ�
		if (_tmp->_prev != nullptr)
			_tmp->_prev->_next = _tmp->_next; // ������ ����� ���� ����� ���� �����Ͱ� ������ ����� ���� ��带 ����Ű������
		// ���� ��尡 ������
		if (_tmp->_next != nullptr)
			_tmp->_next->_prev = _tmp->_prev; // ������ ����� ���� ����� ���� �����Ͱ� ������ ����� ���� ��带 ����Ű������

		delete _tmp; // ������ ��� �޸� ����
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
		_tmp2 = _tmp->_next; // ������ ������ �ӽ�����
		delete _tmp; // ������ �޸�����
		_tmp = _tmp2; // �ӽ������Ѱ� ���� �˻�
	}
}


