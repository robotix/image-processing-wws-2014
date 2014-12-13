// Sample_Project4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

Mat con2gray(Mat image){
	Mat image2(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			image2.at<uchar>(i, j) = image.at<Vec3b>(i, j)[0] * 0.56 + image.at<Vec3b>(i, j)[1] * 0.33 + image.at<Vec3b>(i, j)[2]*0.11;
		}
	}
	return image2;
}
int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\pic.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output = con2gray(input);
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", input);
	imshow("Output Image", output);
	waitKey(0);
	return 0;
}