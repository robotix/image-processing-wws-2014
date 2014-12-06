
#include "stdio.h"
#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
/*
using namespace cv;
using namespace std;

int main()
{
	int t;
    char win[] = "my video";
	namedWindow(win, CV_WINDOW_AUTOSIZE);
	VideoCapture Vid("C:\\Users\\PRIYANK YADAV\\Videos\\eye.mp4");
	
	while (1)
	{
		Mat image;
		Vid.read(image);
		Mat image1(image.rows, image.cols, CV_8UC1);
		

		for (int i = 0; i < image.rows; i++)
		{

			for (int j = 0; j < image.cols; j++)
			{
				image1.at<uchar>(i, j) = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
			}
		}
		Mat image2(image1.rows, image1.cols, CV_8UC1);
		cvCreateTrackbar("TRACHI", win, &t, 255);
		while (1)
		{	

			for (int i = 0; i < image1.rows; i++)
			{
				for (int j = 0; j < image1.cols; j++)
				{
					if (image1.at<uchar>(i, j) > t) 
						image2.at<uchar>(i, j) = 255;
					else
						image2.at<uchar>(i, j) =0;
				}
			}	
			int a = waitKey(50);
			if (a == 27)
				break;
		}
		imshow(win, image2);
		int a = waitKey(50);
		if (a == 27)
			break;
		}

	waitKey(0);
	return(0);
}*/