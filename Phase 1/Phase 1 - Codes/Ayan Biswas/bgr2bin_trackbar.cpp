#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;



int main()
{
	Mat image = imread("G:\\lion.jpg", CV_LOAD_IMAGE_COLOR);
	Mat grey(image.rows, image.cols, CV_8UC1);
	Mat binary(image.rows, image.cols, CV_8UC1);
	int i, j, thres;
	int b, g, r;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			grey.at<uchar>(i, j) = (b + g + r) / 3;
		}
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	namedWindow("Grey", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	imshow("Grey", grey);
	namedWindow("Binary", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Threshold", "Binary", &thres, 255);
	while (1)
	{
		for (i = 0; i < image.rows; ++i)
		{
			for (j = 0; j < image.cols; ++j)
			{
				if (grey.at<uchar>(i, j)>thres)
					binary.at<uchar>(i, j) = 255;
				else
					binary.at<uchar>(i, j) = 0;
			}
		}
		imshow("Binary", binary);
		int ikey = waitKey(50);
		if (ikey == 27)
			break;
	}
	waitKey(0);
	return 0;
}
