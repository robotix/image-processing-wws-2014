// gausian_filter.cpp : Defines the entry point for the console application.
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
	//float a[3][3] = { { 0.06, 0.098, 0.06 }, { 0.098, 0.162, 0.098 }, { 0.06, 0.098, 0.06 } };
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			temp = img.at<uchar>(i - 1, j - 1)*.06 + img.at<uchar>(i - 1, j)*0.098 + img.at<uchar>(i - 1, j + 1)*0.06 + img.at<uchar>(i, j - 1)*0.098 + img.at<uchar>(i, j)*0.162 + img.at<uchar>(i, j + 1)*0.098 + img.at<uchar>(i + 1, j - 1)*0.06 + img.at<uchar>(i + 1, j)*0.098 + img.at<uchar>(i + 1, j + 1)*0.06;
			/*int m = 0; int n = 0;
			for (int r = i - 1; r <= i + 1; r++)
			{
				for (int c = j - 1; c <= j + 1; c++)
				{
					temp += a[m][n] * img.at<uchar>(r, c);
					n++;
				}
				m++;
				n = 0;
			}*/
			img2.at<uchar>(i, j) = temp;
		}
	}
	namedWindow("Gausian", WINDOW_AUTOSIZE);
	imshow("Gausian", img2);
	waitKey(0);
	return 0;
}

