#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;


Mat makebinary(Mat image, int threshold)
{
	Mat result(image.size(), CV_8UC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j)>threshold)
				result.at<uchar>(i, j) = 255;
			else
				result.at<uchar>(i, j) = 0;	
		}
	}
	return result;
}

int main()
{
	Mat image;
	image = imread("e2b.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Original", WINDOW_AUTOSIZE);
	namedWindow("Binary", WINDOW_AUTOSIZE);
	int threshold = 10;
	createTrackbar("Threshold", "Binary", &threshold, 255);
	while (1)
	{
		Mat gray;
		Mat binary = makebinary(image, threshold);
		imshow("Original", image);
		imshow("Binary", binary);
		char a = waitKey(33);
		if (a == 27) break;
	}
	return 0;
}