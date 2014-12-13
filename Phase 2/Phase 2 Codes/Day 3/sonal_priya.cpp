#include "stdafx.h"
#include<stdio.h>
#include<math.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include<Windows.h>
#include<iostream>
using namespace std;
using namespace cv;




void makeflag()
{
	Mat img(132, 999, CV_8UC3, Scalar(255, 255, 255));
	
	for (int i = 0; i < 132; i++)
	{
		for (int j = 0; j < 999; j++)
		{
			if (i < 44)
			{
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 165;
				img.at<Vec3b>(i, j)[2] = 255;
			}
			else if ((i > 44) && (i < 88))
			{
				img.at<Vec3b>(i, j)[0] = 255;
				img.at<Vec3b>(i, j)[1] = 255;
				img.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 255;
				img.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	namedWindow("sonal", WINDOW_AUTOSIZE);
	imshow("sonal", img);
}
Mat bin(Mat img1,int x)
{
	Mat img2(img1.rows,img1.cols,CV_8UC3,Scalar(0,0,0));
	Mat img3(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	int av;
	int i , j ;

	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			//img2.at<uchar>(i, j) = img1.at < Vec3b>(i, j)[0] * 0.55 + img1.at < Vec3b>(i, j)[1] * 0.33 + img1.at < Vec3b>(i, j)[2] * 0.11;
			if (img1.at<uchar>(i, j)>x)
			{
				img3.at<uchar>(i, j) = 0;
			}
			else
			{
				img3.at<uchar>(i, j) = 255;
			}
		}
	}


	/*namedWindow("sonal", WINDOW_AUTOSIZE);
	imshow("sonal", img3);*/
	return img3;
}
void invert()
{
	Mat img1 = imread("haha.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	int i, j,k=0,m=0;
	for (i = 0, k = img1.rows-1; (i < img1.rows)&&(k>=0); k--, i++)
	{
		for (j = 0; j < img1.cols ; j++)
		{
			//for (m = 0; m < 3; m++)
			
				img2.at<Vec3b>(i, j)[0] = img1.at<Vec3b>(k, j)[0];
				img2.at<Vec3b>(i, j)[1] = img1.at<Vec3b>(k, j)[1];
				img2.at<Vec3b>(i, j)[2] = img1.at<Vec3b>(k, j)[2];
			
		}
	}
	namedWindow("sonal", WINDOW_AUTOSIZE);
	imshow("sonal", img2);
}
void histo()
{
	Mat img1;
	img1 = imread("haha.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2(500, 256, CV_8UC1, Scalar(255));
	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int i, j, k = 0, m = 0;
	int a[256];
	for (i = 0; i < 256; i++) a[i] = 0;
	int n;
	int sum = 0, s = 0;
	int t;
	for (k = 0; k < 256; k++)
	{
		for (i = 0; i < img1.rows; i++)
		{
			for (j = 0; j < img1.cols; j++)
			{
				if (img1.at<uchar>(i, j) == k)
					a[k]++;

			}
		}
	}
	for (i = 0; i < 256; i++)
	{
		a[i] /= 50;
		sum += a[i];
	}
	
	
		for (j = 0; j < img2.cols; j++)
		{
			for (i = img2.rows - 1; img2.rows - i <= a[j];i--)
			{
			img2.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("histo",WINDOW_AUTOSIZE);
	imshow("histo", img2);

	for (i = 0; i < 256; i++)
	{

			s+=a[i]++;
			if (s >= sum / 2)
				break;
			else
				continue;
	}
	m = i;
	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			
			if (img1.at<uchar>(i, j)>m)
			{
				img3.at<uchar>(i, j) = 0;
			}
			else
			{
				img3.at<uchar>(i, j) = 255;
			}
		}
	}
	namedWindow("pic", WINDOW_AUTOSIZE);
	imshow("pic",img3);
	
	}
Mat newedge(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	int dx = 0, dy = 0;
	for (h = 1; h < img1.rows-1; h++)
	{
		for (n = 1; n < img1.cols-1; n++)
		{
			for (i = -1; i < 2; i++)
			{
				dx = 0; dy = 0;
				for (j = -1; j<2; j++)
				{
					dx+= img1.at<uchar>(i + h, j + n)*i;
					dy+= img1.at<uchar>(i + h, j + n)*j;
				}
			}
			d = sqrt(dx*dx + dy*dy);
			img2.at<uchar>(h, n) = d;
			
		}
	}
	return(img2);

}

Mat edge(Mat img1,int x)
{
	int a[9];
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	//cout << "enter the value of threshold";
	//cin >> px;
	for (h = 0; h < img1.rows; h++)
	{
		for (n = 0; n < img1.cols; n++)
		{
			if ((h == 0) || (h == img1.rows - 1) || (n == 0) || (n == img1.cols - 1)) continue;
			max = img1.at<uchar>(h-1,n-1);
			min = img1.at<uchar>(h - 1, n - 1);
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2;j++)
				{
					if (img1.at<uchar>(i + h, j + n)>max)max = img1.at<uchar>(i + h, j + n);
					if (img1.at<uchar>(i + h, j + n)<min)min = img1.at<uchar>(i + h, j + n);
				}
			}
			if ((max - min)>x)

				img2.at<uchar>(h, n) = 255;
			else
				img2.at<uchar>(h, n) = 0;
		}
	}
	return(img2);

}
Mat erode(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows - 1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			max = img1.at<uchar>(h - 1, n - 1);
			min = img1.at<uchar>(h - 1, n - 1);
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2; j++)
				{
					if (img1.at<uchar>(i + h, j + n)>max)max = img1.at<uchar>(i + h, j + n);
					if (img1.at<uchar>(i + h, j + n) < min)min = img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h, n) = min;
		}
	}
	return(img2);
}
Mat dilate(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows-1; h++)
	{
		for (n = 1; n < img1.cols-1; n++)
		{
			max = img1.at<uchar>(h - 1, n - 1);
			min = img1.at<uchar>(h - 1, n - 1);
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2; j++)
				{
					if (img1.at<uchar>(i + h, j + n)>max)max = img1.at<uchar>(i + h, j + n);
					if (img1.at<uchar>(i + h, j + n) < min)min = img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h, n) = max;
		}
	}
	return(img2);
}
void avgborder(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int i = 0, j = 0, k = 0, m = 0,sum=0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows -1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			sum = 0;
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2; j++)
				{
					sum = sum+img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h,n) = sum / 9;
		}
	}
	namedWindow("sp", WINDOW_AUTOSIZE);
	imshow("sp", img2);

}
void median(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, l = 0, m = 0, sum = 0;
	int px = 0, h = 0, n = 0, d = 0;
	int a[9];
	for (h = 1; h < img1.rows - 1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			m = 0;
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j < 2; j++)
				{
					a[m++] = img1.at<uchar>(i + h, j + n);
				}
			}
			for (int f = 7; f >=0; f--)
			{
				for (l = 0; l <=f; l++)
				{
					if (a[l] > a[l + 1])
					{
						px = a[l];
						a[l] = a[l + 1];
						a[l + 1] = px;
					}
				}
			}
			img2.at<uchar>( h, n) = a[4];
		}
	}
	namedWindow("si", WINDOW_AUTOSIZE);
	imshow("si", img2);
}
void gauss(Mat img1)
{ 
	float a[9] = { 0.06, 0.098, 0.06, 0.098, 0.162, 0.098, 0.06, 0.098, 0.06 };
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, l = 0, m = 0, sum = 0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows - 1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			m = 0; sum = 0;
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j < 2; j++)
				{
					sum += a[m++] * img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h,n) = sum;
		}
	}
	namedWindow("s", WINDOW_AUTOSIZE);
	imshow("s", img2);

}

	int main()
	{
		Mat img;
		/*int x = 10;
		namedWindow("changing", WINDOW_AUTOSIZE);
		createTrackbar("value", "changing", &x, 255);*/
		img = imread("k.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	 //avgborder(img);
		//median(img);
		//gauss(img);
		namedWindow("s", WINDOW_AUTOSIZE);
		imshow("s", img); int in = 0, up = 0;
		createTrackbar("1", "s", &in, 255);
		createTrackbar("2", "s", &up, 255);
		while (1)
		{
			Mat img1;
			Canny(img, img1, in, up, 3);
			imshow("s", img1);
			//Mat bing = edge(img,x);
			//bing = dilate(bing);
			//bing = erode(bing);
			//imshow("changing", bing);
				char a = waitKey(33);
			if (a == 27)break;

		}
		//Mat img2 =newedge(img);
		//img2 = newedge(img2);
	//Mat img2=edge(bing);
		//invert();
		//histo();
	/*namedWindow("s", WINDOW_AUTOSIZE);
	imshow("s", img2);*/
		waitKey(0);
		return 0;
	}