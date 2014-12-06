#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
	Mat image;
	int t=0;
	image = imread("samantha.jpg", CV_LOAD_IMAGE_COLOR);
	if (image.empty())
		exit(1);
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	createTrackbar("Track", "My Window", &t, 255);
	Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));

	while (true)
	{
		int value = t;
		for (int i = 0; i < final.rows; i++)
		{
			for (int j = 0; j < final.cols; j++)
			{
				
				if (((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3) > value)
				{
					final.at<uchar>(i, j) = 255;
				}
				else
					final.at<uchar>(i, j) = 0;
			}
		}
		imshow("My Window", final);
		waitKey(33);
              //if(waitKey()=27) break;
	}

	
	
	waitKey(0);
	return 0;
}