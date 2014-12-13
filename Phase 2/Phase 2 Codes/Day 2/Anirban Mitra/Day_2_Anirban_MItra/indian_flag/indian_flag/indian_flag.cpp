// indian_flag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;


int _tmain(int argc, _TCHAR* argv[])
{
	Mat img(450, 900, CV_8UC3, Scalar(255, 255, 255));
	for (int i = 0; i < 150; i++)
	{
		for (int j = 0; j < 900; j++)
		{
			img.at<Vec3b>(i, j)[0] = 0;
			img.at<Vec3b>(i, j)[1] = 165;
		}
	}
	for (int i = 300; i < 450; i++)
	{
		for (int j = 0; j < 900; j++)
		{
			img.at<Vec3b>(i, j)[0] = 0;
			img.at<Vec3b>(i, j)[2] = 0;
		}
	}
	namedWindow("My Window", WINDOW_AUTOSIZE);
	imshow("My Window", img);
	waitKey(0);
	return 0;
}

