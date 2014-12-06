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
	image = imread("D:\\baba2.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", image);
	//dilate(image, image, 3);
	erode(image, image, 3);
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	imshow("Output", image);
	waitKey(0);
	return 0;
}