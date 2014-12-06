#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
	int i, j;
	Mat image(300, 300, CV_8UC3, Scalar(0, 0, 255));
	for (i = 0; i < 300; i++)
	{
		for (j = 0; j < 300; j++)
		{
			if (j < 100)
			{
				image.at<Vec3b>(i, j)[0] = 255;
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[2] = 0;
			}
			else
			if ((j >= 100) && (j < 200))
			{
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[0] = 0;
				image.at<Vec3b>(i, j)[2] = 0;
			}
			else
			if ((j >= 200) && (j < 300))
			{
				image.at<Vec3b>(i, j)[2] = 255;
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[0] = 0;
			}
		}
	}
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	imshow("My Window", image);
	waitKey(0);
	return 0;
}
			