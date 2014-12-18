// Robin Singh Sidhu
// 13EC10052
#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include <queue>


using namespace cv;
using namespace std;

#define pi 3.14159265359
#define	gs(x,y)	img.at<uchar>(x, y) 

int cannyimp();
int tb2();
int scharr(Mat);
Mat gtob(int, Mat);
Mat grayscale(int, int, int);
int rw();
int flag();
void invert(Mat& img);
int histo();
Mat edge_detect(uchar);
int krcheck(Mat img, uchar thresh, int i, int j);
Mat sobel1(Mat);
Mat dilation(Mat img);
Mat erosion(Mat);
Mat meanfilter(Mat);
int median(int a[]);
Mat medianfilter(Mat img);
void swap(int *x, int *y);
Mat gauss_filter(Mat img);
void bfs_blob(Mat img, int **a, int qcount, int i, int j);
void blob_detect(Mat, bool);
void plot(Mat& , int i, int j);
Mat line_detect(Mat linimg, int );
void marker(Mat& img, int r, int t, Mat);
// CV_8SC1
Point p[1000000];
queue <Point> q;

int main()
{

	int threshold = 100;
	Mat linim = imread("A:\\lines.png", 1);
	Mat img = linim;
	imshow("org1", img);
	Canny(linim, linim, 50, 200);
	namedWindow("det", WINDOW_AUTOSIZE);
	createTrackbar("th", "det", &threshold, 250);
	while (1)
	{
		
		Mat detectim = line_detect(linim, threshold);
		imshow("det", detectim);
		if (waitKey(33) == 27)
			break;
	}
	

	


}

Mat line_detect(Mat linimg, int threshold) // linimg is almost binary
{
	int i, j;
	int rl = linimg.rows;
	int cl = linimg.cols;
	Mat acc(cl+rl, 720, CV_8UC1);
	Mat img(linimg.rows, linimg.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < cl + rl; i++)
	{
		for (j = 0; j < 720; j++)
		{
			acc.at<uchar>(i, j) = 0;
		}
	}
	for (i = 0; i < rl; i++)
	{
		for (j = 0; j < cl; j++)
		{
			if (linimg.at<uchar>(i, j) >= 250) //if white pixel
			{
				// represent in hough space
				plot(acc, i, j);

			}
		}
	}
	int max = 170, maxr = 0, maxt = 0;
	for (i = 0; i < rl+cl; i++)
	{
		for (j = 0; j < 720; j++)
		{
			if (acc.at<uchar>(i, j) > threshold)  // if possible intersection
			{
				// mark the line in img
				marker(img, i, j, linimg);
				//max = acc.at<uchar>(i, j);
				//maxr = i; // r of intersection	
				//maxt = j; // theta
			}
		}
	}

	/*for (i = 0; i < rl ; i++) // display the line with r = maxr and theta = maxt
	{
		for (j = 0; j < cl; j++)
		{
			if (int(j*cos(maxt*pi / 360) + i*sin(maxt*pi / 360)) >= maxr-1 && int(j*cos(maxt*pi / 360) + i*sin(maxt*pi / 360)) <= maxr+1)
			{
				gs(i, j) = 255;
			}
		}
	}
	*/
	//imshow("detect", img);
	imshow("Hough", acc);
	

	return img;
}
void marker(Mat& img, int r, int t, Mat linimg)
{
	int i, j;
	for (i = 0; i < img.rows; i++) // display the line with r = maxr and theta = maxt
	{
		for (j = 0; j < img.cols; j++)
		{
			if ((j*cos(t*pi / 360) + i*sin(t*pi / 360)) >= r && int(j*cos(t*pi / 360) + i*sin(t*pi / 360)) <= r && linimg.at<uchar>(i, j) >= 250)
			{
				gs(i, j) = 255;
			}
		}
	}
}
void plot(Mat& acc, int i, int j)
{
	int r, t;
	for (t = 0; t < 720; t++) // t is angle in degrees , incrementing half a degree
	{
		// r = xcos + ysin
		r = int(j*cos(t*pi / 360) + i*sin(t*pi / 360));
		if (r >= 0 && acc.at<uchar>(r, t) < 253)
			acc.at<uchar>(r, t) += 2;
	}
}