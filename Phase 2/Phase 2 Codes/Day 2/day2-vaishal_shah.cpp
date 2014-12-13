// ComputerVisionProject.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;


Mat grey(Mat a)
{
	Mat z(a.rows,a.cols,CV_8UC1);
	int i,j;
	for(i=0;i<a.rows;i++)
	{
		for(j=0;j<a.cols;j++)
			z.at<uchar>(i,j)=(56*a.at<Vec3b>(i,j)[0]+33*a.at<Vec3b>(i,j)[1]+11*a.at<Vec3b>(i,j)[2])/100;
	}
	return z;
}
Mat bin(Mat a,int m)
{
	int i,j;
	for(i=0;i<a.rows;i++)
		for(j=0;j<a.cols;j++)
		{	if(a.at<uchar>(i,j)<m)
				a.at<uchar>(i,j)=0;
			else	a.at<uchar>(i,j)=255;
		}
		return a;
}
Mat colorch(Mat a,int m,int q)
{
int i,j;
	for(i=0;i<a.rows;i++)
		for(j=0;j<a.cols;j++)
		{	if(a.at<Vec3b>(i,j)[q]<m)
				a.at<Vec3b>(i,j)[q]=0;
			else	a.at<Vec3b>(i,j)[q]=255;
		}
		return a;
}
Mat inv(Mat a)
{
	int i,j,t;
	for(i=0;i<a.rows/2;i++)
		for(j=0;j<a.cols;j++)
		{t=a.at<Vec3b>(i,j)[0];	a.at<Vec3b>(i,j)[0]=a.at<Vec3b>(a.rows-1-i,j)[0];	a.at<Vec3b>(a.rows-1-i,j)[0]=t;
		t=a.at<Vec3b>(i,j)[1];	a.at<Vec3b>(i,j)[1]=a.at<Vec3b>(a.rows-1-i,j)[1];	a.at<Vec3b>(a.rows-1-i,j)[1]=t;
		t=a.at<Vec3b>(i,j)[2];	a.at<Vec3b>(i,j)[2]=a.at<Vec3b>(a.rows-1-i,j)[2];	a.at<Vec3b>(a.rows-1-i,j)[2]=t;
	}
	return a;
}
Mat hi(Mat im)
{
	int i,j,k;
	long int pf[256];
	for(int k=0;k<256;k++)pf[k]=0;
	for(i=0;i<im.rows;i++)
		for(j=0;j<im.cols;j++)
			pf[im.at<uchar>(i,j)]++;
	int m=0;
	for(k=0;k<(im.rows*im.cols)/2;m++)
		k=k+pf[m];
	Mat hist(500,256,CV_8UC1,Scalar(0));
	for(i=0;i<256;i++)
		for(j=0;j<pf[i]/100;j++)
			hist.at<uchar>(499-j,i)=255;
	return hist;
}
Mat binimg(Mat im)
{
	int i,j,k;
	long int pf[256];
	for(int k=0;k<256;k++)pf[k]=0;
	for(i=0;i<im.rows;i++)
		for(j=0;j<im.cols;j++)
			pf[im.at<uchar>(i,j)]++;
	int m=0;
	for(k=0;k<(im.rows*im.cols)/2;m++)
		k=k+pf[m];
	Mat hist=bin(im,m);
	return hist;
}
int main()
{
	/*Mat img;
	img=imread("D:\\Vaishal\\Vaishal\\Images\\FLOWERS\\a.jpg",1);
	namedWindow("track",WINDOW_NORMAL);
	int x=50;
	char a;
	createTrackbar("Threshold","track",&x,255);
	while(1)
	{
		Mat im=grey(img);
		Mat binary=bin(im,x);
		imshow("track",binary);
		a=waitKey(33);
		if(a==27)break;
	}
	*/

	Mat img;
	namedWindow("track",WINDOW_NORMAL);
	int x=100,y=100,z=100;
	char a;
	createTrackbar("red","track",&x,256);
	createTrackbar("blue","track",&y,256);
	createTrackbar("green","track",&z,256);
	while(1)
	{
		img=imread("D:\\Vaishal\\Vaishal\\Images\\FLOWERS\\a.jpg",1);
		Mat bi=colorch(img,x,2);
		Mat bin=colorch(bi,y,0);
		Mat binary=colorch(bin,z,1);
		imshow("track",binary);
		a=waitKey(33);
		if(a==27)break;
	}


		return 0;
}