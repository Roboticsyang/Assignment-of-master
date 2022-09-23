#include<iostream>
#include<vector>
using std::vector;

int PARTITION(vector<int>& A, int p, int r)
{
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (A[j] <= x)
		{
			i = i + 1;
			int m = A[i];
			A[i] = A[j];
			A[j] = m;
		}
	}
	//基准数A[r]放到i+1处
	int m = A[i + 1];
	A[i + 1] = A[r];
	A[r] = m;

	return i + 1;
}

int HOARE_PARTITION(vector<int>& A, int p, int r)
{
	int x = A[p];
	int i = p - 1;
	int j = r + 1;
	while (1)
	{
		while (A[i] < x)
		{
			i = i + 1;
		}
		while (A[j] > x)
		{
			j = j - 1;
		}
		if (i < j)
		{
			int m = A[i];
			A[i] = A[j];
			A[j] = m;
		}
		else
		{
			break;
		}
	}
	return j;
}

void QUICKSORT(vector<int>& A, int p, int r)
{
	if (p < r)
	{
		int q = PARTITION(A, p, r);
		QUICKSORT(A, p, q - 1);
		QUICKSORT(A, q + 1, r);
	}
}

void HOARE_QUICKSORT(vector<int>& A, int p, int r)
{
	if (p < r)
	{
		int q = HOARE_PARTITION(A, p, r);
		HOARE_QUICKSORT(A, p, q - 1);
		HOARE_QUICKSORT(A, q + 1, r);
	}
}

int main()
{

	vector<int> A = { 8,13,15 };//12个
	QUICKSORT(A, 0, A.size() - 1);
	std::cout << "1)已有的划分算法：";
	for (auto i : A)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	vector<int> B = { 13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21 };//12个
	HOARE_QUICKSORT(B, 1, B.size() - 2);
	std::cout << "1)C．R．Hoare划分算法：";
	for (auto i : B)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	return 0;
}