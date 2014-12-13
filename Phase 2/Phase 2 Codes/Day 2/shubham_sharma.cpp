Histogram:
#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;

 int main()
{
	int i, j,k,a[300];
	Mat image;
	image = imread("C:\\a1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat gimage(image.rows, image.cols, CV_8UC1);
	
	for (j = 0; j < 256; j++)
		a[j] = 0;
	for (j = 0; j < image.rows; j++)
	{
		for (k = 0; k < image.cols; k++)
		{
			gimage.at<uchar>(j, k) = (uchar)(0.56*image.at<Vec3b>(j, k)[0] + 0.33*image.at<Vec3b>(j, k)[1] + 0.11*image.at<Vec3b>(j, k)[2]);
		}
	}
	Mat hist(image.rows, image.cols, CV_LOAD_IMAGE_GRAYSCALE,Scalar(255));
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j<image.rows; j++)
		{
			for (k = 0; k < image.cols; k++)
			{
				if ((int)gimage.at<uchar>(j, k) == i)
				{
					a[i] += a[i];
				}

			}

		}
	}

	for (j = 0; j < image.cols; j++)
	{
		for (i = (image.rows - 1); i >= 0; i--)
		{
			hist.at<uchar>(i, j) = (uchar)0;
		}
	}

	namedWindow("window1", WINDOW_AUTOSIZE);
	imshow("window1", image);
	namedWindow("window2", WINDOW_AUTOSIZE);
	imshow("window1", gimage);
	namedWindow("window3", WINDOW_AUTOSIZE);
	imshow("window1", hist);

	waitKey(0);

	return 0;
} 

Trackbar:
#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


using namespace cv;
using namespace std;
Mat makebinary(Mat,int);


int main()
{
	Mat image = imread("C:\\Users\\Subham Bhatter\\Downloads\\mast-sherlock-s3-mini-episode-hires.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copy = image;
	int t = 10;
	namedWindow("Window1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Window1", &t, 255);
	while (1)
	{
		Mat bin = makebinary(image, t);
		imshow("Window1", bin);
		int a = waitKey(33);
		if (a == 27){
			break;
		}

	}
}
Mat makebinary(Mat xyz,int z)
{
	int i, j;
	Mat REDIM(xyz.rows, xyz.cols, CV_8UC1,Scalar(255));
	for (i = 0; i < xyz.rows; i++)
	{
		for (j = 0; j < xyz.cols; j++)
		{
			 

			if ((uchar)(0.11*xyz.at<Vec3b>(i, j)[2] + 0.33*xyz.at<Vec3b>(i, j)[1] + 0.56*xyz.at<Vec3b>(i, j)[0]) < z)
			{
				REDIM.at<uchar>(i, j) = 0;
			}
		}
	}
	return(REDIM);
}

inverted image:
#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


using namespace cv;
using namespace std;


int main()
{
	Mat image = imread("C:a1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copy = image;
	namedWindow("Grayscale", WINDOW_NORMAL);
	imshow("Grayscale", copy);
	waitKey(10);

	Mat black(image.rows, image.cols, CV_8UC3);
	int x, y;
	for (x = 0; x < image.rows; x++)
	{
		for (y = 0; y < image.cols; y++)
		{
			black.at<Vec3b>(image.rows - x-1, y)[0] = image.at<Vec3b>(x, y)[0];
			black.at<Vec3b>(image.rows - x-1, y)[1] = image.at<Vec3b>(x, y)[1];
			black.at<Vec3b>(image.rows - x-1, y)[2] = image.at<Vec3b>(x, y)[2];

		}
	}

	imshow("Grayscale", black);
	waitKey(0);

}

grayscale:
#include "stdafx.h"
#include "iostream"
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;

int main()
{
	int i, j;
	Mat image;
	image = imread("C:\\a1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat gimage(image.rows, image.cols, CV_8UC1);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
			gimage.at<uchar>(i,j) =(uchar)(0.56*image.at<Vec3b>(i,j)[0] + 0.33*image.at<Vec3b>(i,j)[1] + 0.11*image.at<Vec3b>(i,j)[2]);
	}
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", gimage);
	waitKey(0);
	return 0;
}