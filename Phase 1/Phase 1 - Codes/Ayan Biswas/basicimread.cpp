#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("G:\\lion.jpg", 0);
	if (image.empty())
		exit(1);
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", image);
	waitKey(0);
	return 0;
}