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
	image = imread("D:\\blob.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat image1(image.rows, image.cols, CV_8UC1);
	int i, j, k, l;

	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	int freq[256];
	memset(freq, 0, sizeof(freq));
	for (i = 0; i < image1.rows; i++)
	{
		for (j = 0; j < image1.cols; j++)
		{
			freq[(int)image1.at<uchar>(i, j)]++;
		}
	}
	int sum = 0, median = 0;
	for (i = 0; i < 256; i++)
	{
		sum += freq[i];
	}
	int Sum = 0;
	for (i = 0; i < 256; i++)
	{
		Sum += freq[i];
		if (Sum>sum / 2)
		{
			median = i;
			break;
		}
	}
	int lower = median / 3;
	int upper = 2 * median / 3;
	Canny(image, image1, lower, upper, 3);
	vector<vector<Point>> contour;
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	imshow("Output", image1);
	findContours(image1, contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	for (int k = 0; k < contour.size(); k++)
	{
		vector<Point> approx;
		approxPolyDP(Mat(contour[k]), approx, arcLength(contour[k], true)*0.02, true);
		//cout << approx.size()<<endl;
		if (approx.size() == 4)
			cout << "This is a rectangle"<<endl;
		else if (approx.size() == 3)
			cout << "This is a triangle" << endl;
		else if (approx.size()>=5)
			cout << "Ayan is a dumbass" << endl;
		if (waitKey(30) == 27)
			break;
	}
	
	waitKey(0);
	return 0;
}