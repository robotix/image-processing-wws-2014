// opencv_9th_2st.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int f[256];
int k = 0;


Mat image;

Mat make_grayscale(Mat picture)
{
	Mat img2(image.rows,image.cols,CV_8UC1);

	for (int i = 0; i<image.rows;i++)
	{
		for(int j = 0; j<image.cols;j++)
		{
		
			img2.at<uchar>(i,j) = image.at<Vec3b>(i,j)[0]*0.56 + image.at<Vec3b>(i,j)[1]*0.33 + image.at<Vec3b>(i,j)[2]*0.11;
		}
	}
	return img2;
}

Mat make_binary(Mat picture,int threshold)
{
	Mat img2(image.rows,image.cols,CV_8UC1);

	for (int i = 0; i<image.rows;i++)
	{
		for(int j = 0; j<image.cols;j++)
		{
		
			img2.at<uchar>(i,j) = image.at<Vec3b>(i,j)[0]*0.56 + image.at<Vec3b>(i,j)[1]*0.33 + image.at<Vec3b>(i,j)[2]*0.11;
			if(img2.at<uchar>(i,j)>threshold)
			{
				img2.at<uchar>(i,j) = 255;
			}

			else
			{
				img2.at<uchar>(i,j) = 0;
			}
		}
	}
	return img2;
}

Mat invert(Mat picture,int x = 0,int y = 0) // make x or y 1 to flip on that axis
{
	Mat img2(picture.rows,picture.cols,CV_8UC3);

	for (int i = 0; i<picture.rows;i++)
	{
		for(int j = 0; j<picture.cols;j++)
		{
			img2.at<Vec3b>(i,j)[0] = picture.at<Vec3b>(abs(x*(picture.rows-1)-i),abs(y*(picture.cols-1)-j))[0];
			img2.at<Vec3b>(i,j)[1] = picture.at<Vec3b>(abs(x*(picture.rows-1)-i),abs(y*(picture.cols-1)-j))[1];
			img2.at<Vec3b>(i,j)[2] = picture.at<Vec3b>(abs(x*(picture.rows-1)-i),abs(y*(picture.cols-1)-j))[2];
		}
	}
	return img2;
}

Mat threshold(Mat picture)
{
	for (int i = 0; i<picture.rows;i++)
	{
		for(int j = 0; j<picture.cols;j++)
		{
			f[picture.at<uchar>(i,j)]++;
		}
	}
	k = 0;
	int sum = 0;
	int total = 0;
	
	for(int i = 0;i<256;i++)
	{
		if((sum + f[i])<( (picture.cols*picture.rows)/2 ))
		{
			sum = sum + f[i];
			k = i;
		}
		total = total + f[i];
	}
	cout << sum<<endl;
	cout << total/2<<endl;
	cout << ((picture.rows*picture.cols)/2)<<endl;
	cout<<k;

	for(int i = 0; i<picture.rows;i++)
	{
		for(int j = 0; j<picture.cols;j++)
		{
			if(picture.at<uchar>(i,j) > k)
			{
				picture.at<uchar>(i,j) = 255;
			}

			else
			{
				picture.at<uchar>(i,j) = 0;
			}
		}

	}

	return picture;
	
}

Mat histogram(Mat image,int threshold)
{
	int max = 0;
	int im = 0;
	for(int i = 0; i<256;i++)
	{
		f[i] = f[i]/100;
		if(max<f[i])
		{
			max = f[i];
			im = i;
		}
	}

	cout<<endl<<max<<endl<<im;

	Mat img2(max,256,CV_8UC1,Scalar(255));

	for(int j = 0;j<256;j++)
	{
		
		for (int i = 0;i<f[j];i++)
		{	
			if(j==threshold)
			{
				img2.at<uchar>(max-1-i,j) = 122;
			}

			else
			{
				img2.at<uchar>(max-1-i,j) = 0;
			}
			
		}
	}

	return img2;
}


int _tmain(int argc, _TCHAR* argv[])
{

	/* How to call the functions:

	Mat threshold(Mat image);
	Mat histogram(Mat image,int threshold); // threshold is taken to make it appear on the histogram. Call this function only after calling threshold() fuction
	Mat make_binary(image,threshold);
	Mat invert(Mat image, int x, int y); set x or y 1 to flip on that axis
	Mat make_grayscale(image);

	*/


	image = imread("C:\\Users\\acer\\Desktop\\a.jpg",CV_LOAD_IMAGE_GRAYSCALE);	
	imshow("Original Image",image);
	
	Mat a = threshold(image);
	imshow("Binary Image",a);

	image = histogram(image,k);
	//namedWindow("Histogram",WINDOW_AUTOSIZE);
	imshow("Histogram",image);
	waitKey(0);
	return 0;
}