// Sample_Project13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>


using namespace std;
using namespace cv;

float G[3][3] = { { 0.06, 0.098, 0.06 }, { 0.098, 0.162, 0.098 }, { 0.06, 0.098, 0.06 } };

Mat blurAVG(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			int count = 0;
			long unsigned n = 0;
			for (int k = -1; k<= 1 ; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (((i + k) >= 0) && ((j + l) >= 0) && ((i + k) < input.rows) && ((j + l) <input.cols))
					{
						n += input.at<uchar>(i + k, j + l); count++;
					}
				}
			}
			output.at<uchar>(i, j) = n/count;
		}
	}
	return output;
}

Mat blurGauss(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			output.at<uchar>(i, j) = 0;
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (((i + k) >= 0) && ((j + l) >= 0) && ((i + k) < input.rows) && ((j + l) <input.cols))
					{
						output.at<uchar>(i, j) += G[1 + k][1 + l] * input.at<uchar>(i + k, j + l);
					}
				}
			}
		}
	}
	return output;
}

Mat blurMedian(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	input.copyTo(output);
	for (int i = 1; i < input.rows-1; i++)
	{
		for (int j = 1; j < input.cols-1; j++)
		{
			uchar data[9];
			int count = 0;
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
						data[count++] = input.at<uchar>(i + k, j + l);
				}
			}
			int i1, j1, max, maxidx;
			for (i1 = 8; i1>0; i1--){
				maxidx = 0;
				max = data[maxidx];
				for (j1 = 1; j1 <= i1; j1++){
					if (data[j1]>max){
						maxidx = j1; max = data[j1];
					}
				}
				data[maxidx] = data[i1];
				data[i1] = max;
			}
			output.at<uchar>(i, j) = data[4];
		}
	}
	return output;

}

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\edge1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat AVG_Blur_Img = blurAVG(input);
	Mat Gauss_Blur_Img = blurGauss(input);
	Mat Median_Blur_Img = blurMedian(input);
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Avaraged Blurred Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Gaussian Blurred Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Median Blurred Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", input);
	imshow("Avaraged Blurred Image", AVG_Blur_Img);
	imshow("Gaussian Blurred Image", Gauss_Blur_Img);
	imshow("Median Blurred Image", Median_Blur_Img);
	waitKey(0);
	return 0;
}