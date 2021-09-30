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
// 1) 모든 노드는 Red or Black
// 2) Root는 Black
// 3) Leat(NIL)는 Black
// 4) Red 노드의 자식은 Black(연속해서 Red-Red X)
// 5) 각 노드로부터 리프까지 가는 경로들은 모두 같은 수의 Black
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	

	void Print();
	void Print(int x, int y) { Print(_root, x, y); }
	void Print(Node* node, int x, int y);
	void Print_Inorder() { Print_Inorder(_root); }
	void Print_Inorder(Node* node);

	Node* Search(Node* node, int key);


	Node* Min() { return Min(_root); }
	Node* Min(Node* node);
	Node* Max(Node* node);
	// node의 다음 값을 찾는 함수
	Node* Next(Node* node);

	void Insert(int key);
	void InsertFixup(Node* node);

	void Delete(int key);
	void Delete(Node* node);
	void DeleteFixup(Node* node);

	void Replace(Node* u, Node* v);

	void LeftRotate(Node* node);
	void RightRotate(Node* node);
private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};

// 균형이 안맞을수 있음 그러면 데이터 탐색이 늦어진다