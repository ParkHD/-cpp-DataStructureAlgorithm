//#pragma once
//struct Node
//{
//	Node* parent = nullptr;
//	Node* left = nullptr;
//	Node* right = nullptr;
//	int key = {};
//};
//class BinarySearchTree
//{
//public:
//
//	void SetCursorPosition(int x, int y);
//
//	void Print() { Print(_root, 10, 0); }
//	void Print(int x, int y) { Print(_root, x, y); }
//	void Print(Node* node, int x, int y);
//	void Print_Inorder() { Print_Inorder(_root); }
//	void Print_Inorder(Node* node);
//
//	Node* Search(Node* node, int key);
//	Node* Search2(Node* node, int key);
//
//	Node* Min() { return Min(_root); }
//	Node* Min(Node* node);
//	Node* Max(Node* node);
//	// node의 다음 값을 찾는 함수
//	Node* Next(Node* node);
//
//	void Insert(int key);
//	void Delete(int key);
//	void Delete(Node* node);
//
//	void Replace(Node* u, Node* v);
//private:
//	Node* _root = nullptr;
//};
//
//// 균형이 안맞을수 있음 그러면 데이터 탐색이 늦어진다