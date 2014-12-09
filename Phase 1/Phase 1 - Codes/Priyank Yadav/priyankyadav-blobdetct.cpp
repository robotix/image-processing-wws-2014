#include "stdafx.h"
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<stdio.h>
#include<queue>
#include<stdio.h>
#include<conio.h>

using namespace std;
using namespace cv;
 typedef struct cor
{
	int x; int y;
} cor;
 /*
 int main()
 {
	 struct cor u, s, a;
	 queue<struct cor> q;
	 int i, j, t = 150, k, l, ctr = 0,r,c;


	 Mat image = imread("C:\\Users\\PRIYANK YADAV\\visual photos\\21.png", CV_LOAD_IMAGE_GRAYSCALE);
	 char win[] = "window";
	 Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	 r = image.rows; c = image.cols;
	 int **v = (int **)malloc(sizeof(int *)*r);
	 for (i = 0; i < r; i++)
	 {
		 v[i] = (int *)malloc(sizeof(int)*c);
		 for (j = 0; j < c; j++)
		 {
			 v[i][j] = 0;
		 }
	 }
	 int **b = (int **)malloc(sizeof(int *)*r);
	 for (i = 0; i < r; i++)
	 {
		 b[i] = (int *)malloc(sizeof(int)*c);
		 for (j = 0; j < c; j++)
		 {
			 b[i][j] = 0;
		 }
	 }
	 waitKey(0);
	 for (i = 0; i < r; i++)
	 {
		 for (j = 0; j < c; j++)
		 {
			 v[i][j] = b[i][j] = 0;
			 if (image.at<uchar>(i, j) > t)
				 image1.at<uchar>(i, j) = 255;
			 else
				 image1.at<uchar>(i, j) = 0;
		 }

	 }

	 for (i = 0; i < image1.rows; i++)
	 {
		
		 for (j = 0; j < image1.cols; j++)
		 {
			 s.x = i; s.y = j;
			 if (image1.at<uchar>(i, j) == 0)
			 		 v[i][j] = 1;
		
			 else if (image1.at<uchar>(i, j) != 0 && v[i][j]==0)
			 {
				 q.push(s);
				 ++ctr;
				 while (!q.empty())
				 {
					 
					 a = q.front();
					 q.pop();
					 for (k = (a.x) - 1; k <= (a.x) + 1; k++)
					 {
						 if (k >= 0 && k < image1.rows)
						 for (l = (a.y)-1; l <= (a.y) + 1; l++)
						 {
							 if (l >= 0 && l < image1.cols)
							 {
								 if (image1.at<uchar>(k, l) != 0 && v[k][ l] == 0)
								 {
									 u.x = k; u.y = l;
									 q.push(u);
									 v[k][l] = 1;
									 b[k][l] = ctr;
								 }
							 }
						 }
					 }
				 }
			 }
		 }
	 }
	 cout << ctr;
	 cout << " ";
	 for (i = 0; i < r; i++)
	 {
		 for (j = 0; j < c; j++)
		 {
			 cout << b[i][j] << " " ;
		 }
		 cout << endl;
	 }
	 namedWindow(win, CV_WINDOW_AUTOSIZE);
	 imshow(win, image1);
	 waitKey(0);
	 return 0;

 }*/
