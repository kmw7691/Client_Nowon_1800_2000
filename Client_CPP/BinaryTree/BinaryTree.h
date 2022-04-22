#pragma once

// ���� Ʈ��
// ��� : �⺻����
// ��Ʈ���(�Ѹ����) : �ֻ��� �θ� ���
// �������(�ܸ����) : ������ �ڽ� ���
// ũ�� : ��尹��
// ����(����) : ���ǰ���
// ���� : �������� = ũ�� - 1

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

