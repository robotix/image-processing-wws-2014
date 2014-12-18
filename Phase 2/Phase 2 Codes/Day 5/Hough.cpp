#include <queue>
#include"stdafx.h"
#include <iostream>
#include "vector"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
using namespace std;
using namespace cv;
void main()
{
	Mat image = imread("lines.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img(image.rows, image.cols, CV_8UC1);
	int r;
	r = image.rows*(1.414);
	Mat ho(r, 180, CV_8UC1,Scalar(0));
	Canny(image, img, 20, 50, 3);
	int i, j,k,l;
	for (i = 0; i <= img.rows; i++)
	{
		for (j = 0; j <= img.cols; j++)
		{
			for (k = 0; k <= r; k++)
			for (l = 0; l <= 180; l++)
			{
				if (k == i*cos(l) + j*sin(l))
					ho.at<uchar>(k, l) = 255;
			}
		}
	}
	namedWindow("Hough",WINDOW_NORMAL);
	imshow("Hough", ho);
	waitKey(0);
}