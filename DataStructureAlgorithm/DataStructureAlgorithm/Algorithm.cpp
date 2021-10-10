#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;
#include "RedBlackTree.h"
#include <thread>

// 시간복잡도 n^2
void BubbleSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
			{
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}
// 선택 정렬
void SelectionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;
		for (int j = i + 1; j < n - 1; j++)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}

		int temp = v[i];
		v[i] = v[bestIdx];
		v[bestIdx] = temp;
	}
}

// 삽입정렬 중요!!
void InsertionSort(vector<int>& v)
{
	const int n = (int)v.size();

	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
			{
				v[j+1] = v[j];
			}
			else
			{
				v[j + 1] = insertData;
				break;
			}

		}
	}
}
int main()
{
#pragma region  redblacktree
	//RedBlackTree bst;
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

	//bst.Delete(20);
	//bst.Print();
	//this_thread::sleep_for(1s);

	//bst.Delete(10);
	//bst.Print();
	//this_thread::sleep_for(1s);
#pragma endregion
	vector<int> v{ 1, 5, 3, 4, 2 };


	InsertionSort(v);

	int x = 3;

}
=======
	bst.Delete(10);
	bst.Print();
	this_thread::sleep_for(1s);
	
}
>>>>>>> 38dfa572f2d421dc7ca22ee996534620adc76220
