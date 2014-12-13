// Sample_Project4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

Mat con2bw(Mat image, int threshold){
	Mat image2(image.rows, image.cols, CV_8UC1,Scalar(0));
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (((image.at<Vec3b>(i,j)[0] + image.at<Vec3b>(i,j)[1] + image.at<Vec3b>(i,j)[2]) / 3) > threshold)
				image2.at<uchar>(i, j) = 255;
		}
	}
	return image2;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int threshold;
	cout << "Enter the value of the Threshold(0-255)=";
	cin >> threshold;
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\pic.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output = con2bw(input,threshold);
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", input);
	imshow("Output Image", output);
	waitKey(0);
	return 0;
}