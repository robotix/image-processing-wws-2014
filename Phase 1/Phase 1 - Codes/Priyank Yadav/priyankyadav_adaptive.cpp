#include"stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("C:\\Users\\PRIYANK YADAV\\visual photos\\11.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	char win[] = "window";
	Mat image1(image.rows, image.cols, CV_8UC1,Scalar(255));
	int k, l, m = 0,n;

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
				if ((image.at<uchar>(i, j)) < m/n)
					image1.at<uchar>(i, j) = 0;
				else
					image1.at<uchar>(i, j) = 255;

			}


		}
		namedWindow(win, CV_WINDOW_AUTOSIZE);
		imshow(win, image1);
		waitKey(0);
		return 0;
	}

