#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("e2b.jpg", CV_LOAD_IMAGE_COLOR);

	namedWindow("Display Red", WINDOW_NORMAL);
	imshow("Display Red", image);
	waitKey(10);

	return 0;


	int i, j;
	Mat REDIM(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 255));
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
}