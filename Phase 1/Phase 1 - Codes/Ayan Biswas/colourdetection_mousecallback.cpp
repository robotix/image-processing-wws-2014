#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
#define MAX_KERNEL_LENGTH 10
int Mx=0, My=0;

void mouse_callback(int event, int x, int y, int, void*)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		Mx = x;
		My = y;
	}
}

int main()
{
	Mat image = imread("G:\\colourful2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat imageHSV(image.rows, image.cols, CV_8UC3);
	Mat colordetect(image.rows, image.cols, CV_8UC1);
	int i, j;
	int h, s, v, h1, s1, v1;
	cvtColor(image, imageHSV, CV_BGR2HSV);
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	namedWindow("Color", CV_WINDOW_AUTOSIZE);
	int Hthres, Sthres, Vthres;
	setMouseCallback("Input", mouse_callback, NULL);
	createTrackbar("Hue Thres", "Color", &Hthres, 15);
	createTrackbar("Sat Thres", "Color", &Sthres, 70);
   createTrackbar("Val Thres", "Color", &Vthres, 200);
	while (1)
	{
		
		imshow("Input", image);
		h = imageHSV.at<Vec3b>(My, Mx)[0];
		s = imageHSV.at<Vec3b>(My, Mx)[1];
          v = imageHSV.at<Vec3b>(My, Mx)[2];
		for (i = 0; i < image.rows; ++i)
		{
			for (j = 0; j < image.cols; ++j)
			{
				h1 = imageHSV.at<Vec3b>(i, j)[0];
				s1 = imageHSV.at<Vec3b>(i, j)[1];
                        v1 = imageHSV.at<Vec3b>(i, j)[2];
				if (h1<=(h + Hthres) && h1>=(h - Hthres) && s1<=(s + Sthres) && s1>=(s - Sthres) && v1<=(v+Vthres) && v1>=(v-Vthres))
					colordetect.at<uchar>(i, j) = 255;
				else
					colordetect.at<uchar>(i, j) = 0;
			}
		}
		imshow("Color", colordetect);
		if (waitKey(30) == 27)
			break;
	}
	waitKey(0);
	return 0;
}