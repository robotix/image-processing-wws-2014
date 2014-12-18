#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<opencv2/imgproc/imgproc.hpp>
#include<queue>
using namespace std;
using namespace cv;
# define pi 3.1414
int detectcolor(Mat image, int hue, int lum,int sat,int tol,int tol1,int tol2, int th)
{
	int i, j,h,n=0,l,s;
	for (i = 0; i < image.rows;i++)
	for (j = 0; j < image.cols; j++)
	{
		h = image.at<Vec3b>(i, j)[0];
		l = image.at<Vec3b>(i, j)[1];
		s = image.at<Vec3b>(i, j)[2];
       if (abs(h - hue) < tol && abs(l-lum)<tol1 && abs(s-sat)<tol2)
			n++;
	}
	if (n>th)
		return 1;
	else
		return 0;
}
Mat getbinary(Mat image, int hue, int lum, int sat, int tol, int tol1, int tol2)
{
	Mat bimage(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j, h, n = 0, l, s;
	for (i = 0; i < image.rows; i++)
	for (j = 0; j < image.cols; j++)
	{
		h = image.at<Vec3b>(i, j)[0];
		l = image.at<Vec3b>(i, j)[1];
		s = image.at<Vec3b>(i, j)[2];
		if (abs(h - hue) < tol && abs(l - lum) < tol1 && abs(s - sat) < tol2)
			bimage.at<uchar>(i, j) = 255;//white
	}
	return bimage;
}
Mat erosion(Mat image1)
{
	Mat image(image1.rows, image1.cols, CV_8UC1);
	int i, j, nb, nw;
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		if (i == 0 || j == 0 || i == (image1.rows - 1) || j == (image1.cols - 1))
			image.at<uchar>(i, j) = 0;
		else
		{
			nb = nblack(image1, i, j);
			nw = 9 - nb;
			if (nb>0 && nw>0)
			{
				if (nb>nw)
					image.at<uchar>(i, j) = 255;
				else
					image.at<uchar>(i, j) = 0;
			}
			else
				image.at<uchar>(i, j) = image1.at<uchar>(i, j);
		}
	}
	return image;

}
Mat dilation(Mat image1)
{
	Mat image(image1.rows, image1.cols, CV_8UC1);
	int i, j, nb, nw;
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		if (i == 0 || j == 0 || i == (image1.rows - 1) || j == (image1.cols - 1))
			image.at<uchar>(i, j) = 0;
		else
		{
			nb = nblack(image1, i, j);
			nw = 9 - nb;
			if (nb>0 && nw>0)
			{
				if (nb > nw)
					image.at<uchar>(i, j) = 0;
				else
					image.at<uchar>(i, j) = 255;
			}
			else
				image.at<uchar>(i, j) = image1.at<uchar>(i, j);
		}
	}
	return image;

}
int ccwhite(Mat image)
{
	int i = image.rows * 3 / 4;
	int j,n=0,h,l,s,f;
	for (j = 0; j < image.cols; j++)
	{
		h = image.at<Vec3b>(i, j)[0];
		l = image.at<Vec3b>(i, j)[1];
		s = image.at<Vec3b>(i, j)[2];
		if (abs(h) < 10 && abs(l - 255) < 10 && abs(l) < 10)//0,255,0 values for white seen using paint image
			n++;
		else
			n = 0;
		if (n>15)
		{
			f = j - n;
			break;//starting index of the white lane as seen by robot to tackle noises taken at least 15 pixels white ina row;
		}
	}
	for (j =f; j < image.cols; j++)
	{
		h = image.at<Vec3b>(i, j)[0];
		l = image.at<Vec3b>(i, j)[1];
		s = image.at<Vec3b>(i, j)[2];
		if (abs(h) < 10 && abs(l) < 10 && abs(l) < 10)//0,0,0 value for black seen usin g paint image paint
			n++;
		else
			n = 0;
		if (n>15)
		{
			l = j - n;
			break;//finishing  index of the white lane as seen by robot to tackle noises taken at least 15 pixels black ina row;
		}
	}
	return (f + l) / 2;// centre of the white patch
}
int main()
{
	Mat frame,frame1,bframe;
	char a=33;
	int k, th = 55, tol, h, l, s, tol1, tol2, cw;
	float ac, abr;
	h = 254;//value for red;
	l = 132;//value for red;
	s = 218;//value for red;

	namedWindow("current frame", WINDOW_NORMAL);
	VideoCapture V(1);
	
	cvtColor(frame, frame1, CV_BGR2HLS_FULL);
	
	while (a != 27)
	{
		V >> frame;
		cvtColor(frame, frame1, CV_BGR2HLS_FULL);
		k=detectcolor(frame1, h,l,s,tol,tol1,tol2, th);//detct whether red is present in sufficient amount or not
		if (k==1)//we encountered a red circle or rectangle;
		{
		
	        //get binary image for frame for applying shape detection with red replaced with white and all other replaced with black;
			 bframe = getbinary(frame1, h, l, s, tol, tol1, tol2);
			//noise removal to remove smallwhite patches
			 bframe = dilation(bframe);
			 bframe = dilation(bframe);
			 bframe = dilation(bframe);
			 bframe = erosion(bframe);
			 vector< vector<Point> > contours;
			 vector<Rect> boundRect(contours.size());
			 vector< vector<Point> > boundingBoxArea;
			 findContours(bframe, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
			 if (contours.size() == 1)//there is only one fig
			 {
				 boundRect[0] = boundingRect(Mat(contours[0]);
				 ac = contourArea(contours[0]);//area of the contour
				 boundingBoxArea.clear();
				 boundingBoxArea.push_back(Point2f(boundRect[0].x, boundRect[0].y));
				 boundingBoxArea.push_back(Point2f(boundRect[0].x + boundRect[0].width, boundRect[0].y));
				 boundingBoxArea.push_back(Point2f(boundRect[0].x + boundRect[0].width, boundRect[0].y + boundRect[0].height));
				 boundingBoxArea.push_back(Point2f(boundRect[0].x, boundRect[0].y + boundRect[0].height));
				 abr = contourArea(boundingBoxArea);//area of the bounding rectangle
				 if (abs(abr / ac - 4 / pi) < 0.5)//circle stop using the ratio of bounded rectangle to circle
					 stall();
				 else if (abs((abr / ac - 1) < 0.5)//rectangle turn right using the ratio of bounded rectangle to circle
					 full_right();
				 else// something wrong proceed with lane
					 k = 0;
			 }
            if (k == 0)//we have still not encountered red circle or rectangle
		{
			cw=ccwhite(frame1);// check centre white in hls 
			if (abs(cw - frame.cols / 2)<10)
				forward();// almost in center of lane keep movin forward);
			else if (cw>frame.cols / 2)
				right();//centre of white is in right of centre of image bot has starting moving towards the left barrier hence move right
			else
				left();//move left
		}
		imshow("current frame", frame);
		a = waitKey(33);
	
	return 0;
}