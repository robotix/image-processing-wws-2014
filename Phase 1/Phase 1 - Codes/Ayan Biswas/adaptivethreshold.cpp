#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("G:\\blackwhite.jpg", CV_LOAD_IMAGE_COLOR);
	Mat binary(image.rows, image.cols, CV_8UC1);
	int i, j, k, l, sum, count, thres;
	int b, g, r;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			sum = 0; count = 0;
			for (k = i - 1; k <= i + 1; ++k)
			{
				for (l = j - 1; l <= j + 1; ++l)
				{
					if (k >= 0 && k < image.rows && l >= 0 && l < image.cols)
					{
						count++;
						sum += (image.at<Vec3b>(k, l)[0] + image.at<Vec3b>(k, l)[1] + image.at<Vec3b>(k, l)[2])/3;
					}
				}
			}
			thres = sum / count;
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			if ((b+g+r)/3>thres)
				binary.at<uchar>(i, j) = 255;
			else
				binary.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", binary);
	waitKey(0);

	return 0;
}