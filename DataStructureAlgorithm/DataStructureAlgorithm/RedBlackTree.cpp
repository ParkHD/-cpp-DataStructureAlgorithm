#include "RedBlackTree.h"
#include <iostream>
#include <Windows.h>

using namespace std;

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}
void SetCursorPosition(int x, int y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}
RedBlackTree::RedBlackTree()
{
	_nil = new Node();
	_root = _nil;
}

RedBlackTree::~RedBlackTree()
{
	delete _nil;
}
void RedBlackTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
		return;

	SetCursorPosition(x, y);

	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

void RedBlackTree::Print_Inorder(Node* node)
{
	// ���� ��ȸ(preorder traverse) [��][��][��]
	// ���� ��ȸ(inorder )			[��][��][��]
	// ���� ��ȸ(postorder )		[��][��][��]
	if (node == _nil)
		return;

	cout << node->key << endl; // ��ġ�� ���� � ��ȸ���� ������(�� : ����, ��� : ����, �� : ����)
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

Node* RedBlackTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key)
		return node;
	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}



Node* RedBlackTree::Min(Node* node)
{
	while (node->left != _nil)
	{
		node = node->left;
	}
	return node;
}

Node* RedBlackTree::Max(Node* node)
{
	while (node->right != _nil)
	{
		node = node->right;
	}
	return node;
}

Node* RedBlackTree::Next(Node* node)
{
	if (node->right != _nil)
		return Min(node->right);

	// �θ� ��尡 ���ų� ���(node)�� �θ���(parent)�� �����ڽĳ��(parent->left)�϶����� ã�´�
	Node* parent = node->parent;
	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void RedBlackTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	Node* node = _root;
	Node* parent = _nil;

	while (node != _nil)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;

	// �����Ͱ� ���� ��
	if (parent == _nil)
		_root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	// �˻�
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);
}

void RedBlackTree::InsertFixup(Node* node)
{
	// 1) p = red, uncle = red
	// 	   -> p = black, u = black, pp = red �� �ٲ�
	// 2) p = red, uncle = black (triangle)
	// 	   -> ȸ���� ���� case3�� �ٲ�
	// 3) p = red, uncle = black (list)
	// 	   -> ���躯�� + ȸ��
	// p = black �̸� �� �ʿ���� �׳� ����

	//		[pp(B)]
	// [p(R)]		[u]
	//	   [n(R)]
	while (node->parent->color == Color::Red) // �����ϴ� ���� Red�̱� ������ ���尡 2���� ������ �ʰ� �ϱ�����
	{
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				node->parent->parent->color = Color::Red; // ���⼭ �ݺ��� �Ͼ�� �κθ�� �κκθ���� ���� �� �ִ�.
				node = node->parent->parent;			
			}
			else
			{
				// triangle        			  list
				//		[pp(B)]        ->    		[pp(B)]
				// [p(R)]		[u]			    [p(R)]		[u]
				//	   [n(R)]				 [n(R)]	   


				if (node == node->parent->right) // triangle �̶��
				{
					node = node->parent;
					LeftRotate(node);
				}
				// ������
				//		[pp(B)]           		 [pp(R)]
				//   [p(R)]		[u]   ->     [p(B)]	   [u(B)]
				//[n(R)]	 			  [n(R)]	
				// ȸ��
				//		[p(B)]
				//   [n(R)]	 [pp(R)]
				//				  [u]
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}
		else
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				node->parent->parent->color = Color::Red;
				node = node->parent->parent;
			}
			else
			{
				// triangle�̸� list�� �ٲ�
				// 
				// triangle                    list      
				//		[pp(B)]			      		 [pp(B)]
				//  [u(B)]    [p(R)]   ->        [u(B)]   [p(R)]
				//		    [n(R)]		                       [n(R)]	
											  
				if (node == node->parent->left)
				{
					node = node->parent;
					RightRotate(node);
				}
				// list Ÿ�� �̸�
				// list   
				//		 [pp(B)]
				//   [u(B)]   [p(R)]
				//                 [n(R)]	 
				// 

				//		  [p(B)]
				//   [pp(R)]    [n(R)]
				//	[u(B)]			  
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}
	_root->color = Color::Black;
}

// left
//		[x]         	    [y]    
//   [1]   [y]	   ->    [x]   [3] 
//       [2] [3]      [1] [2]	   
void RedBlackTree::LeftRotate(Node* x)
{
	Node* y = x->right;

	// x - [2] ����
	x->right = y->left;	
	// [2]�� nil �ϼ� �ִ�
	if (y->left != _nil)
		y->left->parent = x;

	// x y ��ü
	y->parent = x->parent;
	if (x->parent == _nil)	// root���� �˻�
		_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

// right
//		[y]    		   [x]
//   [x]   [3]  ->  [1]   [y]
// [1] [2]	            [2]  [3]
void RedBlackTree::RightRotate(Node* y)
{
	Node* x = y->left;
	y->left = x->right;	// [1] 
	// [2]�� nil �ϼ� �ִ�
	if (y->right != _nil)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == _nil)	// root���� �˻�
		_root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}

void RedBlackTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void RedBlackTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	// �����Ϸ��� ����� �ڽ��� �ϳ��� �������
	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	// �ڽ��� �ΰ� �ִ� ���
	else
	{
		// �������� ū �����͸� ã�� �����Ͱ��� �ű�� ���
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void RedBlackTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v)
		v->parent = u->parent;

	delete u;
}


