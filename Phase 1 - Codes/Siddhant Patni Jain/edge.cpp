
#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{

	Mat image;
	image = imread("F:\picture002.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	int t = 100, i, j, max, min, k, l;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j<image.cols; j++)
		{

			if ((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2])>t)
			{
				image1.at<uchar>(i, j) = 255;
			}

			else
			{
				image1.at<uchar>(i, j) = 0;


			}
		}
	}

	for (i = 1; i < (image1.rows - 1); i++)
	{
		for (j = 1; j < (image1.cols - 1); j++)
		{
			max = 0; min = 255;
			for (k = (i - 1); k <= (i + 1); k++)
			{
				for (l = (j - 1); l <= (j + 1); l++)
				{
					if (k!= l)
					{
						if (max < image1.at<uchar>(k, l))
							max = image1.at<uchar>(k, l);
						if (min > image1.at<uchar>(k, l))
							min = image1.at<uchar>(k, l);
					}
				}
			}
			if ((max - min) > 100)
				image2.at<uchar>(i, j) = 255;
			else
				image2.at<uchar>(i, j) = 0;
		}
	}
	
	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", image);
	
	namedWindow("Binary Image1", WINDOW_AUTOSIZE);
	imshow("Binary Image1", image1);
	namedWindow("Edge Detection", WINDOW_AUTOSIZE);
	imshow("Edge Detection", image2);
	waitKey();
	return 0;
}
