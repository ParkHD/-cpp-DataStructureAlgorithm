#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node() {}
	Node(const string& data) : data(data) {}
	string data;
	vector<NodeRef> children;
};
NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf1 = make_shared<Node>("전투");
			node->children.push_back(leaf1);

			NodeRef leaf2 = make_shared<Node>("경재");
			node->children.push_back(leaf2);
			NodeRef leaf3 = make_shared<Node>("스토리");
			node->children.push_back(leaf3);
		}
		NodeRef node2 = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node2);
		{
			NodeRef leaf1 = make_shared<Node>("서버");
			node2->children.push_back(leaf1);
			NodeRef leaf2 = make_shared<Node>("클라");
			node2->children.push_back(leaf2);
			NodeRef leaf3 = make_shared<Node>("엔진");
			node2->children.push_back(leaf3);
		}
		NodeRef node3 = make_shared<Node>("아트팀");
		root->children.push_back(node3);
		{
			NodeRef leaf1 = make_shared<Node>("배경");
			node3->children.push_back(leaf1);
			NodeRef leaf2 = make_shared<Node>("캐릭터");
			node3->children.push_back(leaf2);
		}
	}
	return root;
}

// 트리만들때는 재귀함수를 생각하자
void PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "-";
	}
	cout << root->data << endl;
	for (NodeRef& child : root->children)
	{
		PrintTree(child, depth + 1);
	}
}

int GetHeight(NodeRef root)
{
	int height = 1;

	for (NodeRef& child : root->children)
	{
		height = max(height, GetHeight(child) + 1);
	}

	return height;
}