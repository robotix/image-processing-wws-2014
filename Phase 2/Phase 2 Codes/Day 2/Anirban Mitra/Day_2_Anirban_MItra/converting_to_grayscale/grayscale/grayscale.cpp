// grayscale.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;


int main(int argc, _TCHAR* argv[])
{
	Mat img = imread("E:\\walpapers\\VC.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image(img.rows, img.cols, CV_8UC1);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			image.at<uchar>(i, j) = .56*img.at<Vec3b>(i, j)[0] + .33*img.at<Vec3b>(i, j)[1] + .11*img.at<Vec3b>(i, j)[2];
		}
	}
	namedWindow("MY Window", WINDOW_AUTOSIZE);
	namedWindow("MY Window2", WINDOW_AUTOSIZE);
	imshow("My Window", image);
	imshow("My Window2", img);
	waitKey(0);
	return 0;
}
