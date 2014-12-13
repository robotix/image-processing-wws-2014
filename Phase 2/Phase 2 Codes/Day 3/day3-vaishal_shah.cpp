// ComputerVisionProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
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
Mat edge(Mat a,int x)
{
	long int i,j,u,v;
	int max,min;
	Mat img(a.rows,a.cols,CV_8UC1,255);
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{
			max=min=a.at<uchar>(i-1,j-1);
			for(u=i-1;u<=i+1;u++)
				for(v=j-1;v<=j+1;v++)
				{
					if(a.at<uchar>(u,v)>max)	max=a.at<uchar>(u,v);
					else if(a.at<uchar>(u,v)<min)	min=a.at<uchar>(u,v);
				}
				if((max-min)>x)	img.at<uchar>(i,j)=0;
		}
		return img;
}
Mat newedge(Mat a)
{
long int i,j;
	int x,v,y;
	Mat img(a.rows,a.cols,CV_8UC1,255);
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{
			x=a.at<uchar>(i-1,j+1)-a.at<uchar>(i-1,j-1)+a.at<uchar>(i,j+1)-a.at<uchar>(i,j-1)+a.at<uchar>(i+1,j+1)-a.at<uchar>(i+1,j-1);
			y=a.at<uchar>(i+1,j+1)-a.at<uchar>(i-1,j+1)+a.at<uchar>(i+1,j)-a.at<uchar>(i-1,j)+a.at<uchar>(i+1,j-1)-a.at<uchar>(i-1,j-1);
			v=(int)pow((x*x + y*y),0.5);
			//v=v/3;
			if(v>255)	img.at<uchar>(i,j)=255;
			else img.at<uchar>(i,j)=v;
		}
		return img;
}
Mat edgex(Mat a)
{
long int i,j;
	int x;
	Mat img(a.rows,a.cols,CV_8UC1,255);
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{
			x=a.at<uchar>(i-1,j+1)-a.at<uchar>(i-1,j-1)+a.at<uchar>(i,j+1)-a.at<uchar>(i,j-1)+a.at<uchar>(i+1,j+1)-a.at<uchar>(i+1,j-1);
			//x=x/3;
			if(x>255)	img.at<uchar>(i,j)=255;
			else img.at<uchar>(i,j)=x;
		}
		return img;
}
Mat edgey(Mat a)
{
long int i,j;
	int y;
	Mat img(a.rows,a.cols,CV_8UC1,255);
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{
			y=a.at<uchar>(i+1,j+1)-a.at<uchar>(i-1,j+1)+a.at<uchar>(i+1,j)-a.at<uchar>(i-1,j)+a.at<uchar>(i+1,j-1)-a.at<uchar>(i-1,j-1);
			//y=y/3;
			if(y>255)	img.at<uchar>(i,j)=255;
			else img.at<uchar>(i,j)=y;
		}
		return img;
}
Mat colgr(Mat a,int x)
{
	Mat img(a.rows,a.cols,CV_8UC1);
		for(int i=0;i<a.rows;i++)
			for(int j=0;j<a.cols;j++)
				img.at<uchar>(i,j)=a.at<Vec3b>(i,j)[x];
		return img;	
}
Mat dil(Mat a)
{
	Mat img(a.rows,a.cols,CV_8UC1,255);
	int i,j,u,v;
	int n;
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{	
			n=0;
			for(u=i-1;u<i+2;u++)
				for(v=j-1;v<j+2;v++)
				{if(a.at<uchar>(u,v)==0)	n++;}
			if(n>=5)	img.at<uchar>(i,j)=0;
		}
		return img;
}
Mat ero(Mat a)
{
	Mat img(a.rows,a.cols,CV_8UC1,255);
	int i,j,u,v;
	int n;
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{	
			n=0;
			for(u=i-1;u<i+2;u++)
				for(v=j-1;v<j+2;v++)
				{if(a.at<uchar>(u,v)==0)	n++;}
			if(n<5 && n>0)	img.at<uchar>(i,j)=0;
			else if(n==9)	img.at<uchar>(i,j)=0;
		}
		return img;
}
Mat blur1(Mat a)
{
	Mat x(a.rows,a.cols,CV_8UC1, Scalar(0));
	int i,j,u,v,s;
	for(i=3;i<a.rows-3;i++)
		for(j=3;j<a.cols-3;j++)
		{
			s=0;
			for(u=i-3;u<i+4;u++)
				for(v=j-3;v<j+4;v++)
					s+=a.at<uchar>(u,v);
			x.at<uchar>(i,j)=s/49;
		}
		return x;
}
Mat blur2(Mat a)
{
	Mat x(a.rows,a.cols,CV_8UC1);
	int i,j,u,v,s[9],t,k;
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{
			k=0;
			for(u=i-1;u<i+2;u++)
				for(v=j-1;v<j+2;v++)
					{
						s[k]=a.at<uchar>(u,v);
						k++;
					}
			for(u=0;u<9;u++)
				for(v=0;v<9;v++)
				{if(s[u]>s[v])	{t=s[u];s[u]=s[v];s[v]=t;}}
			x.at<uchar>(i,j)=s[4];
		}
		return x;
}
Mat blur3(Mat a)
{
Mat x(a.rows,a.cols,CV_8UC1);
	int i,j;
	for(i=1;i<a.rows-1;i++)
		for(j=1;j<a.cols-1;j++)
		{
			x.at<uchar>(i,j)=(0.098*(a.at<uchar>(i-1,j)+a.at<uchar>(i+1,j)+a.at<uchar>(i,j-1)+a.at<uchar>(i,j+1))+0.06*(a.at<uchar>(i-1,j-1)+a.at<uchar>(i+1,j-1)+a.at<uchar>(i+1,j+1)+a.at<uchar>(i-1,j+1))+0.162*a.at<uchar>(i,j))/0.794;
		}
		return x;
}

/*
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

/*	Mat img;
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
	
Mat img;
	img=imread("D:\\Vaishal\\Vaishal\\Images\\a.jpg",1);
	//	Mat i=grey(img);
	//	i=edge(i,50);
	//	imshow("Edge",i);
	
	int x=50;
	char a;
	namedWindow("Dil",1);
	namedWindow("Ero",1);
	namedWindow("edge",1);
	createTrackbar("Threshold","edge",&x,255);
	while(1)
	{
		//img=imread("D:\\Vaishal\\Vaishal\\mages\\Background\\butterfly.jpg",1);
		Mat i=grey(img);
		i=edge(i,x);
		imshow("edge",i);
		i=dil(i);
		imshow("Dil",i);
		i=ero(i);
		imshow("Ero",i);
		a=waitKey(33);
		if(a==27)break;
	}
/*	Mat img,imgx,imgy;
	img=imread("D:\\Vaishal\\Vaishal\\Images\\Background\\FM.jpg",1);
	Mat i=grey(img);
	namedWindow("grey",WINDOW_NORMAL);
	imshow("grey",i);
	im=newedge(i);
	namedWindow("NewEdge",WINDOW_NORMAL);
	imshow("NewEdge",im);
	im=newedge(im);
	namedWindow("NewEdge2",WINDOW_NORMAL);
	imshow("NewEdge2",im);
	waitKey(0);
	

		return 0;
}
*/

int main()
{ 
	/*Mat	i,ib1,ib2,ib3;
	Mat img=imread("D:\\Vaishal\\Vaishal\\Images\\b.jpeg",1);
	i=grey(img);
	namedWindow("grey",WINDOW_NORMAL);
	imshow("grey",i);
	ib1=blur1(i);namedWindow("blur1",WINDOW_NORMAL);
	imshow("blur1",ib1);
	ib2=blur2(i);namedWindow("blur2",WINDOW_NORMAL);
	imshow("blur2",ib2);
	ib3=blur3(i);namedWindow("blur3",WINDOW_NORMAL);
	imshow("blur3",ib3);
	
	waitKey(0);*/
	Mat i,o;
	int m1,m2;
	Mat img=imread("D:\\Vaishal\\Vaishal\\Images\\b.jpeg",1);
	i=grey(img);
	namedWindow("canny",1);
	m1=50;
	m2=100;
	char a;
	createTrackbar("m1","canny",&m1,255);
	createTrackbar("m2","canny",&m2,255);
	while(1)
	{
		Canny(i,o,m2,m1,3);
		imshow("canny",o);
		a=waitKey(33);
		if(a==27)break;
	}
	return 0;
}