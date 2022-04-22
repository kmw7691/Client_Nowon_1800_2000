#include "BinaryTree.h"

Node& BinaryTree::Find(int item)
{
	if (_root == nullptr) return;

	_tmp = _root;

	while (_tmp != nullptr)
	{
		// 찾고자하는 값이 현재 노드보다 작을때
		if (_tmp->_data > item)
			_tmp = _tmp->_left;
		// 찾고자하는 값이 현재 노드보다 클때
		else if (_tmp->_data < item)
			_tmp = _tmp->_right;
		// 찾고자하는 값이 현재 노드와 같을때
		else
			return  *_tmp;
	}
	return *_tmp;
}

void BinaryTree::Insert(int item)
{
	if (_root != nullptr) {
		_tmp = _root;
		while (_tmp != nullptr)
		{
			// 삽입하고자 하는 값이 현재 노드보다 작을때
			if (_tmp->_data > item) {
				// 현재 노드에 왼쪽 자식이 있으면
				if (_tmp->_left != nullptr)
					_tmp = _tmp->_left;
				// 현재 노드에 왼쪽 자식이 없으면
				else {
					_tmp->_left = new Node();
					_tmp->_left->_data = item;
					return;
				}
			}
			else if (_tmp->_data < item) {

				// 현재 노드에 오른쪽 자식이 있으면
				if (_tmp->_right != nullptr)
					_tmp = _tmp->_right;
				// 현재 노드에 오른쪽 자식이 없으면
				else {
					_tmp->_right = new Node();
					_tmp->_right->_data = item;
					return;
				}
			}
			// 삽입하고자 하는 값이 현재노드와 같을때
			else
				throw "해당 노드가 이미 존재함";
		}
	}
	else {
		_root = new Node();
		_root->_data = item;
	}
}

bool BinaryTree::Remove(int item)
{
	bool doRemove = false;
	int dir = 0; // 0이면 왼쪽 진행, 1이면 오른쪽 진행

	if (_root == nullptr) 
		return doRemove;

	_tmp = _root;
	 
	while (_tmp != nullptr)
	{
		// 삭제하려는 값이 현재노드 값보다 작을 경우
		if (_tmp->_data > item) {
			dir = 0;
			_tmp2 = _tmp; // 부모노드 포인터 저장
			_tmp = _tmp->_left; // 포인터 왼쪽 자식으로 옮김
		}
		// 삭제하려는 값이 현재노드 값보다 클 경우
		else if (_tmp->_data < item) {
			dir = 1;
			_tmp2 = _tmp; // 부모노드 포인터 저장
			_tmp = _tmp->_right; // 포인터 오른쪽 자식으로 옮김
		}
		// 삭제하려는 값이 현재노드 값과 같을 경우
		else {
			doRemove = true;
			break;
		}
	}

	if (doRemove) {
		 
		// 논리연산
		// == 을 했을때 좌항과 우항이 같으면 true, 다르면 false가 반환됨

		// 조건부 논리연산자 (&&, ||)
		// 좌항의 결과에 따라 논리연산의 결과가 결정되었을 경우 우항 비교연산을 하지않고 좌항 결과를 반환함

		// 삭제하고자 하는 노드에 자식이 없을경우
		if (_tmp->_left == nullptr && _tmp->_right == nullptr) {
			// 삭제하고자 하는 노드와 그 부모노드 간의 연결을 끊음
			if (_tmp2 != nullptr) {
				if (dir == 0)
					_tmp2->_left = nullptr;
				else
					_tmp2->_right = nullptr;
			}
			// 노드삭제
			delete _tmp;
			_tmp = nullptr;
		}
		// 삭제하고자 하는 노드에 왼쪽 자식만 있을 경우
		else if (_tmp->_left == nullptr && _tmp->_right == nullptr) {
			// 삭제하고자하는 노드의 자식노드와 삭제하고자하는 노드의 부모노드를 연결
			if (_tmp2 != nullptr) {
				if (dir == 0)
					_tmp2->_left = _tmp->_right;
				else
					_tmp2->_right = _tmp->_right;
			}
			// 노드 삭제
			delete _tmp;
			_tmp = nullptr;
		}
		// 삭제하고자 하는 노드에 왼쪽 오른쪽 자식이 둘다 있을경우
		else {

			// 단말노드 검색(삭제한 노드를 대체할 노드 검색)
			Node* leaf = FindLeaf(_tmp);
		}
	}

	return doRemove;
}

Node* BinaryTree::FindLeaf(Node* start)
{
	Node* leaf = start;

	if (leaf->_right != nullptr) {
		leaf = leaf->_right;
		while (leaf->_left != nullptr)
		{
			leaf = leaf->_left;
		}
		leaf =  FindLeaf(leaf);
	}
	return leaf;
}
