// histogram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main(int argc, _TCHAR* argv[])
{
	int a[256] = { 0 };
	Mat img = imread("E:\\walpapers\\VC.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	int count = 0;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			a[img.at<uchar>(i, j)]++;
		}
	}
	Mat histo(400, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++)
	{
		for (int j = 399; j>400-(a[i] /100);j--)
		{
			histo.at<uchar>(j,i) = 0;
		}
	}
	int total = img.rows*img.cols; int sum = 0; int n;
	for (int i = 0; i < 256; i++)
	{
		sum += a[i];
		if (sum >= (total) / 2)
		{
			n = i;
			break;
		}
	}
	Mat image2(img.rows, img.cols, CV_8UC1); int temp;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			temp = img.at<uchar>(i, j);
			if (temp>n)
				image2.at<uchar>(i, j) = 255;
			else
				image2.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("My Window", WINDOW_AUTOSIZE);
	imshow("My Window", histo);
	namedWindow("My Window2", WINDOW_AUTOSIZE);
	imshow("My Window2", image2);
	waitKey(0);

	return 0;
}

