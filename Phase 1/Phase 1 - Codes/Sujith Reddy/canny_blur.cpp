#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <vector>
using namespace std;
using namespace cv;
#define MAX_KERNEL_LENGTH 20
int main()
{
	VideoCapture vid(0);
	while (1)
	{

		Mat image;
		vid.read(image);
		int i,j,T,h=0;
		vector<int> arr(255);
		int sum = 0, Sum = 0;
		
		
		if (image.empty())
			exit(1);
		Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));
		Mat canny(image.rows, image.cols, CV_8UC1, Scalar(0));
		//	Mat final1(image.rows, image.cols, CV_8UC1, Scalar(0));
		Mat final2(image.rows, image.cols, CV_8UC1, Scalar(0));
		//Mat final3(image.rows, image.cols, CV_8UC1, Scalar(0));
		//Mat final4(image.rows, image.cols, CV_8UC1, Scalar(0));
		for ( i = 0; i < final.rows; i++)
		{
			for ( j = 0; j < final.cols; j++)
			{
				int grey = (0.33 * (image.at<Vec3b>(i, j)[0]) + 0.33 * (image.at<Vec3b>(i, j)[1]) + .33*(image.at<Vec3b>(i, j)[2]));
				final.at<uchar>(i, j) = grey;
			}
		}
		for (i = 1; i < MAX_KERNEL_LENGTH; i += 2)
		{


			//blur(final, final1, Size(i, i), Point(-1, -1));
			GaussianBlur(final, final2, Size(i, i), 0, 0);
			//medianBlur(final, final3, i);
			//bilateralFilter(final, final4, i, 0, 0);

		}

		namedWindow("My Window", CV_WINDOW_AUTOSIZE);
		//namedWindow("My Window1", CV_WINDOW_AUTOSIZE);
		namedWindow("My Window2", CV_WINDOW_AUTOSIZE);
		//namedWindow("My Window3", CV_WINDOW_AUTOSIZE);
		//namedWindow("My Window4", CV_WINDOW_AUTOSIZE);
		imshow("My Window", final);
		//imshow("My Window1", final1);
		imshow("My Window2", final2);
		//imshow("My Window3", final3);
		//imshow("My Window4", final4);
		waitKey(33);

		for (i = 0; i < 255; i++) arr[i] = 0;
		

		for (i = 0; i < final2.rows; i++)
		{
			for (j = 0; j < final2.cols; j++)

			{
				T = (final2.at<uchar>(i, j)+ final2.at<uchar>(i, j) + final2.at<uchar>(i, j)) / 3;
				arr[T] = arr[T] + 1;
			}
		}
		imshow("My Window2", final2);
		waitKey(33);
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
		int LT = h / 3;
		int HT = h * 2 / 3;
		Canny(final2, canny, LT, HT, 3);
		imshow("Canny", canny);

		if (waitKey(33) == 27) break;
	}

	waitKey(0);
	return 0;
}