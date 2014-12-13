// prac.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main(int argc, _TCHAR* argv[])
{
	Mat img;
	img = imread("E:\\walpapers\\VC.jpg", CV_LOAD_IMAGE_COLOR);
	
	int column = img.cols;
	int row = img.rows; int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			//img.at<Vec3b>(i,j)[2] =255;
			img.at<Vec3b>(i,j)[0] =0;
			img.at<Vec3b>(i,j)[1] =0;
		}
	}
	namedWindow("My Window", WINDOW_AUTOSIZE);
	imshow("My Window", img);
	waitKey(0);
	return 0;
}

