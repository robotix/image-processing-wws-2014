// noise_reduction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main(int argc, _TCHAR* argv[])
{
	int n=50;
	Mat img = imread("E:\\walpapers\\VC.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			int max = img.at<uchar>(i-1, j-1);
			int min = img.at<uchar>(i-1, j-1);
			for (int r = i - 1; r <= i + 1; r++)
			{
				for (int c = j - 1; c <= j + 1; c++)
				{
					if (img.at<uchar>(r, c)>max)
						max = img.at<uchar>(r, c);
					if (img.at<uchar>(r,c)<min)
						min = img.at<uchar>(r, c);
				}
			}
			if (max - min >= n)
				img2.at<uchar>(i, j) = 255;
		}
	}
	Mat img3(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (int i = 1; i < img2.rows - 1; i++)
	{
		for (int j = 1; j < img2.cols - 1; j++)
		{
			int w = 0; int b = 0;
			for (int r = i - 1; r <= i + 1; r++)
			{
				for (int c = j - 1; c <= j + 1; c++)
				{
					if (img2.at<uchar>(r, c) == 0)
						b++;
					else
						w++;
				}
			}
			if (b == 0 || w == 0)
			{
				if (b == 0)
					img3.at<uchar>(i, j) = 255;
				else
					img3.at<uchar>(i, j) = 0;
			}
			else if (b > w)
				img3.at<uchar>(i, j) = 0;
			else
				img3.at<uchar>(i, j) = 255;
		}
	}
	Mat img4(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (int i = 1; i < img3.rows - 1; i++)
	{
		for (int j = 1; j < img3.cols - 1; j++)
		{
			int b = 0; int w = 0;
			for (int r = i - 1; r <= i + 1; r++)
			{
				for (int c = j - 1; c <= j + 1; c++)
				{
					if (img3.at<uchar>(i, j) == 0)
						b++;
					else
						w++;
				}
			}
			if (b == 0 || w == 0)
			{
				if (b == 0)
					img4.at<uchar>(i, j) = 255;
				else
					img4.at<uchar>(i, j) = 0;
			}
			else if (b > w)
				img4.at<uchar>(i, j) = 255;
			else
				img4.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("Dilution", WINDOW_AUTOSIZE);
	imshow("Dilution", img3);
	namedWindow("Erosion", WINDOW_AUTOSIZE);
	imshow("Erosion", img4);
	waitKey(0);
	return 0;
}

