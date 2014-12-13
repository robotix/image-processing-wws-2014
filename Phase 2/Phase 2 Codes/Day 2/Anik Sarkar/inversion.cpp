#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


using namespace cv;
using namespace std;


int main()
{
	Mat image = imread("C:\\Users\\Subham Bhatter\\Downloads\\mast-sherlock-s3-mini-episode-hires.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copy = image;
	namedWindow("Grayscale", WINDOW_NORMAL);
	imshow("Grayscale", copy);
	waitKey(10);

	Mat black(image.rows, image.cols, CV_8UC3);
	int x, y;
	for (x = 0; x < image.rows; x++)
	{
		for (y = 0; y < image.cols; y++)
		{
			black.at<Vec3b>(image.rows - x-1, y)[0] = image.at<Vec3b>(x, y)[0];
			black.at<Vec3b>(image.rows - x-1, y)[1] = image.at<Vec3b>(x, y)[1];
			black.at<Vec3b>(image.rows - x-1, y)[2] = image.at<Vec3b>(x, y)[2];

		}
	}

	imshow("Grayscale", black);
	waitKey(0);

}