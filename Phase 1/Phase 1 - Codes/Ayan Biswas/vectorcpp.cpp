#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<vector<int>> A;
	int i, j, a;
	for (j = 0; j<2; ++j)
	{
		vector<int> temp;
		for (i = 0; i<3; ++i)
		{
			cin >> a;
			temp.push_back(a);
		}
		A.push_back(temp);
	}
	for (j = 0; j<2; ++j)
	{
		for (i = 0; i<3; ++i)
			cout << A[j][i] % 10 << " ";
		cout << endl;
	}
	cin >> a;
	return 0;
}