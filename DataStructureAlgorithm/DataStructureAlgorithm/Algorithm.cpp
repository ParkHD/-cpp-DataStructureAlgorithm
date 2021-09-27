#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

vector<int> numbers;
void BinarySearch(int N)
{
	int left = 0;
	int right = (int)numbers.size() - 1;

	while (left <= right)
	{
		cout << "Ž�� ���� :" << left << "~" << right << endl;
		int mid = (left + right) / 2;

		if (N < numbers[mid])
		{
			cout << N << " < " << numbers[mid] << endl;
			right = mid - 1;
		}
		else if (N > numbers[mid])
		{
			cout << N << " > " << numbers[mid] << endl;
			left = mid + 1;
		}
		else
		{
			cout << "ã�� !!" << endl;
			break;
		}
	}
}
int main()
{
	numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 70, 77, 90 };
	BinarySearch(32);
}