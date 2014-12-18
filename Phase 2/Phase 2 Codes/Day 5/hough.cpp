

#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<queue>
#include<stdlib.h>


using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("G:\\12.png",CV_LOAD_IMAGE_GRAYSCALE);
	int i, j;
	Mat dst, cdst;
	int a = (int)sqrt(image.rows*image.rows + image.cols*image.cols);
	Mat hough(a, 180 * 3, CV_8UC1, Scalar(0));
	imshow("image", image);
	waitKey(0);
	int ang;
	int r;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) == 255)
			{

				for (ang = 0; ang <= 180; ang++)
				{
					r = (int)abs(j*cos(ang*CV_PI / 180) + i*sin(ang*CV_PI / 180));
					hough.at<uchar>(r, ang) = hough.at<uchar>(r, ang) + 1;
				}
			}


		}
	}
	namedWindow("detected lines", WINDOW_NORMAL);
	imshow("detected lines", hough);

	waitKey(0);
	return 0;
}