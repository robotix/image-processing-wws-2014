// Sample_Project3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat image(450, 900, CV_8UC3, Scalar(0, 0, 0));
	int i, j,k,l;
	for ( i = 0; i < image.rows; i++)
	{
		for ( j = 0; j < image.cols; j++)
		{
			if (i<image.rows/3)
			{
				image.at<Vec3b>(i, j)[1] = 165;
				image.at<Vec3b>(i, j)[2] = 255;
			}
			else if (i<(2*image.rows)/3)
			{
				image.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				image.at<Vec3b>(i, j)[1] = 255;
			}
		}
	}
	for (k = image.rows / 3; k < (2 * image.rows) / 3;k+=2)
	for (l = (2 * image.cols) / 5; l < (3 * image.cols) / 5; l+=2)
	{
		if (((k - image.rows / 2)*(k - image.rows / 2) + (l - image.rows / 2)*(l - image.rows / 2)) <= (image.rows / 6)*(image.rows/6))
		image.at<Vec3b>(k, l)[0] = image.at<Vec3b>(k, l)[1] = image.at<Vec3b>(k, l)[2] = 0;
	}
	namedWindow("Output Window", CV_WINDOW_AUTOSIZE);
	imshow("Output Window", image);
	waitKey(0);
	return 0;
}