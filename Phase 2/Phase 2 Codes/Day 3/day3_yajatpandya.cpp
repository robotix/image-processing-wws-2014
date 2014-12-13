#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>
#include<opencv2/imgproc/imgproc.hpp>
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
			img.at<uchar>(a, b) =(uchar)(0.56*z.at<Vec3b>(a, b)[0] + 0.33*z.at<Vec3b>(a, b)[1] + 0.11*z.at<Vec3b>(a, b)[2]);
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
	int f[256];
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
Mat compl(Mat image, int p,int q,int r)
{
	Mat i(image.rows, image.cols, CV_8UC3);
	int a, b;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			if ((image.at<Vec3b>(a, b)[0] + p-255)>255) i.at<Vec3b>(a, b)[0] = 255;
			else if ((image.at<Vec3b>(a, b)[0] + p-255) < 0) i.at<Vec3b>(a, b)[0] = 0;
			else i.at<Vec3b>(a, b)[0] = image.at<Vec3b>(a,b)[0]+p-255;
			if ((image.at<Vec3b>(a, b)[1] + q-255)>255) i.at<Vec3b>(a, b)[1] = 255;
			else if ((image.at<Vec3b>(a, b)[1] + q-255) < 0) i.at<Vec3b>(a, b)[1] = 0;
			else i.at<Vec3b>(a, b)[1] = image.at<Vec3b>(a, b)[1] + q-255;
			if ((image.at<Vec3b>(a, b)[2] + r-255)>255) i.at<Vec3b>(a, b)[2] = 255;
			else if ((image.at<Vec3b>(a, b)[2] + r-255) < 0) i.at<Vec3b>(a, b)[2] = 0;
			else i.at<Vec3b>(a, b)[2] = image.at<Vec3b>(a, b)[2] + r-255;
			/**if ((image.at<Vec3b>(a, b)[0] + p) < 0) i.at<Vec3b>(a, b)[0] = 0;
			else i.at<Vec3b>(a, b)[0] = image.at<Vec3b>(a, b)[0] + p;
			if ((image.at<Vec3b>(a, b)[1] + q) < 0) i.at<Vec3b>(a, b)[1] = 0;
			else i.at<Vec3b>(a, b)[1] = image.at<Vec3b>(a, b)[1] + q;
			if ((image.at<Vec3b>(a, b)[2] + r) < 0) i.at<Vec3b>(a, b)[2] = 0;
			else i.at<Vec3b>(a, b)[2] = image.at<Vec3b>(a, b)[2] + r;**/
		}
	}
	return i;
}
Mat outl(Mat image,int t)
{
	Mat im = gray(image);
	int i,j,a,b,min,max;
	Mat im2(image.rows, image.cols, CV_8UC1);
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			if (a == image.rows - 1 || a == 0 || b == image.cols - 1 || b == 0)
			{
				im2.at<uchar>(a, b) = 0; continue;
			}
			max = min = im.at<uchar>(a - 1, b - 1);
			for (i =(a - 1); i <(a + 2); i++)
			{
				for (j =(b - 1); j <(b + 2); j++)
				{
					if (im.at<uchar>(i, j) > max) max = im.at<uchar>(i, j);
					if (im.at<uchar>(i, j) <= min) min = im.at<uchar>(i, j);
				}
			}
			if ((max - min)>t) im2.at<uchar>(a, b) = 255;
			else im2.at<uchar>(a, b) = 0;
		}
	}
	return im2;
}
Mat outl2(Mat image)
{
	int a, b, x=0, y=0;
	Mat i = gray(image), im(image.rows,image.cols,CV_8UC1);
	for (a = 1; a < i.rows - 1; a++)
	{
		for (b = 1; b < i.cols - 1; b++)
		{
			x = i.at<uchar>(a - 1, b + 1) + i.at<uchar>(a, b + 1) + i.at<uchar>(a + 1, b + 1) - i.at<uchar>(a - 1, b - 1) - i.at<uchar>(a, b - 1) - i.at<uchar>(a + 1, b - 1);
			y = i.at<uchar>(a + 1, b + 1) + i.at<uchar>(a+1, b) + i.at<uchar>(a + 1, b - 1) - i.at<uchar>(a - 1, b - 1) - i.at<uchar>(a-1, b) - i.at<uchar>(a - 1, b + 1);
			im.at<uchar>(a, b) = sqrt((x*x) + (y*y));
		}
	}
	return im;
}
Mat dilute(Mat image)
{
	int i, j, a, b, wh, bl;
	Mat im2(image.rows, image.cols, CV_8UC1);
	for (a = 1; a < image.rows-1; a++)
	{
		for (b = 1; b < image.cols-1; b++)
		{
			/**if (a == image.rows - 1 || a == 0 || b == image.cols - 1 || b == 0)
			{
				im2.at<uchar>(a, b) = 0; continue;
			}**/
			wh=bl=0;
			for (i = (a - 1); i <(a + 2); i++)
			{
				for (j = (b - 1); j <(b + 2); j++)
				{
					if (image.at<uchar>(i, j) == 255) wh++;
					else bl++;
				}
			}
			if (wh>bl) im2.at<uchar>(a, b) = 255;
			else im2.at<uchar>(a, b) = 0;
		}
	}
	return im2;
}
Mat erosion(Mat image)
{
	int i, j, a, b, wh, bl;
	Mat im2(image.rows, image.cols, CV_8UC1);
	for (a = 1; a < image.rows - 1; a++)
	{
		for (b = 1; b < image.cols - 1; b++)
		{
			/**if (a == image.rows - 1 || a == 0 || b == image.cols - 1 || b == 0)
			{
			im2.at<uchar>(a, b) = 0; continue;
			}**/
			wh = bl = 0;
			for (i = (a - 1); i < (a + 2); i++)
			{
				for (j = (b - 1); j <(b + 2); j++)
				{
					if (image.at<uchar>(i, j) == 255) wh++;
					else bl++;
				}
			}
			if (wh>bl && bl != 0) im2.at<uchar>(a, b) = 0;
			else if (wh<bl && wh != 0) im2.at<uchar>(a, b) = 255;
			else if (wh>bl && bl == 0) im2.at<uchar>(a, b) = image.at<uchar>(a, b);
			else if (wh < bl && wh == 0) im2.at<uchar>(a, b) = image.at<uchar>(a, b);
		}
	}
	return im2;
}
Mat meanfil(Mat img)
{
	Mat im;
	img.copyTo(im);
	int a, b, i, j, s;
	for (a = 1; a < im.rows - 1; a++)
	{
		for (b = 0; b < im.cols - 1; b++) 
		{
			s = 0;
			for (i = a - 3; i < a + 4; i++)
			{
				for (j = b - 3; j < b + 4; j++)
				{

					s += img.at<uchar>(i, j);
				}
			}
			im.at<uchar>(a, b) = s / 49;
		}
	}
	return im;
}
Mat medianfil(Mat img)
{
	Mat im;
	img.copyTo(im);
	int a, b, i, j, s[9],k,l,m,min,n;
	for (a = 1; a < im.rows - 1; a++)
	{
		for (b = 0; b < im.cols - 1; b++)
		{
			for (i = 0; i < 9; i++) s[i] = 0; k = 0;
			for (i = a - 1; i < a + 2; i++)
			{
				for (j = b - 1; j < b + 2; j++,k++)
				{

					s[k]= img.at<uchar>(i, j);
				}
			}
			for (l = 0; l < 8; l++)
			{
				min = s[l]; n = l;
				for (m = l + 1; m < 9 ; m++)
				{
					if (min>s[m]) {
						min = s[m]; n = m;
					}
				}
				k = s[l];
				s[l] = min;
				s[n] = k;
			}
			im.at<uchar>(a, b) = s[4];
		}
	}
	return im;
}
Mat gaussfil(Mat img)
{
	Mat im;
	img.copyTo(im);
	int a, b;
	for (a = 1; a < im.rows - 1; a++)
	{
		for (b = 0; b < im.cols - 1; b++)
		{
			im.at<uchar>(a, b) = (0.06*(int)(im.at<uchar>(a - 1, b - 1) + im.at<uchar>(a - 1, b + 1) + im.at<uchar>(a + 1, b - 1) + im.at<uchar>(a + 1, b + 1)) + 0.098*(int)(im.at<uchar>(a , b - 1) + im.at<uchar>(a , b + 1) + im.at<uchar>(a + 1, b) + im.at<uchar>(a - 1, b)) +0.162*im.at<uchar>(a,b))/0.794 ;
		}
	}
	return im;
}
int main()
  {
	  Mat image=imread("C:\\Users\\Yajat\\Desktop\\i.jpg",CV_LOAD_IMAGE_COLOR);
	  //int x=255,y=255,z=255,w=0;
	  image = gray(image);
	  int p=0,q=0;
	  namedWindow("Yajat", CV_WINDOW_AUTOSIZE);
	  imshow("Yajat", image);
	  waitKey(0);
	  namedWindow("mean", CV_WINDOW_AUTOSIZE);
	  imshow("mean", meanfil(image));
	  waitKey(0);
	  namedWindow("median", CV_WINDOW_AUTOSIZE);
	  imshow("median", medianfil(image));
	  waitKey(0);
	  namedWindow("gauss", CV_WINDOW_AUTOSIZE);
	  imshow("gauss",gaussfil(image));
	  waitKey(0);
	  namedWindow("canny", CV_WINDOW_AUTOSIZE);
	  
	  //waitKey(0);
	  //createTrackbar("thres", "Yajat", &x, 255);
	  //imshow("Yajat", outl(image,thres));
	  //createTrackbar("blue", "Yajat", &x,510);
	  //createTrackbar("red", "Yajat", &z,510);
	  //createTrackbar("green", "Yajat", &y,510);
	  //createTrackbar("thres", "Yajat", &w, 255);
	  createTrackbar("m1", "canny", &p, 255);
	  createTrackbar("m2", "canny", &q, 255);
	  Mat im(image.rows,image.cols,CV_8UC1);
	  while (1)
	  {
		  /**Mat bimg = compl(image,x,y,z);
		  //bimg = red(image,y);
		  //bimg = green(image,z);
		  //bimg=thres(image,w);//First convert to binary
		  imshow("Yajat",bimg);**/
		  /**imshow("Yajat", outl(image,x));
		  imshow("Yajat1", dilute(outl(image, x)));
		  imshow("Yajat2", erosion(dilute(outl(image, x))));**/
		  Canny(image, im, p, q, 3);
		  imshow("canny", im);
		  char a=waitKey(33);
		  if (a >= 27) break;
	  }
	  return 0;
	 
  }