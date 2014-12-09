#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include<stdlib.h>
using namespace std;
using namespace cv;

int main()
{
	VideoCapture vid(0);
	int LT = 0, HT = 0;
	while (1)
	{
		Mat image;
		vid.read(image);
		vector<int> arr(255);
		int sum = 0, Sum = 0;
		int i, j, T,t=0;
		int h = 0;

		if (image.empty())
			exit(1);
		namedWindow("My Window", CV_WINDOW_AUTOSIZE);
		Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));
		
		for (i = 0; i < 255; i++) arr[i] = 0;
		for (i = 0; i < final.rows; i++)
		{
			for (j = 0; j < final.cols; j++)

			{
				T = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
				arr[T] = arr[T] + 1;
			}
		}
		for (i = 0; (i < 255); i++)
		{
			sum = sum + arr[i];
		}
		for (i = 0; (i < 255); i++)
		{
			Sum = Sum + arr[i];
			if (Sum> sum / 2)
			{
				h = i;
				break;
			}
		}

		Canny(image, final, LT, HT, 3);
		createTrackbar("Lower Threashold", "My Window", &LT, 255);
		createTrackbar("Higher Threashold", "My Window", &HT, 255);
		vector<vector<Point>> contours;
		vector<Vec4i>heirachy;

		//morphological opening (removes small objects from the foreground)
		erode(final, final, getStructuringElement(MORPH_ELLIPSE, Size(1, 1)));
		dilate(final, final, getStructuringElement(MORPH_ELLIPSE, Size(1, 1)));

		//morphological closing (removes small holes from the foreground)
		dilate(final, final, getStructuringElement(MORPH_ELLIPSE, Size(1, 1)));
		erode(final, final, getStructuringElement(MORPH_ELLIPSE, Size(1, 1)));
		
		
		imshow("My Window", final);

		
		int ikey = waitKey(33);
		if (ikey == 27)
			break;

	}
	waitKey(0);
	return 0;
}