#include"stdafx.h"

#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
/*

Mat grey(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			img2.at<uchar>(i, j) = img1.at<Vec3b>(i, j)[0] * 0.55 + img1.at<Vec3b>(i, j)[1] * 0.33 + img1.at<Vec3b>(i, j)[2] * 0.11;
		}
	}
	return img2;

}
Mat bnw(Mat img1, int thresh)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int n;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = img1.at<uchar>(i, j);
			if (n>thresh)
			{
				img2.at<uchar>(i, j) = 0;
			}
			else img2.at<uchar>(i, j) = 255;
		}
	}
	return img2;
}

int main()
{
	Mat img1;
	img1 = imread("hqdefault.jpg", CV_LOAD_IMAGE_COLOR);

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	img2 = grey(img1);
	namedWindow("controller", WINDOW_AUTOSIZE);
	int x = 10;
	createTrackbar("threshold","controller", &x,250);
	while (1)
	{
		Mat img = bnw(img2, x);
		imshow("controller", img);
		char a = waitKey(33);
		if (a == 27) break;
	}

}