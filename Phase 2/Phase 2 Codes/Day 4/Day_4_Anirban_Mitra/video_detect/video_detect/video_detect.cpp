// video_detect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;

/*Mat makebinary(Mat image, int n)
{
	int temp;
	Mat image2(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			temp = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
			if (temp>n)
				image2.at<uchar>(i, j) = 255;
			else
				image2.at<uchar>(i, j) = 0;
		}
	}
	return image2;
}*/
Mat edge(Mat img, int n)
{
	Mat img2(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			int max = img.at<uchar>(i - 1, j - 1);
			int min = img.at<uchar>(i - 1, j - 1);
			for (int r = i - 1; r <= i + 1; r++)
			{
				for (int c = j - 1; c <= j + 1; c++)
				{
					if (img.at<uchar>(r, c)>max)
					{
						max = img.at<uchar>(r, c);
					}
					if (img.at<uchar>(i, j) < min)
					{
						min = img.at<uchar>(r, c);
					}

				}
			}
			if (max - min>n)
				img2.at<uchar>(i, j) = 255;
		}
	}
	return img2;
}
Mat invert(Mat img)
{
	Mat imgx(img.rows, img.cols, CV_8UC3);
	for (int j = 0; j < img.cols; j++)
	{
		for (int i = 0; i < img.rows; i++)
		{
			imgx.at<Vec3b>(i, j)[0] = img.at<Vec3b>(img.rows - 1 - i, j)[0];
			imgx.at<Vec3b>(i, j)[1] = img.at<Vec3b>(img.rows - 1 - i, j)[1];
			imgx.at<Vec3b>(i, j)[2] = img.at<Vec3b>(img.rows - 1 - i, j)[2];
		}
	}
	return imgx;

}

int main(int argc, _TCHAR* argv[])
{
	VideoCapture v(0);
	namedWindow("Video", WINDOW_NORMAL);
	namedWindow("Edge", WINDOW_NORMAL);
	int x = 0;
	createTrackbar("Threshold", "Edge", &x,255);
	while (true)
	{
		Mat frame;
		v >> frame;
		//cvtColor(frame, frame, CV_RGB2GRAY);
		imshow("Video", frame);
		imshow("Edge", edge(frame,x));
		int val = waitKey(33);
		if (val == 27)
			break;
	}
	return 0;
}

