// Sample_Project_HSV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat dilationACP(Mat input){
	Mat output(input.rows, input.cols, input.flags, Scalar(0));
	for (int i = 2; i < input.rows - 2; i++)
	{
		for (int j = 2; j < input.cols - 2; j++)
		{
			int white = 0, black = 0;
			for (int m = -2; m <= 2; m++){
				for (int n = -2; n <= 2; n++)
				{
					if (input.at<uchar>(i + m, j + n) == 0)black++;
					else white++;
				}
			}
			if (black == 0) output.at<uchar>(i, j) = 255;
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

Mat blue(Mat input){
	cvtColor(input, input, CV_BGR2HLS_FULL);
	Mat output(input.rows, input.cols, CV_8UC1,Scalar(0));
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++){
			if ((input.at<Vec3b>(i, j)[0]>(160 - 20)) && (input.at<Vec3b>(i, j)[0]<(160 + 20))) output.at<uchar>(i, j) = 255;
		}
	}
	return output;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\hsv.jpg",CV_LOAD_IMAGE_COLOR);
	imshow("My Window", input);
	Mat output(input.rows, input.cols, CV_8UC1);
		output= blue(input);
		output = dilationACP(output);
    	imshow("HSV Window", output);
	waitKey(0);
	return 0;
}