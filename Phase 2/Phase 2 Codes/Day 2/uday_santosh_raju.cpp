// ComputerVision.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

Mat filter(Mat image)
{
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			image.at<Vec3b>(i, j)[0] = 0;
			image.at<Vec3b>(i, j)[1] = 0;
		}
	}
	return(image);
}

void printflag()
{
	Mat image(900, 1800, CV_8UC3);
	int i, j;
	for (i = 0; i < 300; i++)
	{
		for (j = 0; j < 1800; j++)
		{
			image.at<Vec3b>(i, j)[0] = 0;
			image.at<Vec3b>(i, j)[1] = 165;
			image.at<Vec3b>(i, j)[2] = 255;
		}
	}

	for (i = 300; i < 600; i++)
	{
		for (j = 0; j < 1800; j++)
		{
			image.at<Vec3b>(i, j)[0] = 255;
			image.at<Vec3b>(i, j)[1] = 255;
			image.at<Vec3b>(i, j)[2] = 255;
		}
	}

	for (i = 600; i < 900; i++)
	{
		for (j = 0; j < 1800; j++)
		{
			image.at<Vec3b>(i, j)[0] = 0;
			image.at<Vec3b>(i, j)[1] = 255;
			image.at<Vec3b>(i, j)[2] = 0;
		}
	}
	namedWindow("Window1", WINDOW_NORMAL);
	imshow("Window1", image);
	waitKey(0);

}

Mat convert_to_gs(Mat image)
{
	Mat copy(image.rows, image.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			copy.at<uchar>(i, j) = ((image.at<Vec3b>(i, j)[0] * 0.56) + (image.at<Vec3b>(i, j)[1] * 0.33) + (image.at<Vec3b>(i, j)[2] * 0.11));
		}
	}
	return(copy);
}

Mat reflection(Mat image)
{
	Mat reflec(image.rows, image.cols, CV_8UC1);
	int k;
	for (int i = image.rows - 1, k = 0; i >= 0; i--, k++)
	{
		for (int j = 0; j<image.cols; j++)
		{
			reflec.at<uchar>(k, j) = image.at<uchar>(i, j);
		}
	}
	return(reflec);
}

Mat convert_to_binary(Mat image, int thresh)
{
	Mat binary(image.rows, image.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) <= thresh)
				binary.at<uchar>(i, j) = 0;
			else if (image.at<uchar>(i, j) > thresh)
				binary.at<uchar>(i, j) = 255;
		}
	}
	return(binary);
}

Mat histogram(Mat image)
{
	
	int a[256] = { 0 };
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			a[image.at<uchar>(i, j)]++;
		}
	}


	Mat histo(501,256,CV_8UC1,Scalar(255));
	for (int i = 0; i < 256; i++)
	{
		a[i] = (int)(  ( (a[i]*500) / (image.rows*image.cols) )  );
	}
	for (int i = 0; i < 256; i++)
	{
		histo.at<uchar>(500 - a[i], i) = 0;
	}
	return(histo);
}
int threshold(Mat image)
{
	int a[256], sum = 0, k;
	for (int i = 0; i < 256; i++)
		a[i] = 0;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			a[image.at<uchar>(i, j)]++;
		}
	}
	for (k = 0; k < 256; k++)
	{
		if (sum >= ((image.rows*image.cols) / 2))
			break;
		sum += a[k];
	}
	return(k);
}

int main(int argc, _TCHAR* argv[])
{
	Mat image;
	image = imread("c:\\Users\\V.Uday\\Desktop\\fb pics\\hariharan.jpg");
	Mat gs = convert_to_gs(image);
	//Mat reflec = reflection(gs);
	//Mat histo = histogram(image);
	//int thresh;
	//thresh = threshold(gs);
	//Mat binary = convert_to_binary(gs, thresh);
	int x;
	namedWindow("Window1",WINDOW_NORMAL);
	createTrackbar("threshhold","Window1",&x,255);
	while (1)
	{
		Mat binary = convert_to_binary(gs,x);
		imshow("Window1",binary);
		char a = waitKey(33);
		if (a == 27)break;
	}
	/*namedWindow("Window1",WINDOW_AUTOSIZE);
	imshow("Window1",histo);
	waitKey(0);*/
	return(0);
}