#include"stdafx.h"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
/*
int main()
{
	Mat image = imread("C:\\Users\\PRIYANK YADAV\\visual photos\\11.JPG", CV_LOAD_IMAGE_COLOR);
	char win[] = "window";
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(255));
	Mat image2(image1.rows, image1.cols, CV_8UC1, Scalar(255));
	int i, j, max, min, k, l, mint = 40, maxt = 200;
	namedWindow(win, WINDOW_AUTOSIZE);
	cvCreateTrackbar("TRACHI1", win, &mint, 255);
	cvCreateTrackbar("TRACHI2", win, &maxt, 255);
	while (1)
	{
		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				if ((image.at<Vec3b>(i, j)[0] > mint) && (image.at<Vec3b>(i, j)[1] < maxt) && (image.at<Vec3b>(i, j)[2] < maxt))
					image1.at<uchar>(i, j) = 255;
				else
				{
					image1.at<uchar>(i, j) = 0;
				}
			}
		}
		for (i = 0; i < image1.rows; i++)
		{
			for (j = 0; j < image1.cols; j++)
			{
				max = 0; min = 255;
				for (k = i - 1; k <= i + 1; k++)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						if (k >= 0 && k < image1.rows  && l >= 0 && l < image1.cols)
						{
							if ((k != i && l == j) || (k == i && l != j))

							{
								if (image1.at<uchar>(k, l) > max)
									max = image1.at<uchar>(k, l);

								if (image1.at<uchar>(k, l) < min)
									min = image1.at<uchar>(k, l);

							}
						}

					}
				}
				if ((max - min) > (mint + maxt) / 2)
					image2.at<uchar>(i, j) = 0;
				else
					image2.at<uchar>(i, j) = 0;

			}

		}
		imshow(win, image1);
		int ikey = waitKey(50);
		if (ikey == 27)
			break;
	}
}*/
