// Sample_Project8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

Mat con2bw(Mat image, int threshold){
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i,j) > threshold)
				image2.at<uchar>(i, j) = 255;
		}
	}
	return image2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\pic.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int x = 50;
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "My Window", &x, 255);
	while (1)
	{
		Mat bin = con2bw(input, x);
		imshow("My Window", bin);
		char a = waitKey(33);
		if (a == 27)break;
	}
	return 0;
}