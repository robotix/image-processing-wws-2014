#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("G:\\lion.jpg", CV_LOAD_IMAGE_COLOR);
	int i, j;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			image.at<Vec3b>(i, j)[0] = 255 - image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[1] = 255 - image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[2] = 255 - image.at<Vec3b>(i, j)[2];
		}
	}
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", image);
	waitKey(0);
	return 0;
}
