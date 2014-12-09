#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include<queue>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("G:\\images\\shapes.jpg", CV_LOAD_IMAGE_COLOR);
	Mat grey(image.rows, image.cols, CV_8UC1);
	Mat binary(image.rows, image.cols, CV_8UC1);
	Mat cannyedge(image.rows, image.cols, CV_8UC1);
	int i, j;
	int b, g, r;
	//making grayscale
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			grey.at<uchar>(i, j) = (b + g + r) / 3;
		}
	}
	//histogram to make binary
	int freq[256];
	for (i = 0; i < 256; ++i)
		freq[i] = 0;
	for (i = 0; i < image.rows; ++i)
	for (j = 0; j < image.cols; ++j)
		freq[grey.at<uchar>(i, j)]++;
	int sum = 0, thres1 = 0;
	while (sum < (image.rows*image.cols) / 2)
		sum += freq[thres1++];
	int threslow = thres1 / 3;
	int threshigh = 2 * thres1 / 3;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			if (grey.at<uchar>(i, j) > thres1)
				binary.at<uchar>(i, j) = 255;
			else
				binary.at<uchar>(i, j) = 0;
		}
	}
	//find edges
	Canny(grey, cannyedge, threslow, threshigh, 3);
	//find contours
	vector<vector<Point>> contours0;
	findContours(cannyedge, contours0, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	vector<Point> approx;
	for (int k = 0; k < contours0.size(); ++k)
	{
		approxPolyDP(Mat(contours0[k]), approx, arcLength(contours0[k], true)*0.02, true);
		if (approx.size() == 3)
		{
			cout << k + 1 << "is a triangle" << endl;
			cout << approx[0].x << " " << approx[1].x << " " << approx[2].x << " " << endl;
			cout << approx[0].y << " " << approx[1].y << " " << approx[2].y << " " << endl;
			continue;
		}
		if (approx.size()>7)
		{
			cout << k + 1 << "is a circle" << endl;
			continue;
		}
		if (approx.size() == 4)
		{
			float a = sqrt((approx[0].x - approx[1].x)*(approx[0].x - approx[1].x) + (approx[0].y - approx[1].y)*(approx[0].y - approx[1].y));
			float b = sqrt((approx[1].x - approx[2].x)*(approx[1].x - approx[2].x) + (approx[1].y - approx[2].y)*(approx[1].y - approx[2].y));
			float c = sqrt((approx[2].x - approx[3].x)*(approx[2].x - approx[3].x) + (approx[2].y - approx[3].y)*(approx[2].y - approx[3].y));
			float d = sqrt((approx[0].x - approx[3].x)*(approx[0].x - approx[3].x) + (approx[0].y - approx[3].y)*(approx[0].y - approx[3].y));
			if (fabs(a - b) <= 2)
				cout << k + 1 << "is a square" << endl;
			else
				cout << k + 1 << "is a rectangle" << endl;
			cout << approx[0].x << " " << approx[1].x << " " << approx[2].x << " " << approx[3].x << endl;
			cout << approx[0].y << " " << approx[1].y << " " << approx[2].y << " " << approx[3].y << endl;
		}
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", image);
	waitKey(0);
	return 0;
}