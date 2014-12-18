#include "stdafx.h"
#include<iostream>
#include<math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
#define  rmax (int)(2*sqrt(pow(img.rows,2)+pow(img.cols,2))+2)
#define PI 3.14159265

void main()
{
	int i, j,k,l,r,w=250;
	double angle;
	Mat img = imread("lines.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("window1", WINDOW_NORMAL);
	imshow("window1", img);
	waitKey(0);
	Mat acc(rmax, 180, CV_8UC1, Scalar(0));
	namedWindow("window2", WINDOW_NORMAL);
	createTrackbar("Min brightness detected", "window2", &w, 255);
	while (1)
	{
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				if (img.at<uchar>(i, j) > w)
				{
				for (l = 0; l < 180; l++)
				{   
					angle = (PI*l) / 180;
					r = (int)(j*cos(angle) + i*sin(angle));
                    acc.at<uchar>(rmax/2 +r, l)++;
						}
				}
			}
		}
		Point p;
		int max = 0;
		for (k = 0; k < rmax; k++)
		{
			for (l = 0; l < 180; l++)
			{
				max = (acc.at<uchar>(k, l)>max) ? acc.at<uchar>(k, l) : max;
				p.x = l;
				p.y = k;
			}
		}
		Mat out(rmax, 180, CV_8UC1, Scalar(0));
		for (i = 0; i<out.rows; i++)
		{
			for (j = 0; j<out.cols; j++)
			{
				if (acc.at<uchar>(i,j)!= 0)
				{
					out.at<uchar>(i, j) = (int)(acc.at<uchar>(i, j) * 255 / max);
				}
			}
		}
		
		Mat image(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (i = 0; i < img.rows; i++)
		{
			angle = (PI*p.x) / 180;
			if (angle != 90)
			{
				j = (p.y - i*sin(angle)) / cos(angle);
				image.at<uchar>(i, j) = 255;
			}
			else
				image.at<uchar>(p.y, i) = 255;
		}


		imshow("window2", image);
		imshow("window3", out);
		int a = waitKey(33);
			if (a == 27)
			break;

	}
}