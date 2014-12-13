#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Mat conv_grey(Mat img)
{
	int i, j, temp;
	Mat img_grey(img.rows, img.cols, CV_8UC1);

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		temp = ((img.at<Vec3b>(j, i)[0])*(0.56)) + ((img.at<Vec3b>(j, i)[1])*(0.33)) + ((img.at<Vec3b>(j, i)[2])*(0.11));
		img_grey.at<uchar>(j, i) = temp;
	}

	return img_grey;
}

Mat conv_binary(Mat img,int thresh)
{
	int i, j;

	Mat img_bin(img.rows, img.cols, CV_8UC1);
	img_bin = conv_grey(img);

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		if ((img_bin.at<uchar>(j, i)) > thresh)
		img_bin.at<uchar>(j, i) = 255;
		else
		img_bin.at<uchar>(j, i) = 0;
    }
	return img_bin;
}

Mat invert_color_img(Mat img)
{
	int i, j;
	Vec3b temp;
	for (i = 0; i < img.cols; i++)
	for (j = 0; j < (img.rows)/2; j++)
	{
		temp.val[0] = img.at<Vec3b>(j, i)[0];
		temp.val[1] = img.at<Vec3b>(j, i)[1];
		temp.val[2] = img.at<Vec3b>(j, i)[2];

		img.at<Vec3b>(j, i)[0] = img.at<Vec3b>(((img.rows-1) - j), i)[0];
		img.at<Vec3b>(j, i)[1] = img.at<Vec3b>(((img.rows-1) - j), i)[1];
		img.at<Vec3b>(j, i)[2] = img.at<Vec3b>(((img.rows-1) - j), i)[2];

		img.at<Vec3b>(((img.rows-1) - j), i)[0] = temp.val[0];
		img.at<Vec3b>(((img.rows-1) - j), i)[1] = temp.val[1];
		img.at<Vec3b>(((img.rows-1) - j), i)[2] = temp.val[2];
	}

	return img;
}

Mat invert_grey_img(Mat img)
{
	int i, j,temp;

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < (img.rows) / 2; j++)
	{
		temp=img.at<uchar>(j, i);
		img.at<uchar>(j, i) = img.at<uchar>(((img.rows - 1) - j), i);
		img.at<uchar>(((img.rows - 1) - j), i) = temp;
	}

	return img;
}


Mat build_Histogram(Mat img)  //Pass any greyscale image.
{
	long N = img.rows * img.cols;
	
	int i, j, temp;
	long A[256] = { 0 };


	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		temp = img.at<uchar>(j,i);
		A[temp]++;
	}
	
	//for finding max.m pixel .
	int max = A[i];
	for (i = 0; i < 256;i++)
	if (A[i]>max)
		max = A[i];
	
	Mat x( ( (max+20)/20 ), 260, CV_8UC1);
	//For making Histgram .
	for (i = 0; i < 256; i++)
	for (j = 0; j < max/20; j++)
	{
		if (j<A[i]/20)
			x.at<uchar>(j, i) = 0;
		else
			x.at<uchar>(j, i) = 255;
	}
   x = invert_grey_img(x);

	return x;
}

int Binary_Thresh(Mat img) //Pass any image. 
{
	Mat x(260, 260, CV_8UC1);
	int N, s = 0, i, j, temp;
	long A[256] = { 0 };

	N = (img.rows) * (img.cols);

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		temp = img.at<uchar>(j, i);
		A[temp]++;
	}


	for (i = 0; i < 256; i++)
	{
		if ((s + A[i]) <= (N / 2))
			s += A[i];
		else
			break;
	}

	return i;
}

void TrakerBar_Creater(Mat img_load,int * default_thresh)
{
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "WINDOWS1", default_thresh, 150);
	
	while (1)
	{
		Mat bin = conv_binary(img_load, *default
);
		imshow("WINDOWS1", bin);
		char a = waitKey(33);
		if (a == 27)break;

	}

}
//Code for histogram (Uncomment it to use and comment the trackbar code main())
/*
int main()
{
	int i,j,N;
	int thresh;
	Mat img_load;
	img_load=imread("H://wallpapers//fruits.jpg",CV_LOAD_IMAGE_COLOR);
	
	N = img_load.rows*img_load.cols;

	Mat histogram(((N + 20) / 20),260, CV_8UC1);
	Mat img_out(img_load.rows,img_load.cols,CV_8UC1);

	img_out = conv_grey(img_load);
	histogram = build_Histogram(img_out);

	namedWindow("MyWindow",WINDOW_AUTOSIZE);
	
	//To print greyscale;
	imshow("MyWindow",img_out);
	waitKey(2000);

	//To print histogram; 	
	imshow("MyWindow", histogram);
	waitKey(4000);

	
	//Finding threshhold ;
	thresh = Binary_Thresh(img_load);
	//Converting to binary;
	img_out = conv_binary(img_load, thresh);


	//To print Binary img ;
	imshow("MyWindow", img_out);
	waitKey(0);

	return 0;
}

*/

//Program for track bar , uncomment it to use and comment the histogram main() ;
int main()
{
	int x = 10;
	//int *y = &x;
	
	Mat img_load;
	img_load = imread("H://wallpapers//fruits.jpg", CV_LOAD_IMAGE_COLOR);

	TrakerBar_Creater(img_load, &x);
	return 0;
}