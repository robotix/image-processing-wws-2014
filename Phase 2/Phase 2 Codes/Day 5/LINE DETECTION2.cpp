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
	Mat image = imread("G:\\abc.png", CV_LOAD_IMAGE_GRAYSCALE);
	int i, j;
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(0));
	int l, n;
	int a = (int)sqrt(image.rows*image.rows + image.cols*image.cols);
	Mat hough(a, 180 * 3, CV_8UC1, Scalar(0));
	int t = 20;
	namedWindow("detected lines", WINDOW_NORMAL);
	createTrackbar("Threshold", "detected lines", &t, 255);
	int ang;
	int r;
	int x, y;
	double m, c;
	imshow("image", image);
	waitKey(0);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) == 255)
			{

				for (ang = 0; ang <= 180; ang++)
				{
					r = (int)abs(j*cos(ang*CV_PI / 180) + i*sin(ang*CV_PI / 180));
					hough.at<uchar>(r, ang) = hough.at<uchar>(r, ang) + 2;
				}
			}


		}
	}
	int sum=0;
	while (1)
	{
		for (ang = 2; ang <= 180 - 2; ang++)
		{
			for (i = 2; i < a - 2; i++)
			{
				for (x = ang - 2; x <= ang + 2; x++)
				{
					for (y = i - 2; y <= i + 2; y++)
					{
						sum = sum + hough.at<uchar>(y, x);

					}
				}
				sum = (int)(sum / 25);
				if ((int)(hough.at<uchar>(i, ang) - sum) > t)
				{
					c = ((r / cos(ang*CV_PI / 180)));
					m = tan(ang*CV_PI / 180);
					for (l = 0; l < image.cols; l++)
					{
						n =(int) (r - l*cos(ang*CV_PI / 180)) / sin(ang*CV_PI / 180);
						if (n >= 0 && n < image.rows)
						{

							img.at<uchar>(n, l) = 255;
						}
					}

				}
			}
		}
		int k = waitKey(33);
		if (k== 27){
			break;
		}
		imshow("detected lines", img);
		waitKey(0);
	}
	return 0;
}