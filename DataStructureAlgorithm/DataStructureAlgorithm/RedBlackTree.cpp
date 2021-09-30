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
void ShowConsoleCursor(bool flag)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorinfo;
	::GetConsoleCursorInfo(output, &cursorinfo);
	cursorinfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorinfo);
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

void RedBlackTree::Print()
{
	::system("cls");
	ShowConsoleCursor(false);
	Print(_root, 10, 0);
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
	if (node == _nil)
		return;

	// �����Ϸ��� ����� �ڽ��� �ϳ��� �������
	if (node->left == _nil)
	{
		Color color = node->color;
		Node* right = node->right;

		Replace(node, node->right);
		
		// red�̸� �׳� �����ص� ����̾��� ���ǿ����� black�� �ִ�
		if (color == Color::Black)
			DeleteFixup(right);
	}
	else if (node->right == _nil)
	{
	   	Color color = node->color;
		Node* left = node->left;

		Replace(node, node->left);

		// red�̸� �׳� �����ص� ����̾��� ���ǿ����� black�� �ִ�
		if (color == Color::Black)
			DeleteFixup(left);
	}
	// �ڽ��� �ΰ� �ִ� ���
	else
	{
		// �������� ū �����͸� ã�� �����Ͱ��� �ű�� ���
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}

}
// ���� BST ���� ����...
// - Case1) ������ ��尡 Red -> �׳� ����! ��!
// - Case2) root�� DB -> �׳� �߰� Black ����! ��!
// - Case3) DB�� sibling ��尡 Red
// -- s = black, p = red (s <-> p ���� ��ȯ)
// -- DB �������� rotate(p) 
// -- goto other case
// - Case4) DB�� sibling ��尡 Black && sibling�� ���� �ڽĵ� Black
// -- �߰� Black�� parent���� ����
// --- p�� Red�̸� Black ��.
// --- p�� Black�̸� DB ��.
// -- s = red
// -- p�� ������� �˰��� �̾ ���� (DB�� ������ �����ϸ�)
// - Case5) DB�� sibling ��尡 Black && sibling�� near child = red, far child = black
// -- s <-> near ���� ��ȯ
// -- far �������� rotate(s)
// -- goto case 6
// - Case6) DB�� sibling ��尡 Black && sibling�� far child = red
// - p <-> s ���� ��ȯ
// - far = black
// - rotate(p) (DB ��������)
// - �߰� Black ����
void RedBlackTree::DeleteFixup(Node* node)
{
	Node* x = node; // ������ ���

	// [case1][case2]
	while (x != _root && x->color == Color::Black)
	{
		if (x == x->parent->left)
		{
			//[case3]
			Node* s = x->parent->right; // �������

			if (s->color == Color::Red)
			{
				// ������
				//      [p(B)]      -> 	         [p(R)]
				// [x(DB)]  [s(R)]		    [x(DB)]  [s(B)]
				// ȸ��
				//			[s(B)]
				//      [p(R)]
				// [x(DB)]  [1] 
				s->color = Color::Black;
				x->parent->color = Color::Red;

				LeftRotate(x->parent);
				s = x->parent->right;
			}
			// [case4]
			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
				// ������ ������ while���� ���ư��Ƿ� �Ϸ�
			}
			else
			{
				//[case5]
				//			[p]
				//    [x(DB)]  [s(B)]
				//          [n(R)] [f(B)] 
				//			[p]                		[p]
				//    [x(DB)]  [s(R)]      -> [x(DB)]  [n(B)]    
				//          [n(B)] [f(B)] 	              [s(R)]
				//                                            [f(B)]
				if (s->right->color == Color::Black)
				{
					s->left->color = Color::Black;
					s->color = Color::Red;
					RightRotate(s);
					s = x->parent->right;	// near�� s����
				}

				//[case6]
				//			[p]
				//    [x(DB)]  [s(B)]
				//				  [f(R)] 
	
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->right->color = Color::Black;
				LeftRotate(x->parent);
				x = _root; // while�� ���������� ����
			}
		}
		else
		{
			// [Case3]
			Node* s = x->parent->left;
			if (s->color == Color::Red)
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;
				RightRotate(x->parent);
				s = x->parent->left; // [1]
			}

			// [Case4]
			if (s->right->color == Color::Black && s->left->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
			else
			{
				// [Case5]
				if (s->left->color == Color::Black)
				{
					s->right->color = Color::Black;
					s->color = Color::Red;
					LeftRotate(s);
					s = x->parent->left;
				}

				// [Case6]
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->left->color = Color::Black;
				RightRotate(x->parent);
				x = _root;
			}
		}
	}

	x->color = Color::Black;
}

void RedBlackTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	v->parent = u->parent;

	delete u;
}


