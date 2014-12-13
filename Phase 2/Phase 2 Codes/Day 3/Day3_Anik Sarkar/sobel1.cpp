#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include<math.h>
using namespace cv;
using namespace std;


int nfunc(Mat, int, int);

int main()
{
	uchar d,e;
	int i, j;
	Mat image;
	image = imread("juncker.jpg", CV_LOAD_IMAGE_COLOR);
	Mat gimage(image.rows, image.cols, CV_8UC1);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			gimage.at<uchar>(i, j) = (uchar)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}


	Mat nimage(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < (image.rows - 1); i++)
	{
		for (j = 1; j<(image.cols - 1); j++)
		{
			d = nfunc(gimage, i, j);
			e= nfunc(gimage, i, j);

			nimage.at<uchar>(i, j) = d;
			nimage.at<uchar>(i, j) = e;


		}
	}
	namedWindow("window1", WINDOW_AUTOSIZE);
	imshow("window1", nimage);
	waitKey(0);
	return 0;
}

int nfunc(Mat gimage, int i, int j)
{
	double x, y, d, e;


	x = (gimage.at<uchar>((i - 1), (j + 1)) + gimage.at<uchar>((i), (j + 1)) + gimage.at<uchar>((i + 1), (j + 1))) - (gimage.at<uchar>((i - 1), (j - 1)) + gimage.at<uchar>((i), (j - 1)) + gimage.at<uchar>((i + 1), (j - 1)));
	y = (gimage.at<uchar>((i + 1), (j - 1)) + gimage.at<uchar>((i + 1), (j)) + gimage.at<uchar>((i + 1), (j + 1))) - (gimage.at<uchar>((i - 1), (j - 1)) + gimage.at<uchar>((i - 1), (j)) + gimage.at<uchar>((i - 1), (j + 1)));
	d = sqrt((x*x) + (y*y));
	e = fmod(x, y);
	return e;
}