#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
	Mat image;
	image = imread("samantha.jpg", CV_LOAD_IMAGE_COLOR);
	if (image.empty())
		exit(1);
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	imshow("My Window", image);
	waitKey(0);
}