#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
	Mat image;
	vector<int> arr(255);
	int sum = 0;
	int i, j, T;
	int h = 0; 
   image = imread("samantha.jpg", CV_LOAD_IMAGE_COLOR);
	if (image.empty())
		exit(1);
	Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < 255; i++) arr[i] = 0;
	for (i = 0; i < final.rows; i++)
	{
		for (j = 0; j < final.cols; j++)

		{
			T = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
			arr[T] = arr[T] + 1;
		}
	}
	for (i = 0; (i < 255); i++)
	{
		sum = sum + arr[i];
		if (sum>((final.rows)*(final.cols) / 2))
		{
			h = i;
			break;
		}
	}
	for (i = 0; i < final.rows; i++)
	{
		for (j = 0; j < final.cols; j++)
		{
			if (((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3) < h)
				final.at<uchar>(i, j) = 0;
			else final.at<uchar>(i, j) = 255;
		}
	}

	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	imshow("My Window", final);
	namedWindow("Mine", CV_WINDOW_AUTOSIZE);
	imshow("Mine", image);
	waitKey(0);
}