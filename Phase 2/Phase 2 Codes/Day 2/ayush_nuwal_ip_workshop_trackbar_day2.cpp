#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include<iostream>
using namespace std;
using namespace cv;


int main()
{
	int i, j, k, x = 10,Threshold;
	Mat image2;
	image2 = imread("C:\\Users\\Dell\\Desktop\\900.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	//namedWindow("My window", WINDOW_AUTOSIZE);
	Mat image(image2.size(), CV_8UC1);
	//int a[256] = { 0 };
	/*for (k = 0; k < 256; k++)
	{
		a[k] = 0;
	}*/
	/*
	for (k = 0; k < 256; k++)
	{
		for (i = 0; i < image2.rows; i++)
		{
			for (j = 0; j < image2.cols; j++)
			{
				if(image2.at<uchar>(i, j) == k)
				a[k] = a[k] + 1;
			}
		}
	}
	Mat image(((image2.rows*image2.cols)/100), 256, CV_8UC1,Scalar(0)); */
	/*for (i = 0; i < image1.rows; i++)
	{
		for (j = 0; j < image1.cols; j++)
		{
			image.at<uchar>(i, j) = 255;
		}
	}
*/
	/*for (k = 0; k < 256; k++)
	{
		a[k] = a[k] / 10;
	}*/
	/*for (j = 0; j< 256; j++)
		{
			for (i = 0; i < a[j]/100; i++)
			{
				image.at<uchar>(i, j) = 255;
			}
		} */
	namedWindow("My window", WINDOW_NORMAL);
	createTrackbar("Threshold", "My window", &x, 255);
	while (1)
	{
		for (i = 0; i < image2.rows; i++)
		{
			for (j = 0; j < image2.cols; j++)
			{
				if (image2.at<uchar>(i, j) > x)
				{
					image.at<uchar>(i, j) = 255;
				}
				else
					image.at<uchar>(i, j) = 0;
			}
		}
		imshow("My window", image);
		char a = waitKey(33);
		if (a == 27) break;
	}
	namedWindow("My window histogram", WINDOW_AUTOSIZE);
	imshow("My window", image2);
	imshow("My window histogram", image);
	waitKey(0);
	return 0;
}