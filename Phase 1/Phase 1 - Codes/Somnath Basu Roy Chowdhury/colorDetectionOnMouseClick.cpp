// Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
using namespace cv;


int mx = 0, my = 0, clicked = 0; //Global variables to store image co-ordinates and the flag to check

void mouse_callback(int event, int x, int y, int flags, void* param)
{
	//This is called every time a mouse event occurs in the window
	if (event == CV_EVENT_LBUTTONDOWN) { //This is executed when the left mouse button is clicked
		//Co-ordinates of the left click are assigned to global variables and flag is set to 1
		mx = x;
		my = y;
		clicked = 1;
	}
}

int main(){

	
	Mat image = imread("D:\\baba.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image1(image.rows, image.cols, CV_8UC1);
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	
	setMouseCallback("Input", mouse_callback, NULL);
	while (1)
	{

		imshow("Input", image);
		
		if (clicked)
		{
			clicked = 0;
			cout << mx << " " << my << endl;
			int b = image.at<Vec3b>(my, mx)[0];
			int g = image.at<Vec3b>(my, mx)[1];
			int r = image.at<Vec3b>(my, mx)[2];
			int i, j;
			for (i = 0; i < image1.rows; i++)
			{
			for (j = 0; j < image1.cols; j++)
			{
				if (image.at<Vec3b>(i, j)[0]<b + 30 && image.at<Vec3b>(i, j)[0]>b - 30 &&
					image.at<Vec3b>(i, j)[1]<g + 30 && image.at<Vec3b>(i, j)[1]>g - 30&&
					image.at<Vec3b>(i, j)[2]<r + 30 && image.at<Vec3b>(i, j)[2]>r - 30)
				{
			image1.at<uchar>(i, j) = 255;
			}
			else
			image1.at<uchar>(i, j) = 0;
			}
			}

			imshow("Output", image1);
		}
		if (waitKey(30) == 27)
			break;
	}
	return 0;


}