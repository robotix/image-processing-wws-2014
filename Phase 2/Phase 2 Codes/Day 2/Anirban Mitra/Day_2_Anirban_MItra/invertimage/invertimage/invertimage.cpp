// invertimage.cpp : Defines the entry point for the console application.
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
	Mat imgx(img.rows, img.cols, CV_8UC3);
	//Mat imgy(img.rows, img.cols, CV_8UC1);
	for (int j = 0; j < img.cols; j++)
	{
		for (int i = 0; i < img.rows;i++)
		{
			imgx.at<Vec3b>(i, j)[0] = img.at<Vec3b>(img.rows-1-i,j)[0];
			imgx.at<Vec3b>(i, j)[1] = img.at<Vec3b>(img.rows - 1 - i, j)[1];
			imgx.at<Vec3b>(i, j)[2] = img.at<Vec3b>(img.rows - 1 - i,j)[2];
		}
	}

	namedWindow("My Window", WINDOW_AUTOSIZE);
	namedWindow("My Window2", WINDOW_AUTOSIZE);
	imshow("My Window2", img);
	imshow("My Window", imgx);
	waitKey(0);
	return 0;
}

