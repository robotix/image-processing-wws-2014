#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace cv;
int main()
{
	Mat image;
	image = imread("F:\\picture001.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	int t1 =100, t2 = 100, i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if ((image.at<Vec3b>(i, j)[2]>t1) && (image.at<Vec3b>(i, j)[1] < t2) && (image.at<Vec3b>(i, j)[0] < t2))
				image1.at<uchar>(i, j) = 255;
			else
				image1.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("Colour", WINDOW_AUTOSIZE);
	imshow("Colour", image1);
	waitKey(0);
	return 0;
}