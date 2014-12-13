#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


using namespace cv;
using namespace std;


int main()
{
	int a[256], n, i, j;
	Mat image = imread("C:\\Users\\Subham Bhatter\\Downloads\\mast-sherlock-s3-mini-episode-hires.jpg", CV_LOAD_IMAGE_COLOR);
	int row = image.rows;
	int col = image.cols;
	n = (image.rows*image.cols) / 100;
	Mat hist(image.rows, image.cols, CV_8UC1, Scalar(255));
	int f,y, z = 0;
	int x, t, c = 0;
	f = 0;
	for (x = 0; x < 256; x++)
	{
		z = 0;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{

				if ((0.11*image.at<Vec3b>(i, j)[2] + 0.33*image.at<Vec3b>(i, j)[1] + 0.56*image.at<Vec3b>(i, j)[0]) == x)
				{
					z++;
				}
			}
		}
		a[x] = z;
		f = f + z / 100;
		if (f > n / 2 && c == 0){
			c++;
			t = x;
		}
	}
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{

				if ((0.11*image.at<Vec3b>(i, j)[2] + 0.33*image.at<Vec3b>(i, j)[1] + 0.56*image.at<Vec3b>(i, j)[0]) <=t)
				{
					hist.at<uchar>(i, j) = 0;
				}
			}
		}
		namedWindow("Histogram");
		imshow("Histogram", hist);
		waitKey(0);
}