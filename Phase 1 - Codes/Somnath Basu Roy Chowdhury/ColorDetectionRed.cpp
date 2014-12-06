// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
using namespace cv;
int main()
{
	Mat image;
	image = imread("D:\\redball.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image1(image.rows, image.cols, CV_8UC1);
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	int thres=100, thres1=0,i,j;
	createTrackbar("T1", "Output", &thres, 255);
	createTrackbar("T2", "Output", &thres1, 255);
	while (1)
	{
		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				if (image.at<Vec3b>(i, j)[0] < thres&&image.at<Vec3b>(i, j)[1]<thres&&image.at<Vec3b>(i, j)[2]>thres1)
				{
					/*image.at<Vec3b>(i, j)[0] = 0;
					image.at<Vec3b>(i, j)[1] = 0;
					image.at<Vec3b>(i, j)[2] = 0;*/
					image1.at<uchar>(i, j) = 0;
				}
				else
				{
					/*image.at<Vec3b>(i, j)[0] = 255;
					image.at<Vec3b>(i, j)[1] = 255;
					image.at<Vec3b>(i, j)[2] = 255;*/
					image1.at<uchar>(i, j) = 255;
				}
			}
		}
		imshow("Output", image1);
		
		if (waitKey(30) == 27)
			break;
	}
	return 0;
}



