#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image(200, 300, CV_8UC3, Scalar(0, 0, 255));
	char win[] = "Striped Image"; 
	int location;
	for (int i = 0; i<image.rows; i++)
	{
		for (int j = 0; j<image.cols; j++)
		{
			image.at<Vec3b>(i, j)[0] = 0;
			image.at<Vec3b>(i, j)[1] = 0;
			image.at<Vec3b>(i, j)[2] = 0;
			if (i<image.rows / 3)
				image.at<Vec3b>(i, j)[2] = 255;	
			else if (i >= (2 * image.rows) / 3)
				image.at<Vec3b>(i, j)[0] = 255;	
			else
				image.at<Vec3b>(i, j)[1] = 255;	
		}
	}
	namedWindow(win, CV_WINDOW_FULLSCREEN);
	imshow(win, image);
	waitKey(0);
	return 0;
}