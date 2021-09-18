#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "Vector.h"
#include "List.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;



int main()
{
	ArrayQueue<int> q;

	for (int i = 0; i < 100; i++)
		q.push(i);

	while (q.empty() == false)
	{
		int value = q.front();
		q.pop();
		cout << value << endl;
	}
	int size = q.size();
}