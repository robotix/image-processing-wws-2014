#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


using namespace cv;
using namespace std;
Mat gryscale(Mat);


int main()
{
	Mat image = imread("C:\\Users\\Subham Bhatter\\Downloads\\mast-sherlock-s3-mini-episode-hires.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copy = image;
	namedWindow("Grayscale", WINDOW_NORMAL);
	imshow("Grayscale", copy);
	waitKey(10);
	imshow("Grayscale", gryscale(image));
	waitKey(10);
	
	Mat black(image.rows, image.cols, CV_8UC1, Scalar(255));
	int x, y;
	for (x = 0; x < image.rows; x++)
	{
		for (y = 0; y < image.cols; y++)
		{
			if ((uchar)(0.11*image.at<Vec3b>(x, y)[2] + 0.33*image.at<Vec3b>(x, y)[1] + 0.56*image.at<Vec3b>(x, y)[0]) < 100)
			{
				black.at<uchar>(x, y) = 0;
			}
		}
	}

	imshow("Grayscale", black);
	waitKey(0);

}
Mat gryscale(Mat xyz)
{
	int i, j;
Mat REDIM(xyz.rows, xyz.cols, CV_8UC1);
	for (i = 0; i < xyz.rows; i++)
	{
		for (j = 0; j < xyz.cols; j++)
		{
			REDIM.at<uchar>(i, j) =(uchar)( 0.11*xyz.at<Vec3b>(i, j)[2] + 0.33*xyz.at<Vec3b>(i, j)[1] + 0.56*xyz.at<Vec3b>(i, j)[0] );


		}
	}
	namedWindow("Grayscale", WINDOW_NORMAL);
	return(REDIM);
}