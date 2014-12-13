#include<stdafx.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

int main()
{
	Mat image;
	image = imread("school-building-hi.png", CV_LOAD_IMAGE_GRAYSCALE);
	
	int i, j;
	Mat image2(image.rows, image.cols, CV_8UC1);
	
	for (i = 1; i<image.rows - 1; i++)
	for (j = 1; j<image.cols - 1; j++)
		image2.at<uchar>(i, j) = (int)(0.06*image.at<uchar>(i - 1, j - 1) + 0.098*image.at<uchar>(i - 1, j) + 0.06*image.at<uchar>(i - 1, j + 1) + 0.098*image.at<uchar>(i, j - 1) + 0.062*image.at<uchar>(i, j) + 0.098*image.at<uchar>(i, j + 1) + 0.06*image.at<uchar>(i + 1, j - 1) + 0.098*image.at<uchar>(i + 1, j) + 0.06*image.at<uchar>(i + 1, j + 1));
	namedWindow("Gaussian", CV_WINDOW_AUTOSIZE);
	imshow("Gaussian", image2);
	waitKey(0);
	return 0;

}
				
			
			
	