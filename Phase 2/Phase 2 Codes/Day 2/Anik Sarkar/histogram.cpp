#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

//Scale Down Factor
#define SCL_FACTOR 10

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
				result.at<uchar>(i, j) = 255;	//Make pixel white
			else
				result.at<uchar>(i, j) = 0;	//Make pixel black
		}
	}
	return result;
}

int main()
{
	Mat image, binary;
	image = imread("e2b.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat histogram((int)((image.rows*image.cols) / SCL_FACTOR), 256, CV_8UC1, Scalar(0));
	int freq[256] = { 0 };
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			freq[image.at<uchar>(i, j)]++;
		}
	}

	for (int j = 0; j < 256; j++)
	{
		for (int i = 0; i < (freq[j] / SCL_FACTOR); i++)
		{
			histogram.at<uchar>(i, j) = 255;
		}
	}

	long long int cum_freq = 0;
	int thresh;
	for (int i = 0; i < 256; i++)
	{
		cum_freq += freq[i];
		if (cum_freq>((image.rows*image.cols) / 2))
		{
			thresh = i;
			break;
		}
	}
	binary = makebinary(image, thresh);
	namedWindow("Normal", CV_WINDOW_AUTOSIZE);
	imshow("Normal", image);
	namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
	imshow("Histogram", histogram);
	namedWindow("Binary", CV_WINDOW_AUTOSIZE);
	imshow("Binary", binary);
	waitKey(0);
	return 0;
}