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
	image = imread("D:\\tiger.jpg",CV_LOAD_IMAGE_COLOR);
	namedWindow("My window", CV_WINDOW_AUTOSIZE);
	Mat grey;
	int x, y, i, j;
	x = image.rows;
	y = image.cols;
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			if ((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3>127)
			{
				image.at<Vec3b>(i, j)[0] = 255;
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				image.at<Vec3b>(i, j)[0] = 0;
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	imshow("My window", image);
	waitKey(0);
}
