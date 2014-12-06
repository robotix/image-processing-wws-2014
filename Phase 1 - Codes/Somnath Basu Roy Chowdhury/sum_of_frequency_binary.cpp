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
	Mat image,image1;
	image = imread("D:\\tiger.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	image1 = imread("D:\\tiger.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int freq[256];
	int i, j;
	for (i = 0; i < 256; i++)
		freq[i] = 0;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			freq[(int)image.at<uchar>(i,j)]++;
		}
	}
	int sum = 0,thres=0;
	for (i = 0; i < 256; i++)
	{
		if (sum < (image.rows)*(image.cols) / 2)
		{
			sum += freq[i]; thres = i;
		}
		else
			break;
	}
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
	namedWindow("My", CV_WINDOW_AUTOSIZE);
	namedWindow("My window", CV_WINDOW_AUTOSIZE);
	imshow("My window", image);
	imshow("My", image1);
	waitKey(0);
}

