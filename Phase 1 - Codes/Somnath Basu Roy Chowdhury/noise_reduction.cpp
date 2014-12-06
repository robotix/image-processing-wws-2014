// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<stdio.h>
using namespace std;
using namespace cv;
int main()
{
	Mat image;
	image= imread("D:\\ball.jpg",CV_LOAD_IMAGE_COLOR);
	Mat image1(image.rows, image.cols, CV_8UC1);
	int i, j,k,l;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if ((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3>127)
				image1.at<uchar>(i, j) = 255;
			else
				image1.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", image1);
	for (i = 0; i < image1.rows; i++)
	{
		for (j = 0; j < image1.cols; j++)
		{
			if (i >= 1 && j >= 1 && i < image1.rows - 1 && j < image.cols - 1)
			{
				int b = 0, w = 0;
				for (k = i - 1; k <= i + 1; k++)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						if (image1.at<uchar>(k, l) == 255)
							w++;
						else
							b++;
					}
				}
				if (w > b)
					image1.at<uchar>(i, j) = 255;
				else
					image1.at<uchar>(i, j) = 0;
			}
		}
	}
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	
	imshow("Output", image1);
    waitKey(0);
	return 0;
}
