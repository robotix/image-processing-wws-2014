#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{

	int i, j;
	Mat REDIM(150,250, CV_8UC3,Scalar(255,255,255));
	for (i = 0; i < 50; i++)
	{
		for (j = 0; j <250 ; j++)
		{
			REDIM.at<Vec3b>(i, j)[0] = 0;
			REDIM.at<Vec3b>(i, j)[1] = 165;
			REDIM.at<Vec3b>(i, j)[2] = 255;
		}
	}

	for (i = 100; i < 150; i++)
	{
		for (j = 0; j <250; j++)
		{
			REDIM.at<Vec3b>(i, j)[0] = 0;
			REDIM.at<Vec3b>(i, j)[1] = 255;
			REDIM.at<Vec3b>(i, j)[2] = 0;
		}
	}

	namedWindow("Display", WINDOW_NORMAL);
 imshow("Display", REDIM);
    waitKey(0);
	return 0;


}

