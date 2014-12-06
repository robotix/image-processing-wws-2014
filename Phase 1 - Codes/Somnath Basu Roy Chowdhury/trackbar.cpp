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
void display(int thres,Mat image)
{
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j)>thres)
				image.at<uchar>(i, j) = 255;
			else
				image.at<uchar>(i, j) = 0;
		}
	}
}
int main()
{
	Mat image,image1;
	image = imread("D:\\tiger.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	image1 = imread("D:\\tiger.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int i, j,thres=0;
	namedWindow("My", CV_WINDOW_AUTOSIZE);
	imshow("My", image1);
	
	namedWindow("My window", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Track", "My window", &thres, 255);
	while (1)
	{
		
		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				if (image.at<uchar>(i, j)>thres)
					image.at<uchar>(i, j) = 255;
				else
					image.at<uchar>(i, j) = 0;
			}
		}
		imshow("My window", image);
		int ikey = waitKey(50);
		if (ikey == 27)
		{
			break;
		}
	}
}

