#include"stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
/*int main()
{
	Mat image = imread("C:\\Users\\PRIYANK YADAV\\visual photos\\11.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	char win[] = "window";
	Mat image1(image.rows, image.cols, CV_8UC1);
	int k, l, m = 0, n;

	for (int i = 0; i < image.rows; i++)
	{

		for (int j = 0; j < image.cols; j++)
		{
			m = 0; n = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				if (k >= 0 && k < image.rows)
				{
					for (l = j - 1; l <= j + 1; l++)

					{
						if (l >= 0 && l < image.cols)
						{
							if ((k != i && l == j) || (k == i && l != j))
							{
								++n;
								m += image.at<uchar>(k, l);
							}

						}
					}
				}
			}
			if ((image.at<uchar>(i, j)) < m / n)
				image1.at<uchar>(i, j) = 0;
			else
				image1.at<uchar>(i, j) = 255;

		}


	}

	Mat image2(image1.rows, image1.cols, CV_8UC1);

	for (int i = 0; i < image1.rows; i++)
	{

		for (int j = 0; j < image1.cols; j++)
		{
			m = 0; n = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				if (k >= 0 && k < image.rows)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						if (l >= 0 && l < image.cols)
						{
							if (image1.at<uchar>(i, j) == 0)
								m++;
							else n++;

						}
					}
				}
			}
			if (m>n)
				image2.at<uchar>(i, j) = 0;
			else image2.at<uchar>(i, j) = 255;
		}

	}
	Mat image3(image2.rows, image2.cols, CV_8UC1);

	for (int i = 0; i < image2.rows; i++)
	{

		for (int j = 0; j < image2.cols; j++)
		{
			m = 0; n = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				if (k >= 0 && k < image.rows)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						if (l >= 0 && l < image.cols)
						{
							if (image2.at<uchar>(i, j) == 0)
								m++;
							else n++;

						}
					}
				}
			}
			if (m>n)
				image3.at<uchar>(i, j) = 255;
			else image3.at<uchar>(i, j) = 0;
		}

	}

	namedWindow("final1", CV_WINDOW_AUTOSIZE);
	namedWindow("original", CV_WINDOW_AUTOSIZE);
	namedWindow("final2", CV_WINDOW_AUTOSIZE);
	imshow("original", image1);
	imshow("final1", image2);
	imshow("final2", image3);
	waitKey(0);
	return 0;
}*/