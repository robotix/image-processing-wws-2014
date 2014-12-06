#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <vector>
using namespace std;
using namespace cv;


Mat Detect(Mat img, int min, int max)
{
	Mat final(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j;
	for (i = 0; i < img.rows; i++)
	for (j = 0; j < img.cols; j++)
	{
		Vec3b colours = img.at<Vec3b>(i, j);
		if ((colours[2] >= min) &&(colours[1] < max)&&(colours[0] < max))
		{
			final.at<uchar>(i, j) = 255;
		}
		else final.at<uchar>(i, j) = 0;
	}
	return final;
}

int main()
{
	Mat image;
	Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));

	int min=80,max=100;
	image = imread("samantha.jpg", CV_LOAD_IMAGE_COLOR);
	if (image.empty())
		exit(1);
	namedWindow("Window", CV_WINDOW_NORMAL);
	//imshow("Samantha", image);
	createTrackbar("Min_Threshold", "Window", &min, 255); 
	createTrackbar("Max_Threshold", "Window", &max, 255);
	while (1)
	{
		int a = min;
		int b = max;
		 final = Detect(image, min, max);
		imshow("Window", final);
		waitKey(33);
		
		int ikey = waitKey(33);
		if (ikey == 27)
			break;


	}
	waitKey(0);
	return 0;
}


