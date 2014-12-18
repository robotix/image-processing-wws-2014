// Sample_Project9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\edge1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat output(input.rows, input.cols, input.flags, Scalar(0));
	for (int i = 1; i < input.rows - 1; i++)
	{
		for (int j = 1; j < input.cols - 1; j++)
		{
			int dx = 0, dy = 0;
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++)
				{
					dx += m*input.at<uchar>(i + m, j + n);
					dy += n*input.at<uchar>(i + m, j + n);
				}
			}
			output.at<uchar>(i, j) = (sqrt(dx*dx + dy*dy)>255) ? 255 : (sqrt(dx*dx + dy*dy));
		}
	}
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Output Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", input);
	imshow("Output Image", output);
	waitKey(0);
	return 0;
}