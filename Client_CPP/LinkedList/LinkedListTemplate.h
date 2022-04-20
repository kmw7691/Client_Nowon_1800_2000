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
	Node* _first, * _last, * _tmp, * tmp2;

private:
	T* _data;
	T* item;

public:
	void AddFirst(T item);
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
inline void LinkedListTemplate<T>::AddAfter(Node& node, T item)
{
}

template<typename T>
inline void LinkedListTemplate<T>::AddBefore(Node& node, T item)
{
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::First()
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::Last()
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::Find(T item)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

template<typename T>
inline Node<T>& LinkedListTemplate<T>::FindLast(T item)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

template<typename T>
inline bool LinkedListTemplate<T>::Remove(T item)
{
	return false;
}

template<typename T>
inline bool LinkedListTemplate<T>::RemoveLast(T item)
{
	return false;
}

template<typename T>
inline void LinkedListTemplate<T>::Delete()
{
}

template<typename T>
inline LinkedListTemplate<T>::LinkedListTemplate()
{
	_head = new Node<T>;
	_last = new Node<T>;
	_head->_next = _last;

}

template<typename T>
inline LinkedListTemplate<T>::~LinkedListTemplate()
{
}
