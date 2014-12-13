// Sample_Project7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;
int thrsld(Mat input,int a[]){
	int i, sum = 0;
	for ( i = 0; sum <((input.rows*input.cols)/2) ; i++)
	{
		sum +=a[i];
	}
	return (i-1);

}
Mat con2bw(Mat image, int threshold){
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i,j) > threshold)
				image2.at<uchar>(i, j) = 255;
		}
	}
	return image2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\pic.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int a[256] = {0};
	int t, max = 0;
		for (int j = 0; j < input.rows; j++)
		{
			for (int k = 0; k < input.cols; k++)
			{
				a[(input.at<uchar>(j, k))]++;
			}
		}
		int thrsldval = thrsld(input,&a[0]);
		for (int n = 0; n <256 ; n++)
		{
			max = (a[n]>max) ? a[n] : max;
		}
		max /= 100;
		cout << max;
	Mat histo(max+10, 256, CV_8UC1,Scalar(255));
	for (int m = 0; m < 256; m++)
	{
		for (int l = max+9; l > (max+10-(a[m]/100)); l--)
		{
			histo.at<uchar>(l, m) = 0;
		}
	}
	namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
	imshow("Histogram", histo);
	namedWindow("Black And White", CV_WINDOW_AUTOSIZE);
		Mat output = con2bw(input, thrsldval);
	imshow("Black And White", output);
	waitKey(0);
	return 0;
}