// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<stdio.h>
using namespace std;
using namespace cv;
int main()
{
	Mat image,image1;
	image = imread("D:\\ball.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int i, j,k,l,max,min,thres=100,t=382;
	
	namedWindow("Edge_detected", CV_WINDOW_AUTOSIZE);
	

		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				if (i >= 1 && j >= 1 && i < (image.rows - 1) && j < (image.cols - 1))
				{
					max = image.at<uchar>(i, j); min = max;
					for (k = i - 1; k <= i + 1; k++)
					{
						for (l = j - 1; l <= j + 1; l++)
						{
							if (image.at<uchar>(k, l)>max)
								max = image.at<uchar>(k, l);
							if (image.at<uchar>(k, l) < min)
								min = image.at<uchar>(k, l);
						}
					}
					int t = abs(max - min);
					if (t>thres)
						image.at<uchar>(i, j) = 255;
					else
						image.at<uchar>(i, j) = 0;
				}
			}
		}

		imshow("Edge_detected", image);
    waitKey(0);
	return 0;
}