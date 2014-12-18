#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

Mat linedetect(Mat img)
{
	int i, j, cnt = 0, a1, b1;
	Mat img1(img.size(), CV_8UC1, Scalar(0));
	float slope;

	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			if (img.at<uchar>(i, j) != 0 && img1.at<uchar>(i, j) != 255)
			{
				for (a1 = 1; a1 < img.rows - 1; a1++)
				{
					for (b1 = 1; b1 < img.cols - 1; b1++)
					{
						if (img.at<uchar>(i, j) == img.at<uchar>(a1, b1))
						{
							cnt++;
							slope = (float)(i - a1) / (float)(j - b1);
						}
					}
				}if (cnt>100)
					{
						for (a1 = 1; a1 < img.rows - 1; a1++)
						{
							for (b1 = 1; b1 < img.cols - 1; b1++)
							{
								if ((img.at<uchar>(i, j) == img.at<uchar>(a1, b1)) && ((((float)(j - b1) / (float)(i - a1)) - slope) <= 0.01))
									img1.at<uchar>(a1, b1) = 255;
							}
						}
					}
				}
			}
		}
		return img1;
	}

								


	int main()
 {
	Mat img;
	img = imread("c:\\chess1.jpg", 0);
	Mat img1(img.size(), CV_8UC1);
	img1 = linedetect(img);
	namedWindow("window1", WINDOW_AUTOSIZE);
	imshow("window1", img1);
	waitKey(0);
	return 0;

}