#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace std;
using namespace cv;
#define MAX_KERNEL_LENGTH 10
int Mx = 0, My = 0;

void mouse(int event, int x, int y, int, void*)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		Mx = x;
		My = y;
	}
}
int main()
{
	int i, j;
	Mat image;

	int h, s, v, h1, s1, v1;
	int ht, st, vt;

	image = imread("kriti.jpg", CV_LOAD_IMAGE_COLOR);
	Mat imagehsv(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 255));
	Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));

	Mat color(image.rows, image.cols, CV_8UC1, Scalar(0));
	//Mat colordet(image.rows, image.cols, CV_8UC1, Scalar(0));
	cvtColor(image, imagehsv, CV_BGR2HSV);
	namedWindow("input", CV_WINDOW_NORMAL);
	namedWindow("Color", CV_WINDOW_NORMAL);
	setMouseCallback("input", mouse, NULL);
	createTrackbar("HT", "Color", &ht, 15);
	createTrackbar("ST", "Color", &st, 70);
	createTrackbar("VT", "Color", &vt, 200);
	while (1)
	{
		imshow("input", image);
		h = imagehsv.at<Vec3b>(My, Mx)[0];
		s = imagehsv.at<Vec3b>(My, Mx)[1];
		v = imagehsv.at<Vec3b>(My, Mx)[2];
		for (i = 0; i < image.rows; i++)
		for (j = 0; j < image.cols; j++)
		{
			h1 = imagehsv.at<Vec3b>(i, j)[0];
			s1 = imagehsv.at<Vec3b>(i, j)[1];
			v1 = imagehsv.at<Vec3b>(i, j)[2];
			if (h1<(h + ht) && (h1>h - ht) && (s<s + st) && (s>s - st) && (v<v + vt) && (v>v - vt))
			{
				color.at<uchar>(i, j) = 255;
			}
			else color.at<uchar>(i, j) = 0;


		}
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
							x = color.at<uchar>(k, l);
						}
						if (max < x) max = x;
						if (min>x) min = x;
					}
				}

				if ((max - min) > 125) final.at<uchar>(i, j) = 0;

			}
		}



		imshow("Color", final);


		if (waitKey(33) == 27) break;
	}


	return 0;
}