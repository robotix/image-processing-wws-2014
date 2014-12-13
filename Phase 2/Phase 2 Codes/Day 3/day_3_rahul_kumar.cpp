include <opencv2/imgproc/imgproc.hpp>
#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;



void TrakerBar_Creater_Grey(Mat);
Mat conv_grey(Mat);
Mat conv_binary(Mat, int);
Mat invert_color_img(Mat);
Mat invert_grey_img(Mat);
Mat build_Histogram(Mat);
int Binary_Thresh(Mat);
void TrakerBar_Creater_Grey(Mat);
void TrakerBar_Creater_Color(Mat);
Mat Display_Border(Mat, int);
Mat Border_Creater_Algo(Mat);
void Display_Border_With_Trackbar(Mat);
Mat Delation(Mat);
Mat Erosion(Mat);
Mat Median_Filter(Mat);
Mat Gaussian_Filter(Mat);
void swap(int *, int *);
void insert_sort(int *, int);

void swap(int *x, int *y)
{
	int t;
	t = *x;
	*x = *y;
	*y = t;
}


void insert_sort(int A[], int n)  //In iscending Order.
{
	for (int i = 1; i<n; i++)
	{
		int j = i;
		while (j>0 && (A[j]<A[j - 1]))
		{
			swap(A[j], A[j - 1]);
			j--;
		}
	}
}



Mat Median_Filter(Mat img)
{
	int i, k, m, temp, j, sum_bl, sum_wh;
	int A[9];
	Mat img_out(img.rows, img.cols, CV_8UC1); // To return
	img_out = img;

	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{   
		temp = 0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			A[temp] = (img_out.at<uchar>(j + k, i + m));
			temp++;
		}

		insert_sort(A,9);
		img_out.at<uchar>(j, i) = A[4];
	}

	return img_out;
}

Mat Gaussian_Filter(Mat img)
{
	int i, k, m, temp, j, sum_bl, sum_wh;
	int B, A[9] = { 60, 96, 60, 96, 159, 96, 60, 96, 60 };
	Mat img_out(img.rows, img.cols, CV_8UC1); // To return
	img_out = img;

	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{
		temp = 0,B=0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			B += (img_out.at<uchar>(j + k, i + m))*A[temp];
			img_out.at<uchar>(j, i) = B/1000;
			temp++;
		}
	}

	return img_out;
}


Mat Erosion(Mat img) //Has bug, pls check
{
	int i, k,m,temp, j, sum_bl, sum_wh;

    Mat img_out(img.rows, img.cols, CV_8UC1); // To return
	img_out = img;
	//imshow("Windowx", img_out);
	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{
		sum_bl = 0; sum_wh = 0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			if ((img.at<uchar>(j + k, i + m)) == 0)
				sum_bl++;
			else
				sum_wh++;
		}

		if (sum_bl<sum_wh)
		{
			if (sum_bl != 0)
				img_out.at<uchar>(j, i) = 0;
			else
				img_out.at<uchar>(j, i) = 255;
		}
		
		else if (sum_bl>sum_wh)
		{
			if (sum_wh != 0)
				img_out.at<uchar>(j, i) = 255;
			else
				img_out.at<uchar>(j, i) = 0;
		}
		else
			img_out.at<uchar>(j, i) = img.at<uchar>(j, i);
	}

	return img_out;
}

Mat Delation(Mat img)
{
	int i, thresh, temp,k,m, j, sum_bl, sum_wh;

	Mat x(img.rows, img.cols, CV_8UC1); //To use
	Mat img_out(img.rows, img.cols, CV_8UC1); // To return
	x = img;
	
	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{
		sum_bl = 0; sum_wh = 0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			if ((x.at<uchar>(j + k, i + m)) <128 )
				sum_bl++;
				else
				sum_wh++;
		}
				if (sum_bl>sum_wh )
				img_out.at<uchar>(j, i) = 0;
				else
				img_out.at<uchar>(j, i) = 255;
			
	}
	

	return img_out;
}

Mat Border_Creater_Algo(Mat img)
{ 
	int i, m, k, temp, j, sum_x, sum_y;

	Mat x(img.rows, img.cols, CV_8UC1);
	Mat img_out(img.rows, img.cols, CV_8UC1);
	
	x = conv_grey(img);
	
	for (i = 1; i < (img.cols-1); i++)
	for (j = 1; j < (img.rows-1); j++)
	{
		sum_x = 0; sum_y = 0;

		for (k = -1; k < 2; k++)
		{
			sum_x += (x.at<uchar>(j + k, i - 1)) - (x.at<uchar>(j + k, i + 1));
			sum_y += (x.at<uchar>(j - 1, i + k)) - (x.at<uchar>(j + 1, i + k));
		}

		temp = sqrt( (sum_x*sum_x) + (sum_y*sum_y) );
		
		if (temp<256)
		img_out.at<uchar>(j, i) = temp;
		else
		img_out.at<uchar>(j, i) = 0;

	}

	return img_out;
}


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
	img_bin = img;

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

int Binary_Thresh(Mat img) //Pass any greyscale image. 
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


Mat Display_Border(Mat img, int Border_Thesh)
{
	Mat x(img.rows, img.cols, CV_8UC1), image(img.rows, img.cols, CV_8UC1);
	image = conv_grey(img);
	int i, j, k, m, max, min;
	for (i = 0; i < (img.cols); i++)
	{
		for (j = 0; j < (img.rows); j++)
		{
			if (i == 0 || j == 0 || i == (img.cols - 1) || j == (img.rows - 1))
				x.at<uchar>(j, i) = 0;
			else
			{
				max = image.at<uchar>(j, i); min = image.at<uchar>(j, i);
				for (k = -1; k < 2; k++)
				for (m = -1; m < 2; m++)

				{
					if ((image.at<uchar>(j + m, i + k))>max)
						max = x.at<uchar>(j + m, i + k);
					if ((image.at<uchar>(j + m, i + k)) < min)
						min = x.at<uchar>(j + m, i + k);
				}

				if (max - min >= Border_Thesh)
					x.at<uchar>(j, i) = 0;
				else
					x.at<uchar>(j, i) = 255;
			}
		}
	}
	return x;
}

void TrakerBar_Creater_Color(Mat img_load)
{
	int default_thresh = 10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
	createTrackbar("TC1", "WINDOWS1", &default_thresh, 255);
	createTrackbar("TC2", "WINDOWS1", &default_thresh, 255);
	createTrackbar("TC3", "WINDOWS1", &default_thresh, 255);

	while (1)
	{
		Mat bin = conv_binary(img_load, default_thresh);
		imshow("WINDOWS1", bin);
		char a = waitKey(33);
		if (a == 27)break;
	}
}

void TrakerBar_Creater_Grey(Mat img)
{
int default_thresh = 10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "WINDOWS1", &default_thresh, 255);

	while (1)
	{
		Mat bin = conv_binary(img, default_thresh);
		imshow("WINDOWS1", bin);
		char a = waitKey(33);
		if (a == 27)break;
	}

}


void Display_Border_With_Trackbar(Mat img)
{
	Mat x;
	int default_thresh = 10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "WINDOWS1", &default_thresh, 255);

	while (1)
	{
		x = Display_Border(img, default_thresh);
		imshow("WINDOWS1", x);
		char a = waitKey(33);
		if (a == 27)break;
	}
}



//Program for making display border.
/*
int main()
{
	int i, j;
	Mat img_load;
	img_load = imread("H://wallpapers//minions.jpg", CV_LOAD_IMAGE_COLOR);

	Mat x(img_load.rows, img_load.cols, CV_8UC1);
	
	int default_ = 10,lower=10,upper=10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);

	createTrackbar("Binary_Threshold", "WINDOWS1", &default_, 255);
	createTrackbar("lower", "WINDOWS1", &lower, 255);
	createTrackbar("upper", "WINDOWS1", &upper, 255);

	while (1)
	{
		conv_binary(img_load, default_);
		Canny(img_load, x, lower, upper);
		imshow("WINDOWS1", x);
		char a = waitKey(33);
		if (a == 27)break;
	}

return 0;
}

*/
//Prog for Delation and Erosiom ;
/*
int main()
{
	int i, j;
	Mat img_load;
	img_load = imread("H://wallpapers//minions.jpg", CV_LOAD_IMAGE_COLOR);

	Mat x(img_load.rows, img_load.cols, CV_8UC1);
	x = Border_Creater_Algo(img_load);
	
	int thresh = Binary_Thresh(x);
	x = conv_binary(x, 20);

	namedWindow("MyWindow1", WINDOW_AUTOSIZE);
	imshow("MyWindow1", x);
	//waitKey(0);
	x = Delation(x);
	
	namedWindow("MyWindow", WINDOW_AUTOSIZE);
	imshow("MyWindow", x);
	
	x = Erosion(x);


	namedWindow("MyWindow2", WINDOW_AUTOSIZE);
	imshow("MyWindow2", x);

	waitKey(0);

	return 0;
}

*/
//Applying various filters..

int main()
{
	int i, j;
	Mat img_load;
	img_load = imread("H://wallpapers//Capture1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	Mat x(img_load.rows, img_load.cols, CV_8UC1);
	x = img_load; //x = conv_grey(img_load);
	namedWindow("MyWindow_grey", WINDOW_AUTOSIZE);
	imshow("MyWindow_grey", x);
	Mat y(img_load.rows, img_load.cols, CV_8UC1);
	y = x;
	y = Median_Filter(x);
	namedWindow("MyWindow_Median", WINDOW_AUTOSIZE);
	imshow("MyWindow_Median", y);


	x = Gaussian_Filter(x);
	namedWindow("MyWindow_Gaussian", WINDOW_AUTOSIZE);
	imshow("MyWindow_Gaussian", x);

	waitKey(0);


	return 0;
}