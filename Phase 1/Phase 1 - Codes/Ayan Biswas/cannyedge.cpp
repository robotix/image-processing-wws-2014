#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("G:\\sudoku2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat grey(image.rows, image.cols, CV_8UC1);
	int i, j;
	int b, g, r;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			grey.at<uchar>(i, j) = (33 * b + 56 * g + 11 * r) / 100;
		}
	}
	int freq[256];
	for (i = 0; i < 256; ++i)
		freq[i] = 0;
	for (i = 0; i < image.rows; ++i)
	for (j = 0; j < image.cols; ++j)
		freq[grey.at<uchar>(i, j)]++;
	Mat cannyedge(image.rows, image.cols, CV_8UC1);
	int sum=0, thres=0;
	while (sum < (image.rows*image.cols) / 2)
			sum += freq[thres++];
	int threslow = thres / 3;
	int threshigh = thres * 2 / 3;
	Canny(grey, cannyedge, threslow, threshigh, 3);
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	namedWindow("Grey", CV_WINDOW_AUTOSIZE);
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	imshow("Grey", grey);
	imshow("Canny", cannyedge);
	waitKey(0);
	return 0;
}