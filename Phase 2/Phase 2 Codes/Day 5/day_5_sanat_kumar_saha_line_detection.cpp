// Sample_Project _Blob_Detection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <queue>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <math.h>

using namespace std;
using namespace cv;



int _tmain(int argc, _TCHAR* argv[])
{
	int r, count = 0, max = 0, imax[50] = { 0 }, jmax[50] = { 0 },threshold,imax1,jmax1;
	cout << "Enter the value of no. of pixels that the smallest line should have=";
	cin >> threshold;
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\linedetect.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat hough(sqrt(input.rows*input.rows + input.cols*input.cols), 181, CV_8UC1, Scalar(0));
		Mat output(input.rows, input.cols, CV_8UC1, Scalar(0));
		Mat output_long(input.rows, input.cols, CV_8UC1, Scalar(0));
		Mat output_long_segment(input.rows, input.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++){
			if (input.at<uchar>(i, j) < 10){
				for (int k = 0; k < 181; k++)
				{
					r = (int)abs(j*cos((k*CV_PI) / 180) + i*sin((k*CV_PI) / 180));
				 hough.at<uchar>(r, k)++;
				}
			}
		}
	}
	for (int i = 0,m=0; i <hough.rows; i++)
	{
		for (int j = 0; j < hough.cols; j++){
			if ((int)hough.at<uchar>(i, j)>threshold){
				imax[m] = i, jmax[m] = j; m++;
			}
		}
	}
	for (int i = 0; i <hough.rows; i++)
	{
		for (int j = 0; j < hough.cols; j++){
			if ((int)hough.at<uchar>(i, j)>max){
				imax1 = i, jmax1 = j;
				max = (int)hough.at<uchar>(i, j);
			}
		}
	}
	for (int m = 0; imax[m] != 0; m++)
	{
		for (int i = 0; i < input.rows; i++)
		{
			int j = (int)((imax[m] - i*sin((jmax[m] * CV_PI) / 180)) / cos((jmax[m] * CV_PI) / 180));
			if (j>0)
			{
				output.at<uchar>(i, j) = 255;
			}
		}
	}
	for (int i = 0; i < input.rows; i++)
	{
		int j = (int)((imax1 - i*sin((jmax1 * CV_PI) / 180)) / cos((jmax1 * CV_PI) / 180));
		if (j>0)
		{
			output_long.at<uchar>(i, j) = 255;
		}
	}
	for (int i = 0; i < input.rows; i++)
	{
		int j = (int)((imax1 - i*sin((jmax1 * CV_PI) / 180)) / cos((jmax1 * CV_PI) / 180));
		if ((j>0) && input.at<uchar>(i,j)<3)
		{
			output_long_segment.at<uchar>(i, j) = 255;
		}
	}
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image",input);
	namedWindow("Hough Image",CV_WINDOW_AUTOSIZE);
	imshow("Hough Image", hough);
	namedWindow("Line Detect Image", CV_WINDOW_AUTOSIZE);
	imshow("Line Detect Image", output);
	namedWindow("Longest Line Detect", CV_WINDOW_AUTOSIZE);
	imshow("Longest Line Detect", output_long);
	namedWindow("Longest Line Segment Detect", CV_WINDOW_AUTOSIZE);
	imshow("Longest Line Segment Detect", output_long_segment);
	waitKey(0);
	return 0;
}