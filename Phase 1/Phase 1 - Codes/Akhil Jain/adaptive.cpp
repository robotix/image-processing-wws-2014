#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image;
	image = imread("F:\akhil001.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	char win[] = "Black and White"; 
	int i, j;
	for (int i = 1; i<(image.rows - 1); i++)
	{
		for (int j = 1; j<(image.cols - 1); j++)
		{

			if (((image.at<uchar>(i - 1, j) + image.at<uchar>(i - 1, j - 1) + image.at<uchar>(i - 1, j + 1) + image.at<uchar>(i, j - 1)) + image.at<uchar>(i, j + 1) + image.at<uchar>(i + 1, j - 1) + image.at<uchar>(i + 1, j) + image.at<uchar>(i + 1, j + 1)) / 8> image.at<uchar>(i, j))
			{
				image1.at<uchar>(i, j) = 255;
			}

			else
			{
				image1.at<uchar>(i, j) = 0;


			}
		}

	}
	for (i = 0; i < image.rows; i = i + (image.rows - 1))
	{
		for (int j = 1; j < (image.cols - 1); j++)
		{
			if (((image.at<uchar>(i, j + 1) + image.at<uchar>(i, j - 1) + image.at<uchar>(i + 1, j + 1) + image.at<uchar>(i + 1, j - 1)) + image.at<uchar>(i + 1, j)) / 5 > image.at<uchar>(i, j))
			{

				image1.at<uchar>(i, j) = 255;
			}

			else
			{
				image1.at<uchar>(i, j) = 0;
			}

		}
	}
	for (j = 0; j < image.cols; j = j + (image.cols - 1))
	{
		for (int i = 1; i < (image.rows - 1); i++)
		{
			if (((image.at<uchar>(i + 1, j) + image.at<uchar>(i - 1, j) + image.at<uchar>(i + 1, j + 1) + image.at<uchar>(i - 1, j + 1)) + image.at<uchar>(i, j + 1)) / 5 > image.at<uchar>(i, j))
			{

				image1.at<uchar>(i, j) = 255;
			}

			else
			{
				image1.at<uchar>(i, j) = 0;
			}

		}
	}




	namedWindow(win, WINDOW_AUTOSIZE);
	imshow(win, image1);
	waitKey();
	return 0;
}
