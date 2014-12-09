#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace std;		
using namespace cv;

int main()
{
	Mat image;
	image = imread("F:\picture000.jpg", CV_LOAD_IMAGE_COLOR);
    namedWindow("my window", CV_WINDOW_AUTOSIZE);
	imshow("my window", image);
	waitKey();
	return 0;
}