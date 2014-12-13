// Project_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	int i, j;
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\pic.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output(input.rows, input.cols, input.flags);
	for ( i = 0; i < input.rows; i++)
	{
		for (j = 0; j < input.cols; j++)
		{
			output.at<Vec3b>(i,j)[0] = 0;
			output.at<Vec3b>(i,j)[1] = 0;
			output.at<Vec3b>(i,j)[2] = input.at<Vec3b>(i,j)[2];
		}
	}
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", input);
	imshow("Output Image", output);
	waitKey(0);
	return 0;
}