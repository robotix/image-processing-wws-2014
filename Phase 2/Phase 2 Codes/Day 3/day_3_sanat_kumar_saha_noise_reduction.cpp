// Sample_Project12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

Mat edge(Mat input, int threshold){
	Mat output(input.rows, input.cols, input.flags, Scalar(0));
	for (int i = 1; i < input.rows - 1; i++)
	{
		for (int j = 1; j < input.cols - 1; j++)
		{
			int min, max;
			max = min = input.at<uchar>(i, j);
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++)
				{
					max = (max > input.at<uchar>(i + m, j + n)) ? max : input.at<uchar>(i + m, j + n);
					min = (min < input.at<uchar>(i + m, j + n)) ? min : input.at<uchar>(i + m, j + n);
				}
			}
			if ((max - min)>threshold)
			{
				output.at<uchar>(i, j) = 255;
			}
		}
	}
	return output;
}

Mat dilationACP(Mat input){
	Mat output(input.rows, input.cols, input.flags, Scalar(0));
	for (int i = 1; i < input.rows - 1; i++)
	{
		for (int j = 1; j < input.cols - 1; j++)
		{
			int white=0, black=0;
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++)
				{
					if (input.at<uchar>(i + m, j + n) == 0)black++;
					else white++;
				}
			}
			if (black==0) output.at<uchar>(i, j) = 255;
			else if (white == 0) output.at<uchar>(i, j) = 0;
			else if (white<black) output.at<uchar>(i, j) = 0;
			else output.at<uchar>(i, j) = 255;
		}
	}
	return output;
}

Mat erosionACP(Mat input){
	Mat output(input.rows, input.cols, input.flags, Scalar(0));
	for (int i = 1; i < input.rows - 1; i++)
	{
		for (int j = 1; j < input.cols - 1; j++)
		{
			int white = 0, black = 0;
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++)
				{
					if (input.at<uchar>(i + m, j + n) == 0)black++;
					else white++;
				}
			}
			if (black == 0) output.at<uchar>(i, j) = 255;
			else if (white == 0) output.at<uchar>(i, j) = 0;
			else if (white<black) output.at<uchar>(i, j) = 255;
			else output.at<uchar>(i, j) = 0;
		}
	}
	return output;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int threshold;
	cout << "Enter the value of Threshold=";
	cin >> threshold;
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\edge1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat output_edge = edge(input, threshold);
	Mat output_dilation = dilationACP(output_edge);
	Mat output_erosion = erosionACP(output_dilation);
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Edge", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Dilation", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Erosion", CV_WINDOW_AUTOSIZE);
	imshow("Input", input);
	imshow("Output Edge", output_edge);
	imshow("Output Dilation", output_dilation);
	imshow("Output Erosion", output_erosion);
	waitKey(0);
	return 0;
}