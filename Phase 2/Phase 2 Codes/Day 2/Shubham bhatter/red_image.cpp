#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("C:\\Users\\Subham Bhatter\\Downloads\\mast-sherlock-s3-mini-episode-hires.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copy = image;
	namedWindow("Display Red", WINDOW_NORMAL);
	imshow("Display Red", copy);
	waitKey(10);
	int i, j;
	Mat REDIM(image.rows, image.cols, CV_8UC3,Scalar(0,0,255));
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			REDIM.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];


		}
	}
	namedWindow("Display Red", WINDOW_NORMAL);
	imshow("Display Red", REDIM);
	waitKey(0);
	return 0;
}