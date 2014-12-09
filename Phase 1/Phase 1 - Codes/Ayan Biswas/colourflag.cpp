#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image(200, 300, CV_8UC3);
	int i, j;
	for (i = 0; i < 200; ++i)
	{
		for (j = 0; j < 300; ++j)
		{
			if (i < 60)
			{
				image.at<Vec3b>(i, j)[0] = 10;
				image.at<Vec3b>(i, j)[1] = 120;
				image.at<Vec3b>(i, j)[2] = 255;
			}
			else if (i>140)
			{
				image.at<Vec3b>(i, j)[0] = 30;
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[2] = 0;
			}
			else if (((j - 155)*(j - 155) + (i - 100)*(i - 100)<1580 && (j - 155)*(j - 155) + (i - 100)*(i - 100)>1124) || (j - 155)*(j - 155) + (i - 100)*(i-100) < 50)
			{
				image.at<Vec3b>(i, j)[0] = 255;
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[2] = 0;
			}
			else
			{
				image.at<Vec3b>(i, j)[0] = 255;
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", image);
	waitKey(0);
	return 0;
}