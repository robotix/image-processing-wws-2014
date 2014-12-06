#include "stdafx.h"
#include "opencv2/core/core.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <queue>

using namespace std;
using namespace cv;


int main(int argc, _TCHAR* argv[])
{
	int i, j, n, k;
	cin >> n;

	vector<vector<int> > arr;
	for (int i = 0; i < n; i++)
	{
		vector<int> a;
		for (int j = 0; j < n; j++)
		{

			cin >> k;
			a.push_back(k);
		}
		arr.push_back(a);
	}
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{

			cout << " " << arr[i][j];
		}

	}
	waitKey(0);
	return 0;
}