// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
using namespace cv;
int main()
{
	Mat image;
	image = imread("D:\\baba.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat image2(image.rows, image.cols, CV_8UC3);
	int i, j, k, l;

	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	
	int freq[256];
	memset(freq, 0, sizeof(freq));
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			freq[(int)image.at<uchar>(i, j)]++;
		}
	}
	int a[256]; int min;
	memset(a, 0, sizeof(a));
	for (i = 0; i < 256; i++)
	{
		min = freq[i];
		for (j = 0; j < 256; j++)
		{
			if (a[j] == 0)
				a[j] = j;
			if (freq[j] < min)
			{
				int t = min;
				min = freq[j];
				freq[j] = t;
				a[j] = i;
				a[i] = j;
			}


		}
	}
	int lower = a[127] / 3;
	int upper = 2 * a[127] / 3;
	Canny(image, image, lower, upper, 3);
	/*for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);

		}
	}*/
	int thres=100;
	vector<Vec2f> lines;
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	createTrackbar("Track", "Output", &thres, sqrt(image.rows*image.rows+image.cols*image.cols));
	imshow("Input", image);
	while (1)
	{
		HoughLines(image, lines, 1, CV_PI / 180, thres);
		for (i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(image2, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
		}
		imshow("Output", image2);
		if (waitKey(30) == 27)
			break;
	}
	waitKey(0);
	return 0;
}