// hsv_convert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;

Mat hsv(Mat img)
{
	Mat img2(img.rows, img.cols, CV_8UC1);
	cvtColor(img, img, CV_BGR2HLS_FULL);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<Vec3b>(i, j)[0] >115 && img.at<Vec3b>(i, j)[0] < 125)
				img2.at<uchar>(i, j) = 255;
			else
				img2.at<uchar>(i, j) = 0;
		}
	}
	return img2;
}

int main(int argc, _TCHAR* argv[])
{
	Mat img1 = imread("E:\\walpapers\\hsv.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("HSV", WINDOW_NORMAL);
	namedWindow("Original", WINDOW_NORMAL);
	imshow("Original", img1);
	imshow("HSV", hsv(img1));
	waitKey(0);
	return 0;
}

