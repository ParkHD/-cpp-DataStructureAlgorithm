#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
#include "RedBlackTree.h"
#include <thread>


int main()
{
	RedBlackTree bst;
	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(10);
	bst.Print();
	this_thread::sleep_for(1s);
	

	//bst.Insert(30);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(10);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(20);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(25);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(40);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(50);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(15);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(60);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(5);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(22);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(23);
	//bst.Print();
	//this_thread::sleep_for(1s);
	//bst.Insert(21);
	//bst.Print();
	//this_thread::sleep_for(1s);
}