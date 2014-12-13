#include"stdafx.h"

#include<iostream>
#include<stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>

using namespace std;
using namespace cv;
/*Mat border(Mat img1)
{
	
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
			if ((max - min)>50) img2.at<uchar>(i, j) = 255;
		}
	}
	return(img2);
}*/
/*
Mat border2(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max,x=0,y=0;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows-1) || (j == 0) || (j == img1.cols-1)) continue;
			x = 0; y = 0;
			for (int k = -1; k <= 1; k++)
			{
				x+= img1.at<uchar>(i + k, j + 1) - img1.at<uchar>(i + k, j - 1);
				y += img1.at<uchar>(i + 1, j + k) - img1.at<uchar>(i - 1, j + k);

			}
			img2.at<uchar>(i, j) = sqrt(x*x + y*y);
		}
	}
	return(img2);
}
*/
/*Mat dilation(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
			img2.at<uchar>(i, j) =max;
		}
	}
	return(img2);
}
Mat erosion(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
		img2.at<uchar>(i, j) =min;
		}
	}
	return(img2);
}*/
Mat noisemean(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, avg = 0;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			avg = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
	
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					avg += img1.at<uchar>(i + k, j + l);
				}
			}
			img2.at<uchar>(i, j) = avg / 9;
		}
	}
	return(img2);
}
int sort(int a[])
{
	int temp;
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	return 0;
}
Mat noisemedian(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, n=0,a[9];
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					a[n++] = img1.at<uchar>(i + k, j + l);
				}
			}
			sort(a);
			img2.at<uchar>(i, j) = a[4];
		}
	}
	return(img2);
}
Mat gausian(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, n = 0,sum;
	float a[9] = { 0.06, 0.098, 0.06, 0.098, 0.162, 0.098, 0.06, 0.098, 0.06 };
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = 0;
			sum = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					sum += a[n++] * (img1.at<uchar>(i + k, j + l));
				}
			}
			img2.at<uchar>(i, j) = sum;
		}
	}
	return(img2);
}
int main()
{
	Mat img1;
	img1 = imread("hqdefault.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("edgedetect", WINDOW_AUTOSIZE);
	imshow("edgedetect", img1);
	//int thresh = 10;
	int lower = 0, upper = 0;
	createTrackbar("lower", "edgedetect", &lower, 256);
	createTrackbar("upper", "edgedetect",&upper,256);
	while (1)
	{
		Mat img2;
	    Canny(img1, img2, lower, upper, 3);
		//img2 = dilation(img2);
		//img2 = erosion(img2);
		imshow("edgedetect", img2);
		int a = waitKey(33);
		if (a == 27) break;
	}

	/*Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	img2 = noisemean(img1);
	namedWindow("mean",WINDOW_AUTOSIZE);
	imshow("mean", img2);
	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	img3 = noisemedian(img1);
	namedWindow("median", WINDOW_AUTOSIZE);
	imshow("median", img3);
	img3 = gausian(img1);
	namedWindow("gausian", WINDOW_AUTOSIZE);
	imshow("gausian", img3);*/
	/*img2 = border(img1);
	namedWindow("dilated", WINDOW_AUTOSIZE);
	imshow("dilated", img2);
	img2 = dilation(img2);
	namedWindow("eroded", WINDOW_AUTOSIZE); 
	imshow("eroded", img2);
	img2 = erosion(img2);
	//img2 = border2(img1);
	//img2 = border2(img2);
	//imshow("edgedetect", img2);
	waitKey(0);*/
}