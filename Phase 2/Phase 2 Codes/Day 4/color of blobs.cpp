#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<queue>
#include<stdlib.h>


using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("G:\\12345.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat xyz = imread("G:\\12345.png", CV_LOAD_IMAGE_COLOR);
	imshow("color", xyz);
	waitKey(0);
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(0));
	int **a;
	int i, j, l, z;
	int b;
	int t = 0;
	int c;
	l = 0;
	z = 0;
	int col, blue, white, green, red;
	col = blue = white = green = red = 0;
	a = new int*[(int)image.cols* sizeof(int *)];
	for (i = 0; i < image.cols; i++)
		a[i] = new int[(int)image.rows* sizeof(int)];

	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			a[j][i] = -1;
		}
	}
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j)>0)
			{
				image.at<uchar>(i, j) = 0;
			}
			else
			{

				image.at<uchar>(i, j) = 255;
			}
		}
	}
	Mat copy = image;
	int num[100];
	imshow("Image", image);
	waitKey(0);
	for (i = 0; i < copy.rows; i++)
	{
		for (j = 0; j < copy.cols; j++)
		{
			queue<Point> q;
			if (copy.at<uchar>(i, j) == 0 && a[j][i] == -1)
			{
				Point front1;
				Point rear;
				front1.x = j;
				front1.y = i;
				q.push(front1);
				l++;
				a[j][i] = l;
				num[t++] = l;
				while (1)
				{
					for (b = front1.y - 1; b <= front1.y + 1; b++)
					{
						for (c = front1.x - 1; c <= front1.x + 1; c++)
						{
							if (copy.at<uchar>(b, c) == 0 && a[c][b] == -1)
							{
								rear.x = c;
								rear.y = b;
								a[c][b] = l;
								q.push(rear);
								z++;
							}
						}
					}
					q.pop();

					if (q.empty() == true)
					{
						break;
					}
					front1 = q.front();
				}


			}
		}
	}
	t = t - 1;
	int r = 0;
	for (i = 0; i < copy.rows; i++)
	{
		for (j = 0; j < copy.cols; j++)
		{
			if (a[j][i] != -1)
			{
				
					if (r<=t&&a[j][i] == num[r])
					{
						r++;
						if (xyz.at<Vec3b>(i, j)[0] == 255 && xyz.at<Vec3b>(i, j)[1] == 0 && xyz.at<Vec3b>(i, j)[2] == 0){
							blue++;
						}
						else if (xyz.at<Vec3b>(i, j)[1] == 255 && xyz.at<Vec3b>(i, j)[0] == 0 && xyz.at<Vec3b>(i, j)[2] == 0)
						{
							green++;
						}
						else if (xyz.at<Vec3b>(i, j)[1] == 0 && xyz.at<Vec3b>(i, j)[0] == 0 && xyz.at<Vec3b>(i, j)[2] == 255)
						{
							red++;
						}
						else if (xyz.at<Vec3b>(i, j)[1] == 255 && xyz.at<Vec3b>(i, j)[0] == 255 && xyz.at<Vec3b>(i, j)[2] == 255)
						{
							white++;
						}
						img.at<uchar>(i, j) = (uchar)255 / (a[j][i]);
					}
					col = a[j][i];
				
			}


		}
	}
	cout << "blue blobs=" << blue << "\n";
	cout << "green blobs=" << green << "\n";
	cout << "red blobs=" << red << "\n";
	cout << "white blobs=" << white << "\n";
	imshow("im", xyz);
	waitKey(0);

}


