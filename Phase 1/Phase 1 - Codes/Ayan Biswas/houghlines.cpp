#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("G:\\images\\blobs2.jpg", CV_LOAD_IMAGE_COLOR);
	//first find canny edges
	Mat grey(image.rows, image.cols, CV_8UC1);
	int i, j, k, l;
	int b, g, r;
	for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			b = image.at<Vec3b>(i, j)[0];
			g = image.at<Vec3b>(i, j)[1];
			r = image.at<Vec3b>(i, j)[2];
			grey.at<uchar>(i, j) = (33 * b + 56 * g + 11 * r) / 100;
		}
	}
	int freq[256];
	for (i = 0; i < 256; ++i)
		freq[i] = 0;
	for (i = 0; i < image.rows; ++i)
	for (j = 0; j < image.cols; ++j)
		freq[grey.at<uchar>(i, j)]++;
	Mat cannyedge(image.rows, image.cols, CV_8UC1);
	int sum = 0, thres = 0;
	while (sum < (image.rows*image.cols) / 2)
		sum += freq[thres++];
	int threslow = thres / 3;
	int threshigh = thres * 2 / 3;
	Canny(grey, cannyedge, threslow, threshigh, 3);
	//cannyedge has white edges on black background
	//use HoughLines to find lines
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", cannyedge);
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	Mat output(image.rows, image.cols, CV_8UC1);
	vector<Vec2f> lines;  //lines is a vector of r rows and 2 columns storing float values
	int thres2 = 40;
	createTrackbar("Threshold", "Output", &thres2, sqrt(image.rows*image.rows + image.cols*image.cols));
	while (1)
	{
		HoughLines(cannyedge, lines, 1, CV_PI / 180, thres2);
		for (i = 0; i < image.rows; ++i)
		for (j = 0; j < image.cols; ++j)
			output.at<uchar>(i, j) = 255;
		for (i = 0; i < lines.size(); ++i)
		{
			double rho = lines[i][0];
			double theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1500 * (-b));
			pt1.y = cvRound(y0 + 1500 * (a));
			pt2.x = cvRound(x0 - 1500 * (-b));
			pt2.y = cvRound(y0 - 1500 * (a));
			line(output, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
			/*for (k = 0; k < image.rows; ++k)
			{
				for (l = 0; l < image.cols; ++l)
				{
					if (cannyedge.at<uchar>(k, l) == 0)
						continue;
					if (fabs(rho - l * a - k * b) <= 0.05)
					{
						int m, n;
						for (m = k - 1; m <= k + 1; ++m)
						{
							for (n = l - 1; n <= l + 1; ++n)
							{
								if (m>=0 && m<image.rows && n>=0 && n<image.cols)
									output.at<uchar>(m, n) = 0;
							}
						}
					}
				}
			}*/
		}
		imshow("Output", output);
		if (waitKey(30) == 27)
			break;
	}
	waitKey(0);
	return 0;
}