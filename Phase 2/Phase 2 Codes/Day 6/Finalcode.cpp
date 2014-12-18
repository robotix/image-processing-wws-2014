#include "stdafx.h"
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<queue>
#include<stdlib.h>
#include<math.h>



using namespace cv;
using namespace std;
Mat cannyim(Mat);
Mat noisereduction(Mat);
int shapedetection(Mat);
Mat houghlines(Mat);
bool Blob(Mat);
int sizeblob(Mat);

int main()
{
	
	int f1;
	int n;
	int i, j, ang, r;
	VideoCapture v(0);
	int c = 0;
	while (1)
	{
		Mat Frame;
		v >> Frame;
		Mat copy(Frame.rows, Frame.cols, CV_8UC1);
		Mat img(Frame.rows, Frame.cols, CV_8UC1);
		copy= cannyim(Frame);
		imshow("copy", copy);
		waitKey(100);
		Mat hough(Frame.rows, Frame.cols, CV_8UC1);
		hough = houghlines(copy);
		imshow("Window", hough);
		f1 = waitKey(33);
		while (1)
		{

			if (Blob(Frame) && sizeblob(Frame) >= 0)
			{
				cout<<"a";
			}
			else if (Blob(Frame) && sizeblob ==0)
			{
				c++;
				break;
			}
			else
			{
				break;
			}
		}
		if (c>0)
		{
			break;
		}
		int x1 = 0, y1 = 0, white = 0;
		for (i = 0; i < Frame.rows; i++)
		{
			for (j = 0; j < Frame.cols; j++)
			{
				if (hough.at<uchar>(i, j) == 255)
				{
					white++;
						x1 = x1 + j;
					y1 = y1 + i;
				}
			}
		}
		if (abs(x1 - y1) < 30)
		{
			cout<<"w";
		}
		else if (y1>x1)
		{
			cout<<"d";
		}
		else
		{
			cout<<("a");
		}
		if (f1 == 27)
			break;
	}
}

Mat noisereduction(Mat edge)
{
	int b, w;
	b = w = 0;
	int x, y, i, j;
	int r = edge.rows;
	int c = edge.cols;
	for (x = 1; x <r - 1; x++)
	{
		for (y = 1; y < c - 1; y++)
		{
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (edge.at<uchar>(i, j) == 0)
					{
						b++;
					}
					if (edge.at<uchar>(i, j) == 255)
					{
						w++;
					}
				}
			}
			if (b != 0 && w != 0)
			{

				if (b > w)
				{
					edge.at<uchar>(x, y) = 0;
				}
				else
				{
					edge.at<uchar>(x, y) = 255;
				}
				b = w = 0;
			}
		}
	}
	for (x = 1; x <r - 1; x++)
	{

		for (y = 1; y < c - 1; y++)
		{
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (edge.at<uchar>(i, j) == 0)
					{
						b++;
					}
					if (edge.at<uchar>(i, j) == 255)
					{
						w++;
					}
				}
			}
			if (b != 0 && w != 0)
			{
				if (b > w)
				{
					edge.at<uchar>(x, y) = 255;
				}
				else
				{
					edge.at<uchar>(x, y) = 0;
				}
				b = w = 0;
			}
		}
	}


	return(edge);
}

Mat houghlines(Mat xyz)
{
	Mat dst, cdst, color_dst;
	Mat img(xyz.rows, xyz.cols, CV_8UC1,Scalar(0));
	int i, j;
	int y;
	Canny(xyz, dst, 50, 200, 3);
	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180,100, 60, 3);
	for (size_t i = 0; i < lines.size(); i++)
	{
		line(img, Point(lines[i][0], lines[i][1]),Point(lines[i][2], lines[i][3]), Scalar(255), 1, 8);
	}
	return(img);
	}
Mat cannyim(Mat xyz)
{
	Mat img;
	Canny(xyz, img, 50,200, 3);
	return(img);
}
bool Blob(Mat xyz)
{
	int **a;
	int i, j, l, z;
	Mat image;
	cvtColor(xyz, image, CV_BGR2GRAY);
	int b;
	int t = 0;
	int c;
	l = 0;
	z = 0;
	int col, blue, white, green;
	double red = 0;
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(0));
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

				if (r <= t)
				{
					r++;
					if (xyz.at<Vec3b>(i, j)[0] > 220 && xyz.at<Vec3b>(i, j)[1] < 40 && xyz.at<Vec3b>(i, j)[2] <40 ){
						blue++;
					}
					else if (xyz.at<Vec3b>(i, j)[1] == 255 && xyz.at<Vec3b>(i, j)[0] == 0 && xyz.at<Vec3b>(i, j)[2] == 0)
					{
						green++;
					}
					else if (xyz.at<Vec3b>(i, j)[1] == 0 && xyz.at<Vec3b>(i, j)[0] == 0 && xyz.at<Vec3b>(i, j)[2] == 255)
					{
						red = red + 1;
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
	if (red > 0.6*xyz.rows*xyz.cols)
	{
		return(true);

	}
	else
	{
		return(false);
	}
}
int sizeblob(Mat bw)
{
	vector<vector<Point>> C;
	findContours(bw, C, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	int triangle = 0;
	int fourside = 0;
	int i;
	vector<Point> app;
	for (i = 0; i < C.size(); i++)
	{
		approxPolyDP(Mat(C[i]), app, arcLength(Mat(C[i]), true)*0.2, true);
		if (app.size() == 3)
		{
			triangle++;
		}
		else if (app.size() == 4)
		{
			fourside++;
		}
	}
	return(fourside);
}
