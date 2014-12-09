//brg to binary
// ConsoleApplication3.cpp : Defines the entry point for the console application.


// ConsoleApplication3.cpp : Defines the entry point for the console application.


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
	Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < final.rows; i++)
	{
		for (int j = 0; j < final.cols; j++)
		{
			if (((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3) > 120)
			{
				final.at<uchar>(i, j) = 255;
			}
			else
				final.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	imshow("My Window", final);
	waitKey(0);
	return 0;
}