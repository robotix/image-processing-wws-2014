#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
using namespace std;
using namespace cv;

Mat print(Mat im)
{
	Mat image(im.rows, im.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < im.rows; i++)
	{
		for (int j = 0; j < im.cols; j++)
		{
			if (im.at<uchar>(i, j) < 5)
				image.at<uchar>(i, j) = 255;
		}
	}
	return image;
}

int main(int argc, _TCHAR* argv[])
{
	Mat img = imread("E:\\walpapers\\line.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat hough(sqrt(img.rows*img.rows + img.cols*img.cols), 181, CV_8UC1, Scalar(0));
	int r;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) <5)
			{
				for (int k = 0; k < 181; k++)
				{
					r = abs(i*sin(k) + j*cos(k));
					hough.at<uchar>(r, k) = hough.at<uchar>(r, k) +1;
				}
			}
		}
	}
	int m, n; int max = hough.at<uchar>(0, 0);
	for (int i = 0; i < hough.rows; i++)
	{
		for (int j = 0; j < hough.cols; j++)
		{
			if (hough.at<uchar>(i, j)>max)
			{
				max = hough.at<uchar>(i, j);
				m = i;
				n = j;
			}
		}
	}
	Mat img3(img.rows, img.cols, CV_8UC1, Scalar(0));
	float s = 0.0; int j = 0; float a = 0.0;
	for(int i = 0; i < img3.rows; i++)
	{
		s = (m - (i*sin((3.14*n) / 180)));
		a = cos(n);
		j = abs(s /a );
		img3.at<uchar>(i,j) = 255;
	}
	namedWindow("Line", WINDOW_AUTOSIZE);
	imshow("Line", img3);
	namedWindow("All", WINDOW_AUTOSIZE);
	imshow("All", print(img));
	waitKey(0);
	return 0;
}