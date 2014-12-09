#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;



int main()
{
	Mat image = imread("G:\\lion.jpg", CV_LOAD_IMAGE_COLOR);
	Mat grey(image.rows, image.cols, CV_8UC1);
	Mat binary1(image.rows, image.cols, CV_8UC1);
	int i, j;
	int b, g, r;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			grey.at<uchar>(i, j) = (b + g + r) / 3;
		}
	}
	int freq[256];
	for (i = 0; i < 256; ++i)
		freq[i] = 0;
	for (i = 0; i < image.rows; ++i)
		for (j = 0; j < image.cols; ++j)
			freq[grey.at<uchar>(i, j)]++;
	int sum = 0, thres1 = 0;
	while (sum < (image.rows*image.cols) / 2)
		sum += freq[thres1++];
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			if (grey.at<uchar>(i, j) > thres1)
				binary1.at<uchar>(i, j) = 255;
			else
				binary1.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	namedWindow("Grey", CV_WINDOW_AUTOSIZE);
	namedWindow("Freq", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	imshow("Grey", grey);
	imshow("Freq", binary1);
	waitKey(0);
	return 0;
}