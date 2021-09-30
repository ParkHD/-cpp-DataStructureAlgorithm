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
	// 전위 순회(preorder traverse) [중][좌][우]
	// 중위 순회(inorder )			[좌][중][우]
	// 후위 순회(postorder )		[좌][우][중]
	if (node == _nil)
		return;

	cout << node->key << endl; // 위치에 따라 어떤 순회인지 가려짐(앞 : 전위, 가운데 : 중위, 뒤 : 후위)
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

	// 부모 노드가 없거나 노드(node)가 부모노드(parent)의 왼쪽자식노드(parent->left)일때까지 찾는다
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

	// 데이터가 없을 때
	if (parent == _nil)
		_root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	// 검사
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);
}

void RedBlackTree::InsertFixup(Node* node)
{
	// 1) p = red, uncle = red
	// 	   -> p = black, u = black, pp = red 로 바꿈
	// 2) p = red, uncle = black (triangle)
	// 	   -> 회전을 통해 case3로 바꿈
	// 3) p = red, uncle = black (list)
	// 	   -> 생삭변경 + 회전
	// p = black 이면 할 필요없음 그냥 삽입

	//		[pp(B)]
	// [p(R)]		[u]
	//	   [n(R)]
	while (node->parent->color == Color::Red) // 삽입하는 노드는 Red이기 때문에 레드가 2연속 나오지 않게 하기위함
	{
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				node->parent->parent->color = Color::Red; // 여기서 반복이 일어난다 부부모랑 부부부모색이 같을 수 있다.
				node = node->parent->parent;			
			}
			else
			{
				// triangle        			  list
				//		[pp(B)]        ->    		[pp(B)]
				// [p(R)]		[u]			    [p(R)]		[u]
				//	   [n(R)]				 [n(R)]	   


				if (node == node->parent->right) // triangle 이라면
				{
					node = node->parent;
					LeftRotate(node);
				}
				// 색변경
				//		[pp(B)]           		 [pp(R)]
				//   [p(R)]		[u]   ->     [p(B)]	   [u(B)]
				//[n(R)]	 			  [n(R)]	
				// 회전
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
				// triangle이면 list로 바꿈
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
				// list 타입 이면
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

	// x - [2] 연결
	x->right = y->left;	
	// [2]가 nil 일수 있다
	if (y->left != _nil)
		y->left->parent = x;

	// x y 교체
	y->parent = x->parent;
	if (x->parent == _nil)	// root인지 검사
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
	// [2]가 nil 일수 있다
	if (y->right != _nil)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == _nil)	// root인지 검사
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

	// 삭제하려는 노드의 자식이 하나만 있을경우
	if (node->left == _nil)
	{
		Color color = node->color;
		Node* right = node->right;

		Replace(node, node->right);
		
		// red이면 그냥 삭제해도 상관이없다 조건영향은 black이 있다
		if (color == Color::Black)
			DeleteFixup(right);
	}
	else if (node->right == _nil)
	{
	   	Color color = node->color;
		Node* left = node->left;

		Replace(node, node->left);

		// red이면 그냥 삭제해도 상관이없다 조건영향은 black이 있다
		if (color == Color::Black)
			DeleteFixup(left);
	}
	// 자식이 두개 있는 경우
	else
	{
		// 다음으로 큰 데이터를 찾고 데이터값만 옮기고 재귀
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}

}
// 먼저 BST 삭제 실행...
// - Case1) 삭제할 노드가 Red -> 그냥 삭제! 끝!
// - Case2) root가 DB -> 그냥 추가 Black 삭제! 끝!
// - Case3) DB의 sibling 노드가 Red
// -- s = black, p = red (s <-> p 색상 교환)
// -- DB 방향으로 rotate(p) 
// -- goto other case
// - Case4) DB의 sibling 노드가 Black && sibling의 양쪽 자식도 Black
// -- 추가 Black을 parent에게 이전
// --- p가 Red이면 Black 됨.
// --- p가 Black이면 DB 됨.
// -- s = red
// -- p를 대상으로 알고리즘 이어서 실행 (DB가 여전히 존재하면)
// - Case5) DB의 sibling 노드가 Black && sibling의 near child = red, far child = black
// -- s <-> near 색상 교환
// -- far 방향으로 rotate(s)
// -- goto case 6
// - Case6) DB의 sibling 노드가 Black && sibling의 far child = red
// - p <-> s 색상 교환
// - far = black
// - rotate(p) (DB 방향으로)
// - 추가 Black 제거
void RedBlackTree::DeleteFixup(Node* node)
{
	Node* x = node; // 삭제할 노드

	// [case1][case2]
	while (x != _root && x->color == Color::Black)
	{
		if (x == x->parent->left)
		{
			//[case3]
			Node* s = x->parent->right; // 형제노드

			if (s->color == Color::Red)
			{
				// 색변경
				//      [p(B)]      -> 	         [p(R)]
				// [x(DB)]  [s(R)]		    [x(DB)]  [s(B)]
				// 회전
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
				// 나머지 조건은 while문이 돌아가므로 완료
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
					s = x->parent->right;	// near가 s가됨
				}

				//[case6]
				//			[p]
				//    [x(DB)]  [s(B)]
				//				  [f(R)] 
	
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->right->color = Color::Black;
				LeftRotate(x->parent);
				x = _root; // while문 빠져나오기 위함
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


