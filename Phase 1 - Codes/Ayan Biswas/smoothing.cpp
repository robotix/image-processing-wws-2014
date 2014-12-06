#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
#define MAX_KERNEL_LENGTH 10

int main()
{
	Mat image = imread("G:\\lion.jpg", CV_LOAD_IMAGE_COLOR);
	Mat grey(image.rows, image.cols, CV_8UC1);
	Mat Blur(image.rows, image.cols, CV_8UC1);
	Mat Gaussian(image.rows, image.cols, CV_8UC1);
	Mat Median(image.rows, image.cols, CV_8UC1);
	Mat Bilateralfilter(image.rows, image.cols, CV_8UC1);
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
	namedWindow("Blur", CV_WINDOW_AUTOSIZE);
	namedWindow("GaussianBlur", CV_WINDOW_AUTOSIZE);
	namedWindow("MedianBlur", CV_WINDOW_AUTOSIZE);
	namedWindow("Bilateral", CV_WINDOW_AUTOSIZE);
	for (i = 1; i < MAX_KERNEL_LENGTH; i+=2)
	{
		blur(grey, Blur, Size(i, i), Point(-1, -1));
		imshow("Blur", Blur);
		GaussianBlur(grey, Gaussian, Size(i, i), 0, 0);
		imshow("GaussianBlur", Gaussian);
		medianBlur(grey, Median, i);
		imshow("MedianBlur", Median);
		bilateralFilter(grey, Bilateralfilter, i, 0, 0);
		imshow("Bilateral", Bilateralfilter);
		waitKey(0);
	}
	waitKey(0);
	return 0;
}