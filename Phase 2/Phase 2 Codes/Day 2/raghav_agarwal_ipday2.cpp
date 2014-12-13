#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include<iostream>

using namespace std;
using namespace cv;
Mat convertbin(Mat image1, int threshold)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	for (j = 0; j < image1.rows; j++)
	{
		images.at<uchar>(j, i) = (uchar)(image1.at<Vec3b>(j, i)[0])*0.56 + (image1.at<Vec3b>(j, i)[1])*0.33 + (image1.at<Vec3b>(j, i)[2])*0.11;
		if ((images.at<uchar>(j, i)>threshold))
			images.at<uchar>(j, i) = 255;
		else
			images.at<uchar>(j, i) = 0;
	}
	return images;
}
Mat convertbin1(Mat image1, int threshold)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	{
		for (j = 0; j < image1.rows; j++)
		{

			if ((image1.at<uchar>(j, i)>threshold))
				images.at<uchar>(j, i) = 255;
			else
				images.at<uchar>(j, i) = 0;
		}
	}
	return images;
}
void Trackbar(Mat image)
{
	int x = 10;
	namedWindow("Trackbar1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Trackbar1", &x, 250);
	while (1)
	{
		Mat img = convertbin1(image,x);
		
		imshow("Trackbar1",img);
		char a = waitKey(33);
		if (a==27)
			break;
}	
}
void Trackbar1(Mat image)
{
	int x = 10,y=15;
	int i, j;
	namedWindow("Trackbar1", WINDOW_NORMAL);
	createTrackbar("blueThreshold", "Trackbar1", &x, 100);
	createTrackbar("greenThreshold", "Trackbar1", &y, 100-x);
	while (1)
	{
		Mat img(image.rows, image.cols, CV_8UC1);
		for (i = 0; i < image.cols; i++)
		for (j = 0; j < image.rows; j++)
		{
			img.at<uchar>(j, i) = (uchar)(image.at<Vec3b>(j, i)[0])*x / 100 + (image.at<Vec3b>(j, i)[1])*y / 100 + (image.at<Vec3b>(j, i)[2])*(100 - x - y) / 100;
		}
		imshow("Trackbar1", img);
			char a = waitKey(33);
			if (a == 27)
				break;
		
	}
}
Mat histogram(Mat image1,int * th)
{
	Mat imhist(256, (image1.rows*image1.cols)/1000, CV_8UC1);
	long long int a[256],i,j,sum=0;
	for (i = 0; i < 256; i++)
		a[i] = 0;
	for (i = 0; i < image1.cols; i++)
	for (j = 0; j < image1.rows; j++)
		a[image1.at<uchar>(j, i)]++;
	for (j = 0; j < 256; j++)
	for (i = 0; i < (image1.rows*image1.cols) / 1000; i++)
	{
		if (i < (a[j]/40 ))
			imhist.at<uchar>(j, i) = 0;
		else
			imhist.at<uchar>(j, i) = 255;
	}
	for (i = 0; i < 256; i++)
	{
		sum += a[i];
		if (sum>(image1.rows*image1.cols) / 2)
		{
			*th = i;
			break;
		}
	}

	return imhist;
}

Mat patchmaker()
{
	Mat images(1000,1000,CV_8UC3);
	int i, j;
	for (i = 0; i <1000; i++)
	{
		for (j = 0; j <1000; j++)
		{
			images.at<Vec3b>(j, i)[(i + j) % 3] = 255;
			images.at<Vec3b>(j, i)[(i + j + 1) % 3] = 0;
			images.at<Vec3b>(j, i)[(i + j + 2) % 3] = 0;
		}
	}
	return images;
}
Mat reverse(Mat image1)
{
	Mat images(image1.rows, image1.cols, CV_8UC3);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	{
		for (j = 0; j < image1.rows; j++)
		{
			images.at<Vec3b>(j, image1.cols-i-1)[0] = image1.at<Vec3b>(j, i)[0];
			images.at<Vec3b>(j, image1.cols-i-1)[1] = image1.at<Vec3b>(j, i)[1];
			images.at<Vec3b>(j, image1.cols-i-1)[2] = image1.at<Vec3b>(j, i)[2];
		}
	}
	return images;
}
Mat convert(Mat image1)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	{
		for (j = 0; j < image1.rows; j++)
		{
			images.at<uchar>(j, i) = (image1.at<Vec3b>(j, i)[0] + image1.at<Vec3b>(j, i)[1] + image1.at<Vec3b>(j, i)[2]) / 3;
		}
	}
	return images;
}

Mat convert1(Mat image1)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	for (j = 0; j < image1.rows; j++)
	images.at<uchar>(j, i) = (uchar)(image1.at<Vec3b>(j, i)[0])*0.56 + (image1.at<Vec3b>(j, i)[1])*0.33 + (image1.at<Vec3b>(j, i)[2])*0.11;
		return images;
}
	

int main()
{

	Mat image1,imgray,imgra;
	int th=50;
    image1 = imread("C:\\download.jpg", CV_LOAD_IMAGE_COLOR);
   	namedWindow("hello sachin", WINDOW_AUTOSIZE);
	imshow("hello sachin", image1);
	waitKey(0);/*
	imgray = convert(image1);
    imshow("hello sachin", imgray);
	waitKey(0);*/
	imgray = convert1(image1);
	imshow("hello sachin", imgray);
	waitKey(0);
	/*imgra = convertbin1(imgray,th);
	imshow("hello sachin", imgra);
	waitKey(0);
	imgray = reverse(image1);
	Mat histo = histogram(imgray,&th);
	imshow("hello sachin", histo);
	waitKey(0);
	imgray = convertbin(image1, th);
	imshow("hello sachin", imgray);
	waitKey(0);*/
	Trackbar1(image1);
	return(0);
}