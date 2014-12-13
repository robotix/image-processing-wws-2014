#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


using namespace cv;
using namespace std;

int main()
{
	int i, j;
	Mat REDIM(150, 250, CV_8UC3, Scalar(255,255,255));
	for (j = 0; j<50; j++)
	{
		for (i = 0; i<250; i++)
		{
			REDIM.at<Vec3b>(j,i)[0] = 0;
			REDIM.at<Vec3b>(j,i)[1] = 165;
			REDIM.at<Vec3b>(j,i)[2] = 255;
		}
	}
	for (j = 100; j <150; j++)
	{
		for (i = 0; i <250; i++)
		{
			REDIM.at<Vec3b>(j,i)[0] = 0;
			REDIM.at<Vec3b>(j,i)[1] = 255;
			REDIM.at<Vec3b>(j,i)[2] = 0;



		}
	}
	namedWindow("Display ", WINDOW_NORMAL);
	imshow("Display", REDIM);
	waitKey(0);
	return 0;
}