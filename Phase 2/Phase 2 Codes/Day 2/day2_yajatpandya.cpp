#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int q, r;
Mat gray(Mat z)
{
	Mat img(z.rows, z.cols, CV_8UC1);
	int a, b;
	for (a = 0; a < z.rows; a++)
	{
		for (b = 0; b < z.cols; b++)
		{
			img.at<uchar>(a, b) = 0.56*z.at<Vec3b>(a, b)[0] + 0.33*z.at<Vec3b>(a, b)[1] + 0.11*z.at<Vec3b>(a, b)[2];
		}
	}
	return img;
}
Mat bin(Mat z,int q)
{
	Mat i(z.rows, z.cols, CV_8UC1);
	int a, b;
	for (a = 0; a < z.rows; a++)
	{
		for (b = 0; b < z.cols; b++)
		{
			if (z.at<uchar>(a, b)>q) i.at<uchar>(a, b) = 255;
			else i.at<uchar>(a, b) = 0;
		}
	}
	return i;
}
/**Mat inv(Mat z)
{
	Mat i = z;
	int a, b; unsigned char q;
	for (a = 0; a < (i.rows)/2; a++)
	{
		for (b = 0; b < i.cols; b++)
		{
			q = i.at<uchar>(i.rows - a-1, b);
			i.at<uchar>(i.rows - a-1, b) = i.at<uchar>(i.rows, b);
			i.at<uchar>(i.rows, b) = q;
		}
	}
	return i;
}**/
Mat holo(Mat image)
{
	int f[256], max;
	int a, b;
	for (a = 0; a < 256; a++)
		f[a] = 0;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			f[image.at<uchar>(a, b)]++;
		}
	}
	max = f[0];
	for (a = 0; a < 256; a++)
	{
		if (f[a]>max)
			max = f[a];
	}
	Mat i((max + 1), 255, CV_8UC1, Scalar(255));
	for (b = 0; b < 255; b++)
	{
		for (a = i.rows - 1; a >= i.rows - (f[b]); a--)
			i.at<uchar>(a, b) = 0;
	}
	return i;
}
Mat holo_im(Mat image)
{	
	int f[256], max;
	int a, b;
	for (a = 0; a < 256; a++)
		f[a] = 0;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			f[image.at<uchar>(a, b)]++;
		}
	}
	int p = 0;
	for (a = 0; a < 256; a++)
	{
		p += f[a];
		if (p >= image.rows*image.cols / 2) break;
	}
	p = a;
	Mat i=image = bin(image, p);
	return i;
}
Mat blue(Mat image,int p)
{
	Mat i(image.rows, image.cols, CV_8UC3);
	int a, b;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			i = image;
			i.at<Vec3b>(a, b)[0]=p;
		}
	}
	return i;
}
Mat red(Mat image, int p)
{
	Mat i(image.rows, image.cols, CV_8UC3);
	int a, b;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			i = image;
			i.at<Vec3b>(a, b)[1] = p;
		}
	}
	return i;
}
/**Mat green(Mat image, int p)
{
	Mat i(image.rows, image.cols, CV_8UC3);
	int a, b;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			i = image;
			i.at<Vec3b>(a, b)[2] = p;
		}
	}
	return i;
}**/

int main()
  {
	  Mat image=imread("C:\\Users\\Yajat\\Desktop\\z.jpg",CV_LOAD_IMAGE_COLOR);
	  int x=0,y=0,z=0,w=0;
	  //image = gray(image);
	  namedWindow("Yajat", CV_WINDOW_NORMAL);
	  createTrackbar("blue", "Yajat", &x, 255);
	  createTrackbar("red", "Yajat", &y, 255);
	  createTrackbar("green", "Yajat", &z, 255);
	  createTrackbar("thres", "Yajat", &w, 255);
	  while (1)
	  {
		  Mat bimg = blue(image,x);
		  bimg = red(image, y);
		  //bimg = green(image, z);
		  //bimg=thres(image,w);//First convert to binary
		  imshow("Yajat", bimg);
		  char a=waitKey(33);
		  if (a >= 27) break;
	  }
	  return 0;
	 // a = bin(a);
	  //a = inv(a);
	  //image = imread("C:\\Users\\Yajat\\Desktop\\z.jpg",0);
	  //image.at<Vec3b>(111, 111)[0] = 199;
	  //for (int i = 0; i < 8; i++)
	  /**{
		  for (int j = 0; j < 10; j++)
		  {
			  if ((i + j) % 3 == 0)
			  {
				  for (int a = image.rows*i / 8; a < image.rows*(i + 1) / 8; a++)
				  {
					  for (int b = image.cols*j / 10; b < image.cols*(j + 1) / 10; b++)
					  {
						  image.at<Vec3b>(a,b)[0] = 0;
						  image.at<Vec3b>(a,b)[1] = 0;
					  }
				  }
			  }
			  else if ((i+j)%3==1){
				  for (int a = image.rows*i / 8; a < image.rows*(i + 1) / 8; a++)
				  {
					  for (int b = image.cols*j / 10; b < image.cols*(j + 1) / 10; b++)
					  {
						  image.at<Vec3b>(a, b)[2] = 0;
						  image.at<Vec3b>(a, b)[1] = 0;
					  }
				  }
			  }
			  else 
			  {
				  for (a = image.rows*i / 8; a < image.rows*(i + 1) / 8; a++)
				  {
					  for (b = image.cols*j / 10; b < image.cols*(j + 1) / 10; b++)
					  {
						  image.at<Vec3b>(a, b)[0] = 0;
						  image.at<Vec3b>(a, b)[2] = 0;
					  }
				  }
			  }
		  }
	  }**/
	  /**for (int i = 0; i < image.rows; i++)
	  {
		  for (int j = 0; j < image.cols; j++)
		  {if (image.at<uchar>(i, j)>127) image.at<uchar>(i, j)--;
		  else image.at<uchar>(i, j)++;
	  }
	  }**/
	  
  }