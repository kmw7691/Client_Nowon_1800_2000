#pragma once

// 이진 트리
// 노드 : 기본단위
// 루트노드(뿌리노드) : 최상위 부모 노드
// 리프노드(단말노드) : 최하위 자식 노드
// 크기 : 노드갯수
// 깊이(높이) : 층의갯수
// 차수 : 간선갯수 = 크기 - 1

struct Node {
	int _data;
	Node* _left;
	Node* _right;
};

class BinaryTree
{
private:
	Node* _root, * _tmp, * _tmp2;

public:
	Node& Find(int item);
	void Insert(int item);
	bool Remove(int item);

private:
	Node* FindLeaf(Node* start);
};

