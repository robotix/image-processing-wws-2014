// Problem Statement Solution 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <vector>
#include <math.h>

using namespace std;
using namespace cv;

Mat con2bw1(Mat image, int threshold){
	Mat image2(image.rows, image.cols, CV_8UC1);
	Mat test;
	cvtColor(image, test, CV_BGR2HLS_FULL);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (test.at<Vec3b>(i, j)[1] < threshold)
				image2.at<uchar>(i, j) = 255;
			else
				image2.at<uchar>(i, j) = 0;
		}
	}
	return image2;
}

int detectcolor(int value){
	if (value>245 || value < 5) return 4;
	if (value > 145 && value < 180) return 1;
	if (value>70 && value<90) return 2;
	if (value>35 && value < 50) return 3;
	else return 0;
}

String order[5] = { "Circle","Triangle","Rectangle", "Square","Arrow" },k;
String coming, coming_color;
int gone1 = 0, t=0, move2=0;
int frame_count = 0,l;

int _tmain(int argc, _TCHAR* argv[])
{
	int threshold = 200, min_x, min_y;
	VideoCapture v("C:\\Users\\Sanat Kumar Saha\\Desktop\\shape.mp4");
	while (1)
	{
		int top = 350;
		Mat frame, camera;
		v >> frame;
		Mat frame3 = frame;
		frame=frame(Rect(10, 10, frame.cols - 20, frame.rows - 20));
		Mat BnW = con2bw1(frame, threshold);
		Mat frame2;
		cvtColor(frame, frame2, CV_BGR2HLS_FULL);
		vector <vector <Point>> c;
		vector<Point>app[50];
		findContours(BnW, c, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		l = 0;
		for (int i = 0; i < c.size(); i++)
		{
			approxPolyDP(c[i], app[i], arcLength(c[i], 1)*0.02, true);
			min_x = 0, min_y = 0;
			int j;
			for (j = 0; j < app[i].size(); j++)
			{
				min_x += app[i][j].x;
				min_y += app[i][j].y;
			}
			min_x /= j;
			min_y /= j;
			if (sqrt(((app[i][0].x - min_x)*(app[i][0].x - min_x)) + ((app[i][0].y - min_y)*(app[i][0].y - min_y)))>40)
			{
				if (min_y<400){
					switch (detectcolor((int)frame2.at<Vec3b>((min_y + app[i][0].y) / 2, (min_x + app[i][0].x) / 2)[0]))
					{
					case 1:coming = "Circle"; if (coming == order[gone1]){
							   l = 1;
							   move2 = min_x; k = coming; t = min_y;
					} break;
					case 2: coming = "Arrow"; if (coming == order[gone1]){
								l = 1;
								move2 = min_x; k = coming; t = min_y;
					} break;
					case 3: coming = "Square";  if (coming == order[gone1]){
								l = 1;
								move2 = min_x;  k = coming; t = min_y;
					} break;
					case 4:
						coming = (app[i].size() == 3) ? "Triangle" : "Rectangle";
						if (coming == order[gone1]){ l = 1; move2 = min_x;  k = coming; t = min_y; }
							
						break;
					}
				}
			}
		}
		if ((k == order[gone1]) && l == 0)
		{
			frame_count++;
		}
		if (frame_count > 12){
			frame_count = 0; gone1++; move2 = 0;
		}
		if (gone1 >= 5)
		{
			break;
		}
		if(move2!=0)rectangle(frame, Point(move2 - 30, frame.rows - 5), Point(move2 + 30, frame.rows - 1), Scalar(0, 0, 0), CV_FILLED);

		imshow("BnW Window", frame);
		char a = waitKey(33);
		if (a == 27)break;
	}
	return 0;
}

