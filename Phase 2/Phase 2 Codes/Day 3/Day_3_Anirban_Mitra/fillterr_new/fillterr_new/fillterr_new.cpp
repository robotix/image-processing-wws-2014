// fillterr_new.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;


int main(int argc, _TCHAR* argv[])
{
	Mat img = imread("E:\\walpapers\\VC.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2(img.rows, img.cols, CV_8UC1, Scalar(0));
	int temp;
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			temp = 0;
			for (int r = i - 1; r <= i + 1; r++)
			{
				for (int c = j - 1; c <= j + 1; c++)
				{
					temp = temp+img.at<uchar>(r, c);
				}
			}
			img2.at<uchar>(i, j) = temp / 9;
		}
	}
	namedWindow("Median", WINDOW_AUTOSIZE);
	imshow("Median", img2);
	waitKey(0);
	return 0;
}

