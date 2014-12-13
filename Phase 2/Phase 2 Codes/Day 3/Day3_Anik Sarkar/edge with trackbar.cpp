#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#define THRESH 127


using namespace cv;
using namespace std;
Mat makebinary(Mat, int);


int main()
{
	Mat image = imread("tulip.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copy = image;
	int t = 10;
	namedWindow("Window1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Window1", &t, 255);
	while (1)
	{
		Mat bin = makebinary(image, t);
		imshow("Window1", bin);
		int a = waitKey(33);
		if (a == 27){
			break;
		}

	}
}
Mat makebinary(Mat xyz, int z)
{
	int i, j;
	Mat REDIM(xyz.rows, xyz.cols, CV_8UC1, Scalar(255));
	for (i = 0; i < xyz.rows; i++)
	{
		for (j = 0; j < xyz.cols; j++)
		{


			if ((uchar)(0.11*xyz.at<Vec3b>(i, j)[2] + 0.33*xyz.at<Vec3b>(i, j)[1] + 0.56*xyz.at<Vec3b>(i, j)[0]) < z)
			{
				REDIM.at<uchar>(i, j) = 0;
			}
		}
	}
	return(REDIM);

	Mat rgbimage;
	rgbimage = imread("tulip.jpg", CV_LOAD_IMAGE_COLOR);
	Mat binary(rgbimage.size(), CV_8UC1);
	for (int i = 0; i < rgbimage.rows; i++)
	{
		for (int j = 0; j < rgbimage.cols; j++)
		{
			if (((rgbimage.at<Vec3b>(i, j)[0] + rgbimage.at<Vec3b>(i, j)[1] + rgbimage.at<Vec3b>(i, j)[2]) / 3)>THRESH)
				binary.at<uchar>(i, j) = 255;
			else
				binary.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", rgbimage);
	namedWindow("Binary", WINDOW_AUTOSIZE);
	imshow("Binary", binary);
	waitKey(0);

}
