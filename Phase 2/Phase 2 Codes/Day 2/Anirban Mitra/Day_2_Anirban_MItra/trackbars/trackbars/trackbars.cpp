// trackbars.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


Mat makebinary(Mat image,int n)
{
	 int temp;
	Mat image2(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			temp = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
			if (temp>n)
				image2.at<uchar>(i, j) = 255;
			else
				image2.at<uchar>(i, j) = 0;
		}
	}
	return image2;
}

int main(int argc, _TCHAR* argv[])
{

	int x = 1;
	Mat img = imread("E:\\walpapers\\VC.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("My Window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "My Window", &x, 150);
	while (true)
	{
		Mat bin = makebinary(img,x);
		imshow("My Window", bin);
		char c = waitKey(33);
		if (c == 27)
			break;
	}
	return 0;
}

