// Sample_Project14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

float G[3][3] = { { 0.06, 0.098, 0.06 }, { 0.098, 0.162, 0.098 }, { 0.06, 0.098, 0.06 } };

Mat con2bw(Mat image, int threshold){
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3) > threshold)
				image2.at<uchar>(i, j) = 255;
		}
	}
	return image2;
}

Mat invimgver(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			output.at<Vec3b>(i, j)[0] = input.at<Vec3b>(input.rows - i - 1, j)[0];
			output.at<Vec3b>(i, j)[1] = input.at<Vec3b>(input.rows - i - 1, j)[1];
			output.at<Vec3b>(i, j)[2] = input.at<Vec3b>(input.rows - i - 1, j)[2];
		}
	}
	return output;
}


Mat invimghor(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			output.at<Vec3b>(i, j)[0] = input.at<Vec3b>(i, input.cols - j - 1)[0];
			output.at<Vec3b>(i, j)[1] = input.at<Vec3b>(i, input.cols - j - 1)[1];
			output.at<Vec3b>(i, j)[2] = input.at<Vec3b>(i, input.cols - j - 1)[2];
		}
	}
	return output;
}

Mat edge(Mat input,int threshold){
	Mat output(input.rows, input.cols, input.flags, Scalar(255));
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
				output.at<uchar>(i, j) = 0;
			}
		}
	}
	return output;
}

Mat edgeprewit(Mat input){
	Mat output(input.rows, input.cols, input.flags, Scalar(0));
	for (int i = 1; i < input.rows - 1; i++)
	{
		for (int j = 1; j < input.cols - 1; j++)
		{
			int dx = 0, dy = 0;
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++)
				{
					dx += m*input.at<uchar>(i + m, j + n);
					dy += n*input.at<uchar>(i + m, j + n);
				}
			}
			output.at<uchar>(i, j) = (sqrt(dx*dx + dy*dy)>255) ? 255 : (sqrt(dx*dx + dy*dy));
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

Mat blurAVG(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			int count = 0;
			long unsigned n = 0;
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (((i + k) >= 0) && ((j + l) >= 0) && ((i + k) < input.rows) && ((j + l) <input.cols))
					{
						n += input.at<uchar>(i + k, j + l); count++;
					}
				}
			}
			output.at<uchar>(i, j) = n / count;
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
			output.at<uchar>(i, j) = (output.at<uchar>(i, j) / 0.794>255) ? 255 : output.at<uchar>(i, j);
		}
	}
	return output;
}

Mat blurMedian(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	input.copyTo(output);
	for (int i = 1; i < input.rows - 1; i++)
	{
		for (int j = 1; j < input.cols - 1; j++)
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
	int threshold=80;
	VideoCapture v(1);
	namedWindow("My Video", CV_WINDOW_AUTOSIZE);
	namedWindow("My Video", CV_WINDOW_AUTOSIZE);
	int lowthrsld = 30, highthrsld = 140;
	createTrackbar("LOW THRESHOLD", "My Video", &lowthrsld, 100);
	createTrackbar("HIGH THRESHOLD", "My Video", &highthrsld, 255);
	//createTrackbar("Threshold", "My Video", &threshold, 255);
	while (1)
	{
		Mat frame;
		v >> frame;
		//frame = invimghor(frame);
		Mat test;
		cvtColor(frame, test, CV_BGR2GRAY);
		Canny(frame, test, lowthrsld, highthrsld, 3);
		//imshow("Output Window", output);
		imshow("My Video", test);
		char a = waitKey(1);
		if (a == 27)break;
	}
	return 0;
}