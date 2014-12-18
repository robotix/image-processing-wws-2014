#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"


#include <iostream>
#include <stdio.h>
#include <math.h>
#include <queue>

using namespace std;
using namespace cv;


Mat convert_to_binary(Mat image, int threshold=120)
{
		Mat binary(image.rows,image.cols,CV_8UC1,Scalar(0));
		int i,j;
		for(i=0;i<image.rows;i++)
			{
				for(j=1;j<image.cols;j++)
					{
						if((uchar)(image.at<Vec3b>(i,j)[0]*0.56+image.at<Vec3b>(i,j)[1]*0.33+image.at<Vec3b>(i,j)[2]*0.11)>threshold) binary.at<uchar>(i,j)=255;
					}
			}
		return binary;
}

Mat display_hough(Mat image,int threshold)
{
	int i,j,theta,max=-1;
	int maxi,maxj,y;
	double radians;
	long int r_max=2*sqrt(image.rows*image.rows+image.cols*image.cols) +20,r;
	// cout<<" rows and cols are "<<image.rows<<" and "<<image.cols<<endl;
	// cout<<" r max is "<<r_max<<endl;

	//*************initialising accumulator***********************//
	int **hough=new int*[((int)r_max)*(sizeof(int *))];
	for(i=0;i<r_max;i++)
	{
		hough[i]=new int[180*sizeof(int)];
		for(j=0;j<180;j++)
			{
				 hough[i][j]=0;
			}	 
	}
	//***************************Calculating accumulator values**********************************//
	for(i=0;i<image.rows;i++)
	{
		for(j=0;j<image.cols;j++)
		{
			if(image.at<uchar>(i,j)==255)
			{
				for(theta=0;theta<180;theta++)
				{
					radians= (theta*CV_PI)/180.0;
					r=(int)(i*sin(radians)+j*cos(radians));
					//cout<<" r is "<<r<<endl;
					hough[(r_max/2+r)][theta]++;
				}
			}
		}
	}
	//*****************************Displaying hough domain*********************//
	Mat out(r_max,180,CV_8UC1,Scalar(0));

	for(i=0;i<r_max;i++) //finding max value of r and theta
	{
		for(j=0;j<180;j++)
		{
			if(hough[i][j]>max)
			{
				max=hough[i][j];
			}
		}
	}

	for(i=0;i<out.rows;i++)
		{
			for(j=0;j<out.cols;j++)
			{
				if(hough[i][j]!=0)
				{
					out.at<uchar>(i,j)=(int)(hough[i][j]*255/max);
				}
			}
		}

	namedWindow("domain",WINDOW_NORMAL);
	imshow("domain",out);
	
	//********************Finding r and theta greater than threshold**************************
	Mat lines(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(i=0;i<r_max;i++) //finding max value of r and theta
	{
		for(j=0;j<180;j++)
		{
			if(hough[i][j]>threshold)
			{
				theta=j;
				r=i-r_max/2;				
				int x;
				if(theta!=0)
				{
						for(x=0;x<lines.cols;x++)
						{	
							radians= (theta*CV_PI)/180.0;
							y=(int)(r-(x*cos(radians)))/(sin(radians));
							if(y>0&&y<image.rows&&image.at<uchar>((int)y,x)>0)lines.at<uchar>(y,x)=255;
						}
						
				}
					else if(theta==0)
					{
							for(x=0;x<image.rows;x++)
							{
								lines.at<uchar>(x,r)==255;
							}
					}				
			}
		}
	}
	return lines;
}


void hough_line_detector_trackbar(Mat image)
{
	int threshold=53,a;
	namedWindow("Lines",WINDOW_NORMAL);
	Mat out;
	createTrackbar("Threshold","Lines",&threshold,500);
	while(1)
	{
		
		out=display_hough(image,threshold);
		imshow("Lines",out);
		a=waitKey(33);
		if(a==27)break;
	}
}
int main()
{
	Mat image=convert_to_binary(imread("lines.png"));
	namedWindow("source",WINDOW_AUTOSIZE);
	imshow("source",image);
	waitKey(0);
	hough_line_detector_trackbar(image);
	return 0;
}