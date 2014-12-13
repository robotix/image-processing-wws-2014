#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
using namespace cv;
using namespace std;
Mat border1(Mat img)
{
	Mat img1(img.size(), CV_8UC1);
	int i, j, k, l,max=-1,min=256,th;
	cout << "enter a threshhold";
	cin >> th;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
			img.at<uchar>(i, j) = 255;
	}
	
	
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			for (k = i - 1; k < i + 2; k++)
			{
				for (l = j - 1; l < l + 2; l++)
				{
					if (img.at<uchar>(k, l)>max)
						max = img.at<uchar>(k, l);
					if (img.at<uchar>(k, l) < min)
						min = img.at<uchar>(k, l);
					if (max - min>th)
						img1.at<uchar>(k, l) = 0;
				}
			}
		}
	}


	return img1;
}

Mat border2(Mat img)
{
	Mat img1(img.size(), CV_8UC1);
	int i, j, x, y,t;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			x = 2*img.at<uchar>(i, j + 1) + img.at<uchar>(i + 1, j + 1) + img.at<uchar>(i - 1, j + 1) - 2*img.at<uchar>(i, j - 1) - img.at<uchar>(i + 1, j - 1) - img.at<uchar>(i - 1, j - 1);
			y = 2*img.at<uchar>(i+1, j) + img.at<uchar>(i + 1, j - 1) + img.at<uchar>(i + 1, j + 1) - 2*img.at<uchar>(i-1, j) - img.at<uchar>(i - 1, j + 1) - img.at<uchar>(i - 1, j - 1);
			t = sqrt(x*x + y*y);
			if (t>255) t = 255;
			img1.at<uchar>(i, j) = t;
		}
	}
	
	return img1;
}

Mat dilutebw(Mat img)
{
	Mat img1(img.size(), CV_8UC1);
	int i, j,k,l, a[2], b;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			for (k = i - 1; k < i + 2; k++)
			{
				for (l = j - 1; l < l + 2; l++)
					a[(img.at<uchar>(k, l) / 255)]++;
			}
			if (a[0]>a[1])
				img1.at<uchar>(i, j) = 0;
			else img1.at<uchar>(i, j) = 1;
		}
	}
	return img1;
}

Mat erosionbw(Mat img)
{
	Mat img1(img.size(), CV_8UC1);
	int i, j, k, l, a[2], b;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			for (k = i - 1; k < i + 2; k++)
			{
				for (l = j - 1; l < l + 2; l++)
					a[(img.at<uchar>(k, l) / 255)]++;
			}
			if (a[0]>a[1])
				img1.at<uchar>(i, j) = 1;
			else img1.at<uchar>(i, j) = 0;
		}
	}
	return img1;
}

Mat noisered_gs_avg(Mat img)
{
	int i, j, k, l, m;
	Mat img1(img.size(), CV_8UC1);
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			m = 0;
			for (k = i - 1; k < i + 2; k++)
			{
				for (l = j - 1; l < l + 2; l++)
				{
					m = m + img.at<uchar>(k, l);
				}
			}
			img1.at<uchar>(i, j) = m / 9;
		}
	}
	return img1;
}


Mat noisered_gs_median(Mat img)
{
	int i, j, k, l, p, a, b, *m, x;

	Mat img1(img.size(), CV_8UC1);
	cout << "enter size of kernel for median";
	cin >> p;
	m = (int*)malloc(p*p*sizeof(int));
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			for (a = 0; a < p*p; a++)
				m[a] = 0;
			for (k = i - p; k <= i + p; k++)
			{
				for (l = j - p; l <= l + p; l++)
				{
					for (a = 0; a < p*p; a++)
						m[a] = img.at<uchar>(k, l);
				}
			}
			for (a = 0; a < p*p - 1; a++)
			for (b = a; b < p*p - 1; b++)
			if (m[b + 1]>m[b])
			{
				x = m[b + 1]; m[b + 1] = m[b]; m[b] = x;
			}
			x = m[((int)(p*p) / 2) + 1];
			img1.at<uchar>(i, j) = x;
		}
	}
	return img1;
}



int main()
{
	Mat img;
	int m = 50, n = 50;
	char a;
	img = imread("c:\\ronaldo.jpg", 0);
	Mat img1(img.size(), CV_8UC1);
	namedWindow("window1", WINDOW_AUTOSIZE);
	createTrackbar("max", "window1", &m, 255);
	createTrackbar("min", "window1", &n, 255);
	while (1)
	{
		Canny(img, img1, m, n, 3);
		namedWindow("window1", WINDOW_AUTOSIZE);
		imshow("window1", img1);
		a = waitKey(20);
		if (a ==27) 
			break;
	}
	return 0;
}