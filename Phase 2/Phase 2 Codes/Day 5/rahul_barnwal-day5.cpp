#include "stdafx.h"
#include <iostream>
#include<math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#define PI 3.14159265



using namespace std;
using namespace cv;
void lineext(Mat);
void main()
{
	Mat img = imread("E:\\line.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("w", img);
	cout << img.rows;
	lineext(img);
	waitKey(0);

}
void lineext(Mat img)
{
	Mat hough((int)(sqrt(img.rows*img.rows + img.cols*img.cols)), 180, CV_32SC1, Scalar(0));
	Mat accum(sqrt(img.rows*img.rows + img.cols*img.cols), 180, CV_32SC1, Scalar(0));
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) == 0)

			{
				for (int a = 0; a < 180; a++)
				{
					int r = (int)fabs(j*cos(a*PI / 180) + i*sin(a*PI / 180));
					hough.at<uchar>(r, a) += 1;
					accum.at<schar>(r, a) += 1;
				}
			}
		}

	}
	imshow("window", hough);
	
	cout << "debug";
	namedWindow("mywindow", CV_WINDOW_AUTOSIZE);
	int x = 0;
	createTrackbar("threshold", "mywindow", &x, 200); 
	
	
	while (1)
	{
		int count = 0;

		
		for (int i = 0; i < accum.rows; i++)
		{
			for (int j = 0; j < accum.cols; j++)
			{
				if (accum.at<uchar>(i, j) >=x)count++;
			}
		}
		
		int max = accum.at<schar>(0, 0);
		int ang[180], *R;
		R = new int[hough.rows];

		for (int t = 0; t < count; t++)
		{
			max = accum.at<schar>(0, 0);
			int i1, j1;
			for (i1 = 0; i1 < accum.rows; i1++)
			{
				for ( j1 = 0; j1 < accum.cols; j1++)
				{
					if (max <= accum.at<uchar>(i1, j1))
					{
						max = accum.at<uchar>(i1, j1);
						ang[t] = j1;
						R[t] = i1;
					}

				}
			}
			accum.at<uchar>(i1, j1) = 0;
		}
	
		Mat temp(img.rows, img.cols, CV_8UC1, Scalar(0));
		for (int s = 0; s < count; s++)
		{
			
			for (int i = 0; i < temp.rows; i++)
			{
				for (int j = 0; j < temp.cols; j++)
				{
					int c = fabs(j*cos((ang[s])*PI / 180) + i*sin((ang[s])*PI / 180));
					if ((img.at<uchar>(i, j) == 0) && (R[s] == (c) || R[s] == c + 1 || R[s] == c-1))
					{
						temp.at<uchar>(i,j) = 255;
					}
				}
			}
		}

		char a = waitKey(50);
		if(a == 27)
			break;
		imshow("mywindow", temp);
		free(R);
	}
	
	
}