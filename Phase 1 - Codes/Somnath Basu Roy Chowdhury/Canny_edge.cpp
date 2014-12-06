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
	image= imread("D:\\baba.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	int i, j,k,l;
	
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	int freq[256];
	memset(freq, 0, sizeof(freq));
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			freq[(int)image.at<uchar>(i,j)]++;
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
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	imshow("Output", image);
    waitKey(0);
	return 0;
}

