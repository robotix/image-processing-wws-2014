#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY = 0, int borderType = BORDER_DEFAULT);
	namedWindow("Before", CV_WINDOW_AUTOSIZE);
	Mat src = imread("juncker.jpg", 1);
	Mat dst;
	imshow("Before", src);
	for (int i = 1; i < 51; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		imshow("Gaussian filter", dst);
		waitKey(5000);
	}
}
