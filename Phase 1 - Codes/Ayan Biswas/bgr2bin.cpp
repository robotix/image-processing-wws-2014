#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("G:\\lion.jpg", CV_LOAD_IMAGE_COLOR);
	Mat binary(image.rows, image.cols, CV_8UC1);
	int i, j, sum = 0, count = 0;
	int b, g, r;
       for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			sum += (b + g + r)/3;
			count++;
		}
	}
	int thres = sum / count;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			if (26 * b / 100 + 30 * g / 100 + 43 * r / 100>thres)
				binary.at<uchar>(i, j) = 255;
			else
				binary.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", binary);
	waitKey(0);
	return 0;
}