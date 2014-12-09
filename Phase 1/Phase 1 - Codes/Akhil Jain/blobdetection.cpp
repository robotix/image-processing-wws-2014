#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include "stdafx.h"
#include<queue>

using namespace std;
using namespace cv;

typedef struct {
	int x, y;
}point;

Mat binary(Mat image)
{
	Mat image2(image.rows, image.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if ((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3 < (60))
				image2.at<uchar>(i, j) = 0;
			else
			{
				image2.at<uchar>(i, j) = 255;
			}

		}

	}

	return image2;
}



int main()
{
	Mat image = imread("F:\\akhil001.jpg", CV_LOAD_IMAGE_COLOR);
	Mat bimage(image.rows, image.cols, CV_8UC1);
	Mat help(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat check(image.rows, image.cols, CV_8UC1, Scalar(0));
	bimage = binary(image);
	namedWindow("binary", WINDOW_AUTOSIZE);
	imshow("binary", bimage);
	int r = image.rows, c = image.cols, count = 0, a, b;
	queue<point> q;
	for (int i = 1; i < r - 1; i++)
	{
		for (int j = 1; j < c - 1; j++)
		{
			if (bimage.at<uchar>(i, j) == 0)
				help.at<uchar>(i, j) = 0;

			else
			{
				if (check.at<uchar>(i, j) == 0)
				{

					point p;
					p.x = i;
					p.y = j;
					q.push(p);
					help.at<uchar>(i, j) = count + 1;
					check.at<uchar>(i, j) = 1;
					while (!q.empty())
					{
						point pnt = q.front();
						a = pnt.x;
						b = pnt.y;
						for (int k = a - 1; k <= a + 1; k++)
						{
							for (int l = b - 1; l <= b + 1; l++)
							{
								if (bimage.at<uchar>(k, l) == 255)
								{
									if (check.at<uchar>(k, l) == 0)
									{
										point p;
										p.x = k;
										p.y = l;

										q.push(p);
										help.at<uchar>(k, l) = count + 1;
										check.at<uchar>(k, l) = 1;
									}
								}
							}
						}
						q.pop();
					}
					count++;
				}
			}
		}
	}


	cout << count << "\n";
	waitKey(0);
	return 0;
}
