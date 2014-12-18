#include"stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#define pi 3.142
using namespace std;
using namespace cv;
/*int main()
{
	Mat image = imread("C://gaurav.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat image1(image.rows,image.cols,CV_8UC1,Scalar(0));
	int t=30;
	namedWindow("New", WINDOW_NORMAL);
	createTrackbar("threshold", "New", &t, 100);
	int r = sqrt((image.rows*image.rows) + (image.cols*image.cols));
	int **a;
	a = (int**)malloc((181)*sizeof(int*));
	for (int i = 0; i < 181; i++)
	{
		a[i] = (int*)malloc((2*r+1)*sizeof(int));
	}
	for (int i = 0; i < 181; i++)
	{
		for (int j = 0; j < 2*r+1; j++)
		{
			a[i][j] = 0;
		}
	}

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if ((image.at<uchar>(i, j)) == 255)
			{
				for (int k = 0; k < 181; k++)
				{
					unsigned int x = (r + (j*cos(k*pi / 180) + i*sin(k*pi / 180)));
					a[k][x] += 1;			
				}
			}
		}
	}
	while (1)
	{
		for (int k = 0; k < 181; k++)
		{
			for (int s = 0; s < 2 * r + 1; s++)
			{
				if (a[k][s] >= t)
				{
					for (int j = 0; j < image.cols; j++)
					{
						int y_ = ((s - r - j*cos(k*pi / 180)) / sin(k*pi / 180));
						if (y_ >= 0 && y_ < image.rows)
						{
							if (image.at<uchar>(y_, j) == 255)
								image1.at<uchar>(y_, j) = 255;
						}
					}
				}
			}
		}

		imshow("New", image1);
		char a=waitKey(33);
		if (a == 27)
			break;
	    
	}
}
*/