#include "stdafx.h"
#include <iostream>
#include<vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
void prnimage(Mat);
void prngrey(Mat);
void binaryimg(Mat,int);
void invertimg(Mat);
int threshhold(Mat);

int main()
{
	int p;
	Mat image,x,y;
	image = imread("F:\\image processing\\10847904_10204565576051151_4759441167489822037_n.jpg");
	int t = threshhold(image);
	binaryimg(image, t);
	/*namedWindow("My window", CV_WINDOW_FULLSCREEN);
	createTrackbar("Threshhold", "My window", &p, 255);
	while (1)
	{
		 binaryimg(image, p);
		char a = waitKey(33);
		if (a == 27)break;

	} */
	cout << "No. of rows" << image.rows << "\nNo. of columns" << image.cols << "\nThreshhold"<<t;
	getchar();
	//waitKey(10000);
	return 0;
}
void prngrey(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			img.at<uchar>(i, j) = 0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2];
		}
	}
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	//imshow("my window", img);
	waitKey(0);
	//return(img);
}
void binaryimg(Mat image,int threshhold)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j, temp;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			temp = (int)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
			if (temp < threshhold) 
				img.at<uchar>(i, j) = 0;
			else img.at<uchar>(i, j) = 255;
		}
	}
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	imshow("My window", img);
	waitKey(0);

}
void prnimage(Mat image)
{
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	imshow("my window", image);
	waitKey(0);
}
void invertimg(Mat image)
{
	int i, j,temp[3];
	for (i =0; i < image.rows/2; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			temp[0] = image.at<Vec3b>(i, j)[0]; image.at<Vec3b>(i, j)[0] = image.at<Vec3b>(image.rows - i - 1, j)[0]; image.at<Vec3b>(image.rows - i - 1, j)[0] = temp[0];
			temp[1] = image.at<Vec3b>(i, j)[1]; image.at<Vec3b>(i, j)[1] = image.at<Vec3b>(image.rows - i - 1, j)[1]; image.at<Vec3b>(image.rows - i - 1, j)[1] = temp[1];
			temp[2] = image.at<Vec3b>(i, j)[2]; image.at<Vec3b>(i, j)[2] = image.at<Vec3b>(image.rows - i - 1, j)[2]; image.at<Vec3b>(image.rows - i - 1, j)[2] = temp[2];
		}
	}
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	imshow("my window", image);
	waitKey(0);
}
int threshhold(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j,A[256],k;
	int n = image.rows*image.cols;
	for (int k = 0; k < 256; k++) A[k] = 0;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			img.at<uchar>(i, j) = 0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2];
			A[img.at<uchar>(i, j)]++;
		}
	}
	
	for (k = 0; k < 256; k++)
	{
		A[k]/= 50;
	}
	
	Mat hist(500, 256, CV_8UC1, Scalar(255));
	for (k = 0; k < 256; k++)
	{
		for (int l = 0; l <= A[k]; l++)
		{
			hist.at<uchar>(l, k) = 0;
		}
	}
	//invertimg(hist);
	int temp;
	for (i = 0; i < hist.rows / 2; i++)
	{
		for (j = 0; j < hist.cols; j++)
		{
			temp = hist.at<uchar>(i, j); hist.at<uchar>(i, j) = hist.at<uchar>(hist.rows - i - 1, j); hist.at<uchar>(hist.rows - i - 1, j)= temp;
	
		}
	}
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	imshow("my window", hist);
	waitKey(0);    
	int sum = 0; k = 0;
	while (sum <= (n /50)/2)
	{
		sum += A[k++];
	}
	return(k - 1);
}