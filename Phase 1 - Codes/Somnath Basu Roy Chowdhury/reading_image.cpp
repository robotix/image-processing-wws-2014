// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<vector>
using namespace std;
using namespace cv;

int main()
{
	Mat image;
	image = imread("D://tiger.jpg",CV_LOAD_IMAGE_COLOR);
	namedWindow("My window", CV_WINDOW_AUTOSIZE);
	imshow("My window", image);
	waitKey(0);
}
