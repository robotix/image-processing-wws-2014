
#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
using namespace cv;
using namespace std;
Mat binary(Mat img1,int a)
{
	
	
	
	
	
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{   
			
			if (img1.at<uchar>(i, j) < a)
				img1.at<uchar>(i, j) = 0;
			else
				img1.at<uchar>(i, j) = 255;
		}
	}
	return img1;
}

int main()
{
	int x = 155;
	Mat image;
	image = imread("C:\\city1.jpg", 0);
	Mat bin(image.size(),CV_8UC1);
	namedWindow("window_trackbar", WINDOW_NORMAL);
	createTrackbar("Threshold", "window_trackbar", &x, 255);

	while (1)
	{
		Mat bin = binary(image, x);
		imshow("window_trackbar", bin);

		char c = waitKey(33);
		if (c == 27)
			break;
	}

}