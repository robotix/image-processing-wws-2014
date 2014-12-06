// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<vector>
using namespace std;
using namespace cv;

int main()
{
	Mat image(200,300,CV_8UC3);
	namedWindow("My window", CV_WINDOW_AUTOSIZE);
	int i, j;
	for (i = 0; i < 200; i++)
	{
		for (j = 0; j < 300; j++)
		{
			if (i < 67)
			{
				image.at<Vec3b>(i, j)[0] = 0;
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[2] = 255;
			}
			if (i >= 67 && i < 134)
			{

				image.at<Vec3b>(i, j)[0] = 255;
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[2] = 255;
			}
			if (i>=134&&i<200)
			{

				image.at<Vec3b>(i, j)[0] = 0;
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[2] = 0;
			}

		}
	}
	imshow("My window", image);
	waitKey(0);
}

