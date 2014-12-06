#include "stdafx.h"
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<stdio.h>

using namespace std;
using namespace cv;
/*
int main()
{
	Mat image = imread("C:\\Users\\PRIYANK YADAV\\visual photos\\11.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j,t;
	namedWindow("track", WINDOW_AUTOSIZE);
	cvCreateTrackbar("TRACHI", "track", &t, 255);
	while (1)
	{
		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				if (image.at<uchar>(i, j) > t) image2.at<uchar>(i, j) = 180;
				else
					image2.at<uchar>(i, j) = 50;
			}
		}
		imshow("track", image2);
		int ikey = waitKey(50);
		if (ikey == 27)
			break;
	}
	waitKey(0);
	return(0);
}*/