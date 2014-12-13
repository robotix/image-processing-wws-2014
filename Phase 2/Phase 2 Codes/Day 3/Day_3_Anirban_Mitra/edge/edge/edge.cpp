// edge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

Mat edge(Mat img,int n)
{
	Mat img2(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			int a[5] = { img.at<uchar>(i, j), img.at<uchar>(i, j - 1), img.at<uchar>(i, j + 1), img.at<uchar>(i - 1, j), img.at<uchar>(i + 1, j) };
			int max = a[0];
			int min = a[0];
			for (int k = 0; k < 5; k++)
			{
				if (a[k] > max)
				{
					max = a[k];
				}
				if (a[k] < min)
				{
					min = a[k];
				}
			}
			if (max - min >= n)
				img2.at<uchar>(i, j) = 255;
		}
	}
	return img2;
}


int main(int argc, _TCHAR* argv[])
{
	Mat img1 = imread("E:\\walpapers\\edge.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int n1=0;
	/*cout << "Enter threshold frequency" << endl;
	cin >> n;*/
	//namedWindow("Original", WINDOW_AUTOSIZE);
	namedWindow("New", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "New", &n1, 255);
	while (true)
	{
		
				/*for (int r = i-1; r <= i+1; r++)
				{
				for (int c = j-1; c <= j+1; c++)
				{
				if (img.at<uchar>(r, c)>max)
				{
				max = img.at<uchar>(r,c);
				}
				if (img.at<uchar>(i, j) < min)
				{
				min = img.at<uchar>(r,c);
				}

				}
				}*/
				
		//imshow("Original", img);
		Mat bin = edge(img1, n1);
		imshow("New", bin);
		int val = waitKey(33);
		if (val == 27)
			break;
	}
	return 0;
}

