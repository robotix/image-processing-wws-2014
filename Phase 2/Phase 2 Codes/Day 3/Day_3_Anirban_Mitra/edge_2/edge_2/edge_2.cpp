// edge_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
using namespace std;
using namespace cv;
Mat edge(Mat img)
{
	Mat img2(img.rows, img.cols, CV_8UC1, Scalar(0));
	int x, y;
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			x = img.at<uchar>(i + 1, j - 1) + img.at<uchar>(i + 1, j) + img.at<uchar>(i + 1, j + 1) - img.at<uchar>(i - 1, j - 1) - img.at<uchar>(i - 1, j - 1) - img.at<uchar>(i - 1, j + 1);
			y = img.at<uchar>(i - 1, j + 1) + img.at<uchar>(i, j + 1) + img.at<uchar>(i + 1, j + 1) - img.at<uchar>(i - 1, j - 1) - img.at<uchar>(i, j - 1) - img.at<uchar>(i + 1, j - 1);
			img2.at<uchar>(i, j) = sqrt(x*x+y*y);
		}
	}
	return img2;
}

int main(int argc, _TCHAR* argv[])
{
	Mat image = imread("E:\\walpapers\\VC.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat out1 = edge(image);
	Mat out2 = edge(out1);
	Mat out3 = edge(out2);
	Mat out4 = edge(out3);
	namedWindow("Edge-1", WINDOW_NORMAL);
	namedWindow("Edge-2", WINDOW_NORMAL);
	namedWindow("Edge-3", WINDOW_NORMAL);
	namedWindow("Edge-4", WINDOW_NORMAL);
	imshow("Edge-1", out1);
	imshow("Edge-2", out2);
	imshow("Edge-3", out3);
	imshow("Edge-4", out4);
	waitKey(0);
	return 0;
}


