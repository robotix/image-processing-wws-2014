// Sample_Project9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	int threshold;
	cout << "Enter the value of the threshold=";
	cin >> threshold;
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\edge1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat output(input.rows, input.cols, input.flags,Scalar(0));
	for (int i = 1; i < input.rows-1; i++)
	{
		for (int j = 1; j < input.cols-1; j++)
		{
			int min, max;
			max = min = input.at<uchar>(i, j);
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <=1 ; n++)
				{
					max = (max > input.at<uchar>(i + m, j + n)) ? max : input.at<uchar>(i + m, j + n);
					min = (min < input.at<uchar>(i + m, j + n)) ? min : input.at<uchar>(i + m, j + n);
				}
			}
			if ((max-min)>threshold)
			{
				output.at<uchar>(i, j) = 255;
			}
		}
	}
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", input);
	imshow("Output Image", output);
	waitKey(0);
	return 0;
}