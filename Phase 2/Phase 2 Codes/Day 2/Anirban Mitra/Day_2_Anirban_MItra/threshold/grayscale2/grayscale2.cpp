// grayscale2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int get_no()
{
	int a;
	cout << "Enter the threshold frequency" << endl;
	cin >> a;
	return a;
}
Mat get_image()
{
	Mat i = imread("E:\\walpapers\\VC.jpg", CV_LOAD_IMAGE_COLOR);
	return i;
}

int main(int argc, _TCHAR* argv[])
{
	int n = get_no();
	Mat image = get_image(); int temp;
	Mat image2(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			temp=(image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
			if (temp>n)
				image2.at<uchar>(i, j) = 255;
			else
				image2.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("My Window", WINDOW_AUTOSIZE);
	imshow("My Window", image);
	namedWindow("My Window2", WINDOW_AUTOSIZE);
	imshow("My Window2", image2);
	waitKey(0);
	return 0;
}

