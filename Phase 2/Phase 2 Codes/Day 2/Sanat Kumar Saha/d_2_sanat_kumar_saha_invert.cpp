// Sample_Project6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;
Mat invimgver(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			output.at<Vec3b>(i, j)[0] = input.at<Vec3b>(input.rows - i - 1, j)[0];
			output.at<Vec3b>(i, j)[1] = input.at<Vec3b>(input.rows - i - 1, j)[1];
			output.at<Vec3b>(i, j)[2] = input.at<Vec3b>(input.rows - i - 1, j)[2];
		}
	}
	return output;
}
Mat invimghor(Mat input){
	Mat output(input.rows, input.cols, input.flags);
	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			output.at<Vec3b>(i, j)[0] = input.at<Vec3b>(i,input.cols - j - 1)[0];
			output.at<Vec3b>(i, j)[1] = input.at<Vec3b>(i, input.cols - j - 1)[1];
			output.at<Vec3b>(i, j)[2] = input.at<Vec3b>(i, input.cols - j - 1)[2];
		}
	}
	return output;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\pic.jpg", CV_LOAD_IMAGE_COLOR);
	//Mat output = invimghor(input);
	Mat output = invimgver(input);
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", input);
	imshow("Output Image", output);
	waitKey(0);
	return 0;
}