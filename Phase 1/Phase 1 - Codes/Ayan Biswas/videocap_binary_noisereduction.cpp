#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;



int main()
{
	VideoCapture vid(0);
	int thres=0;
	namedWindow("Output", CV_WND_PROP_FULLSCREEN);
	cvCreateTrackbar("Threshold", "Output", &thres, 255);
	while (1)
	{
		Mat image;
		vid.read(image);
		Mat grey(image.rows, image.cols, CV_8UC1);
		Mat binary(image.rows, image.cols, CV_8UC1);
		int i, j;
		int b, g, r;
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
		
		
			for (i = 0; i < image.rows; ++i)
			{
				for (j = 0; j < image.cols; ++j)
				{
					if (grey.at<uchar>(i, j)>thres)
						binary.at<uchar>(i, j) = 255;
					else
						binary.at<uchar>(i, j) = 0;
				}
			}
			Mat noiseless(image.rows, image.cols, CV_8UC1);
			for (i = 0; i < image.rows; ++i)
			{
				for (j = 0; j < image.cols; ++j)
				{
					int k, l, black = 0, white = 0;
					for (k = i - 1; k <= i + 1; ++k)
					{
						for (l = j - 1; l <= j + 1; ++l)
						{
							if (k >= 0 && k < image.rows && l >= 0 && l < image.cols)
							{
								if (binary.at<uchar>(k, l) == 0)
									black++;
								else
									white++;
							}
						}
					}
					if (white>black)
						noiseless.at<uchar>(i, j) = 255;
					else
						noiseless.at<uchar>(i, j) = 0;
				}
			}
			imshow("Output", noiseless);
			int ikey = waitKey(30);
			if (ikey == 27)
				break;
	}
	waitKey(0);
	return 0;
}