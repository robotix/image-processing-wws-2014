#include "stdafx.h"
#include<iostream>
#include<math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
int X(int i, int j, Mat grey)
{
	int sum1 = 0;
	for (int a = 0; a < 3; a++)
	for (int b = -1; b < 2; b++)
		sum1 += b*grey.at<uchar>(((i + a) < grey.rows) ? (i + a) : (grey.rows - 1), ((j + b + 1) < grey.cols) ? (j + b + 1) : (grey.cols - 1));
	return sum1;
}

int Y(int i, int j, Mat grey)
{
	int sum2 = 0;
	for (int a = -1; a < 2; a++)
	for (int b = 0; b < 3; b++)
		sum2 += a*grey.at<uchar>(((i + a + 1) < grey.rows) ? (i + a + 1) : (grey.rows - 1), ((j + b) < grey.cols) ? (j + b) : (grey.cols - 1));
	return sum2;
}

Mat edgedetect(Mat grey)
{
	Mat grey1(grey.rows, grey.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < grey.rows; i++)
	{
		for (int j = 0; j < grey.cols; j++)
		{
			int v = (int)sqrt(pow(X(i, j, grey), 2) + pow(Y(i, j, grey), 2));
			grey1.at<uchar>(((i + 1) < grey1.rows) ? (i + 1) : (grey1.rows - 1), ((j + 1) < grey1.cols) ? (j + 1) : (grey1.cols - 1)) = (v < 255) ? v : 255;

		}
	}
	return grey1;
}
void main()
{
	Mat image;
	image = imread("school-building-hi.png");
	Mat img(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			img.at<uchar>(i, j) = (0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}

	Mat edge = edgedetect(img);
	imshow("WINDOW", edge);
	waitKey(0);
}