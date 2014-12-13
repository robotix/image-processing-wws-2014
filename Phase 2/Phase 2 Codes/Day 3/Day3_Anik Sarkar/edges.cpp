#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
#define THRESH 127
using namespace std;
using namespace cv;

int main()
{
	Mat rgbimage;
	rgbimage = imread("juncker.jpg", CV_LOAD_IMAGE_COLOR);
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
	return 0;
}
