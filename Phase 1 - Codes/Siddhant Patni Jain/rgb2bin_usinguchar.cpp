#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image;
	image = imread("F:\picture001.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image1 (image.rows,image.cols,CV_8UC1,Scalar (0,10,20));
	char win[] = "Black and White"; 
	int t = 382;
	for (int i = 0; i<image.rows; i++)
	{
		for (int j = 0; j<image.cols; j++)
		{
			
			if ((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2])>t)
			{
				image1.at<uchar>(i, j)= 255;
			}

			else
			{
				image1.at<uchar>(i, j)= 0;
				

			}
		}
	}
	namedWindow(win,WINDOW_AUTOSIZE);
	imshow(win, image1);
	waitKey(0);
	return 0;
}
