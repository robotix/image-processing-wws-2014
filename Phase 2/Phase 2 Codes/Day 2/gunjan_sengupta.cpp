
#include "stdafx.h"

#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

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
/*
Mat bnw(Mat img1,int thresh)
{
	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0));
	int n;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = img1.at<Vec3b>(i, j)[0] * 0.55 + img1.at<Vec3b>(i, j)[1] * 0.33 + img1.at<Vec3b>(i, j)[2] * 0.11;
			if (n>thresh)
			{
				img2.at<uchar>(i, j) = 0;
			}
			else img2.at<uchar>(i, j) = 255;
		}
	}
	return img2;
}
*/
/*
Mat myinvert(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	for (int i = img1.rows, i1 = 0; (i >= 0) && (i1 < img1.rows ); i--, i1++)
	{
		for (int j = 0,j1=img1.cols; j < img1.cols; j++,j1--)
		{
			img2.at<Vec3b>(i1, j)[0] = img1.at<Vec3b>(i, j1)[0];
			img2.at<Vec3b>(i1, j)[1] = img1.at<Vec3b>(i, j1)[1];
			img2.at<Vec3b>(i1, j)[2] = img1.at<Vec3b>(i, j1)[2];
		}
	}
	return img2;
}*/
void histo(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(255));
	img2 = grey(img1);
	int a[256],i,j;
	for (i = 0; i <=255; i++)
		a[i] = 0;
	for (int k = 0; k <= 255; k++)
	{
		for (i = 0; i < img2.rows; i++)
		{
			for (j = 0; j < img2.cols; j++)
			{


				if (img2.at<uchar>(i, j) == k) a[k]++;

			}
		}
	}
	for (i = 0; i <=255; i++)
	a[i]/=10;

	Mat img(500,256, CV_8UC1,Scalar(255));
	for (j=0; j<img.cols; j++)
	{
		for (i = img.rows-1; img.rows-i<=a[j];i--)
		{
			img.at <uchar>(i, j) = 0;
		}
	}
	namedWindow("histogram", WINDOW_AUTOSIZE);
	imshow("histogram", img);
	waitKey(0);

}

int main()
{
	Mat img1;
	img1 = imread("hqdefault.jpg", CV_LOAD_IMAGE_COLOR);

	//Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(255));

	//img2 = myinvert(img1);
	//int thresh;
	
	//cout << "\n enter the threshold value";
	//cin >> thresh;
	//img2 = bnw(img1,thresh);
	//img2 = grey(img1);

	//namedWindow("haha", WINDOW_AUTOSIZE);
	//imshow("haha", img2);
	histo(img1);
	waitKey(0);
}