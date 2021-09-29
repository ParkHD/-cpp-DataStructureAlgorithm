#pragma once

enum class Color
{
	Red = 0,
	Black = 1,
};
struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
	Color color = Color::Black;
};

// Red-Black Tree
// 1) ��� ���� Red or Black
// 2) Root�� Black
// 3) Leat(NIL)�� Black
// 4) Red ����� �ڽ��� Black(�����ؼ� Red-Red X)
// 5) �� ���κ��� �������� ���� ��ε��� ��� ���� ���� Black
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	

	void Print() { Print(_root, 10, 0); }
	void Print(int x, int y) { Print(_root, x, y); }
	void Print(Node* node, int x, int y);
	void Print_Inorder() { Print_Inorder(_root); }
	void Print_Inorder(Node* node);

	Node* Search(Node* node, int key);


	Node* Min() { return Min(_root); }
	Node* Min(Node* node);
	Node* Max(Node* node);
	// node�� ���� ���� ã�� �Լ�
	Node* Next(Node* node);

	void Insert(int key);
	void InsertFixup(Node* node);

	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u, Node* v);

	void LeftRotate(Node* node);
	void RightRotate(Node* node);
private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};

// ������ �ȸ����� ���� �׷��� ������ Ž���� �ʾ�����