#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

int main(int argc, char** argv)
{
	void blur(InputArray src, OutputArray dst, Size ksize, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT);
	namedWindow("Before", CV_WINDOW_AUTOSIZE);
	Mat src = imread("juncker.jpg", 1);
	Mat dst;
	imshow("Before", src);

	for (int i = 1; i<51; i = i + 2)
	{
		blur(src, dst, Size(i, i));
		imshow("Smoothing by avaraging", dst);
		waitKey(3000);
	}
}