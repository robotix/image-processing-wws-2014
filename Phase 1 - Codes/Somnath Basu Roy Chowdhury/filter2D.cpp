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
	image = imread("D:\\tiger.jpg",CV_LOAD_IMAGE_COLOR);
	Mat image1(image.rows, image.cols, CV_8UC3);
	Mat kernel;
	int ind=0,kernel_size,c;
	Point anchor; 
	double delta;
	namedWindow("filter2D_demo", CV_WINDOW_AUTOSIZE);
	imshow("filter2D_demo", image);
	anchor = Point(-1, -1);
	delta = 0;
	while (1)
	{
		c = waitKey(1000);
		if (c == 27)
			break;
		kernel_size = 3 + 2 * (ind % 5);
		kernel = Mat::ones(kernel_size,kernel_size,CV_32F)/(float)(kernel_size*kernel_size);
		filter2D(image, image1, -1, kernel, anchor, delta, BORDER_DEFAULT);
		imshow("My window", image1);
		ind++;
	}
    waitKey(0);
	return 0;
}

