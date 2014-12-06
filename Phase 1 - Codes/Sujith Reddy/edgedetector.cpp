#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
	Mat image;
	image = imread("samantha.jpg", CV_LOAD_IMAGE_COLOR);
	if (image.empty())
		exit(1);


	Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));

	for (int i = 0; i < final.rows; i++)
	{
		for (int j = 0; j < final.cols; j++)
		{
			final.at<uchar>(i, j) = 255;
		}
	}


	for (int i = 0; i < final.rows; i++)
	{
		for (int j = 0; j < final.cols; j++)
		{
			int max = 0, min = 255;
			int x = 0;

			for (int k = i - 1; (k < (i + 2)); k++)
			{
				for (int l = j - 1; (l < (j + 2)); l++)
				{


					if ((0 <= k) && (k <= final.rows) && (0 <= l) && (l <= final.cols))

					{
						x = (image.at<Vec3b>(k, l)[0] + image.at<Vec3b>(k, l)[1] + image.at<Vec3b>(k, l)[2])/3;
					}
					if (max < x) max = x;
					if (min>x) min = x;
				}
			}

			if ((max - min) > 125) final.at<uchar>(i, j) = 0;

		}
	}

	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
		imshow("My Window", final);

		waitKey(0);
		return 0;
	
}