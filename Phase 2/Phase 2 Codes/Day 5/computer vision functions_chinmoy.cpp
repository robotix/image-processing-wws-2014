// computer vision functions.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <queue>
using namespace std;
using namespace cv;

/*COLOUR DETECTION COLOUR DETECTION COLOUR DETECTION COLOUR DETECTION COLOUR DETECTION COLOUR DETECTION COLOUR DETECTION 


Mat detectcolor(Mat image, int h, int tol)
{
	Mat image1;
	cvtColor(image, image1, CV_BGR2HSV);
	int rows = image.rows;
	int cols = image.cols;
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if ((image.at<Vec3b>(i, j)[0] >= h - tol) && (image.at<Vec3b>(i, j)[0] <= h + tol))
			{
				for (int k = 0; k < 3; k++)
				{
					image1.at<Vec3b>(i, j)[k] = image.at<Vec3b>(i, j)[k];
				}
			}
			else
				image1.at<Vec3b>(i, j)[2] = 0;
		}
	}
	return image1;
}


int main(int argc, _TCHAR* argv[])
{
	Mat image;
	image = imread("c:\\download.jpg", 1);
	Mat image1;
	int val,h,tol=5;
	namedWindow("my window",WINDOW_AUTOSIZE);
	cout << "enter the color you want to detect\n 1>red \n 2>green 3>blue\n";
	cin >> val;
	if (val == 1)
		h = 5;
	if (val == 2)
		h = 80;
	if (val == 3)
		h = 160;
	cvtColor(image, image1, CV_BGR2HSV);
	image1 = detectcolor(image1, h, tol);
	Mat image2;
	cvtColor(image1, image2, CV_HSV2BGR);
	imshow("my window", image2);
	waitKey(0);

	

	return 0;
}


*/
/*


Mat image;
Mat image1;
int temp=1;
queue<Point>q;

void mark(int c, int d)
{
	for (int a = c - 1; a < c + 2; a++)
	{
		for (int b = d - 1; b < d + 2; b++)
		{
			if (image.at<uchar>(a, b) == 255 && image1.at<uchar>(a, b) == 1)
			{
				Point p;
				p.x = a;
				p.y = b;
				q.push(p);
				image1.at<uchar>(a, b) = 0;
			}
		}
	}
}
void blob(int i, int j)
{
	temp++;
	int rows = image.rows;
	int cols = image.cols;
	Point p;
	p.x = i;
	p.y = j;
	q.push(p);
	while (q.empty() != true)
	{
		p = q.front();
		image1.at<uchar>(p.x, p.y)=0;
		mark(p.x, p.y);
		image1.at<uchar>(p.x, p.y) = temp;
		q.pop();
	}
}


int main(int argc, _TCHAR* argv[])
{
	image = imread("C:\\Users\\CHINMOY SAM\\Pictures\\untitled.png", 0);
	image1 = imread("C:\\Users\\CHINMOY SAM\\Pictures\\untitled.png", 0);
	int rows=image.rows, cols=image.cols,i=0,j=0;
	for (int i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			image1.at<uchar>(i, j) = 1;
		}
	}
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if ((image.at<uchar>(i, j) == 255) && (image1.at<uchar>(i,j) == 1))
			{
				blob(i, j);
			}
		}
	}
	namedWindow("my window", WINDOW_AUTOSIZE);
	Mat image2(image.size(),0);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			image2.at<uchar>(i, j) = 255 / image1.at<uchar>(i, j);
	}
	}
	imshow("my window", image2);
	waitKey(0);
	return (0);




	 

}

*/
Mat image;


Mat hough()
{
	int r;
	int maxr = sqrt(image.rows*image.rows + image.cols*image.cols);
	int angle;
	Mat houghimg1(maxr,180,CV_8UC1,Scalar(0));
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) == 0)
			{
				for (angle = 0; angle < 181; angle++)
				{
					r = (int)(fabs(j*cos((angle*3.142)/180) + i*sin((angle*3.142)/180)));
					if (houghimg1.at<uchar>(r, angle) + 10 < 255)
						houghimg1.at<uchar>(r, angle) += 10;
				}
			}
		}
	}
	return houghimg1;
}

int main(int argc, _TCHAR* argv[])
{
	image = imread("C:\\Users\\CHINMOY SAM\\Pictures\\hough2.png", 0);
	int rows = image.rows;
	int cols = image.cols;
	int maxr = sqrt(rows*rows + cols*cols);
	Mat houghimg(maxr, 181, CV_8UC1, Scalar(0));
	houghimg = hough();
	int k=0;
	int dist[20000], anglemax[20000];
	for (int i = 0; i < maxr; i++)
	{
        for (int j = 0; j < 181; j++)
		{
			if ((houghimg.at<uchar>(i, j))>40)			
			{
				dist[k] = i;
				anglemax[k] = j;
				k++;
			}
		}
	}
	for (int i = 0; i < k; i++)
	{
		cout << "r =" << dist[i];
		cout << "angle =" << anglemax[i] <<"\n";
	}
	cout << k << "\n" <<rows << "\n" << cols << "\n"<< maxr;
	waitKey(0);
	namedWindow("my window", WINDOW_AUTOSIZE);
	imshow("my window", houghimg);
	waitKey(0);
	return (0);
}