// ConsoleApplication2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<queue>
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
Mat Grayscale(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	Mat img3(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	int av;
	int i, j;

	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			img2.at<uchar>(i, j) = img1.at < Vec3b>(i, j)[0] * 0.55 + img1.at < Vec3b>(i, j)[1] * 0.33 + img1.at < Vec3b>(i, j)[2] * 0.11;
			
		}
	}

	//namedWindow("sonal", WINDOW_AUTOSIZE);
	//imshow("sonal", img2);
return img2;
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
			if (img1.at<uchar>(i, j)<x)
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
Mat prewett(Mat img1)
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
Mat identifyingHSV(Mat img1, int hue/*,int sat,int light*/)
{
	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int av;
	int i, j;

	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			if ((img1.at<Vec3b>(i, j)[0]<hue + 128) && (img1.at<Vec3b>(i, j)[0]> 128 - hue))
				img3.at<uchar>(i, j) = 255;
			//if ((img1.at<Vec3b>(i, j)[1]<sat + 128) && (img1.at<Vec3b>(i, j)[1]> 128 - sat))
			//img3.at<uchar>(i, j) = 255;
			//if ((img1.at<Vec3b>(i, j)[2]<light + 128) && (img1.at<Vec3b>(i, j)[2]> 128 - light))
			//img3.at<uchar>(i, j) = 255;
		}
	}

	/*namedWindow("sonal", WINDOW_AUTOSIZE);
	imshow("sonal", img3);*/
	return img3;
}
Mat searchforcontinuity(int a, int b, Mat img1, Mat img2,int x)
{
	queue<Point> q;
	Point temp(a, b);
	q.push(temp);
	img2.at<schar>(a, b) = 0;
	while (1)
	{
		cout << "break1"<<endl;
		for (int i = a - 1; i < a + 2; i++)
		{
			for (int j = b - 1; j < b + 2; j++)
			{
				if ((img1.at<uchar>(i ,j) == 255) && (img1.at<uchar>(i, j)==-1))
				{
					Point temp2(i, j);
					q.push(temp2);
					img2.at<schar>(i, j) = 0;
					cout << "break2"<<endl;
				}
			}
		}
		img2.at<schar>(a, b) = x;
		q.pop();
		
		if (q.empty())break;
		cout << "break3"<<endl;
		Point n = q.front();
		a = n.x;
		b = n.y;
	}
	cout << "break4"<<endl;
	return img2;
}

void printblob(Mat img1, int x)
{

	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0));
	int counter = 0;
	for (int h = 0; h < img1.rows; h++)
	{
		for (int n = 0; n < img1.cols; n++)
		{
			if (img1.at<schar>(h, n) == x)
			{
				img2.at<uchar>(h, n) = 255;
				cout << "break5 " << counter << endl;
				counter++;
			}
			
		}
	}
	namedWindow("blob", WINDOW_AUTOSIZE);
	imshow("blob", img2);
	waitKey(0);
}

Mat blobdetect(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8SC1, Scalar(-1));
	int i = 0, j = 0;	
	int px = 1;
	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			if ((img1.at<uchar>(i, j) == 255) && (img1.at<uchar>(i, j) == -1))
			{
				img2 = searchforcontinuity(i, j, img1, img2, px);
			}
			
			px++;
		}
	}
	printblob(img2, px);
	return img2;
}

Point linedetect(Mat img1)
{
	int k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	int rmx, thetamx = 180;
	rmx = sqrt(pow(img1.rows, 2) + pow(img1.cols,2));

	int r = 0, theta = 0;
	int **a;
	a = (int**)malloc(rmx*sizeof(int*));
	for (int i = 0; i < rmx; i++)
	{
		a[i] = (int*)malloc(thetamx*sizeof(int));
		for (int j = 0; j < thetamx; j++)
			a[i][j] = 0;
		//cout << thetamx;
	}

	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((img1.at<uchar>(i, j) == 255) )
			{
				for (theta = 0; theta < 180;theta++)
				{
					r = abs((int)(j*(cos((theta*3.14) / 180)) + i*(sin((theta*3.14) / 180))));
					a[r][theta]++;
					//cout << "thetamx1";
				}
			}
		}
				
	}

	cout << ":P";
	int max = 0;
	int imax = 0;
	int jmax = 0;
	for (int i = 0; i < rmx; i++)
	{
		for (int j = 0; j < thetamx; j++)
		{
			if (a[i][j]>max)
			{
				max = a[i][j]; cout << i << j;
				imax = i;
				jmax = j;
			}
		}
	}
	Point p;
	p.x = imax;
	p.y = jmax;
		return(p);
}
	int main()
	{
		Mat img1;
		img1 = imread("linedetect.png", CV_LOAD_IMAGE_GRAYSCALE);
		Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
		Point line=linedetect(img1);
		cout << line.x << line.y;
		double w = line.x;
		double u = line.y;
		for (int i = 0; i < img2.rows; i++)
		{
			int y =(int)( (w - i*cos(u*3.14/180) / sin(u*3.14/180)));
			img2.at<uchar>(i,y) = 255;
			cout << i << y;
		}
		namedWindow("s", WINDOW_AUTOSIZE);
		imshow("s", img2);
		waitKey(0);
		/*Mat img1;
		img1 = imread("blodetect.png", CV_LOAD_IMAGE_GRAYSCALE);
		Mat img2=blobdetect(img1);*/
		/*Mat img1;
		img1 = imread("Untitled.png", CV_LOAD_IMAGE_COLOR);
		int hue = 16; int x = 10,sat=10,light=0;
		namedWindow("tol", WINDOW_AUTOSIZE);
		createTrackbar("value", "tol", &hue, 255);
		createTrackbar("value", "tol", &sat, 255);
		createTrackbar("value", "tol", &light, 255);
		while (1)
		{
			Mat img2;
/			cvtColor(img1, img2, CV_BGR2HLS);
			Mat img3 = identifyingHSV(img2, hue,sat,light);
			imshow("tol", img3);
			char a = waitKey(2);
			if (a == 27)break;
		}*/
		/*Mat img1;
		img1=imread("Untitled.png", CV_LOAD_IMAGE_COLOR);
		int hue = 16; int x = 10;
		namedWindow("tol", WINDOW_AUTOSIZE);
		createTrackbar("value", "tol", &hue, 255);
		while (1)
		{
			Mat img2;
			cvtColor(img1, img2, CV_BGR2HSV);
			Mat img3 = identifyingHSV(img2, hue);
			imshow("tol", img3);
			char a = waitKey(2);
			if (a == 27)break;
		}*/
		/*VideoCapture v(0);
		int x = 10;
		namedWindow("new", WINDOW_AUTOSIZE);
		createTrackbar("value", "new", &x, 255);
		while (1)
		{
			Mat frame;
			v >> frame;
			Mat gimg=Grayscale(frame);
			//cvtColor(frame, gimg, CV_BGR2GRAY);
			gimg = prewett(gimg);
			Mat bing = edge(gimg, x);
			imshow("new", gimg);
			char a = waitKey(2);
			if (a == 27)break;
		}*/
		//Mat img;
		/*int x = 10;
		namedWindow("changing", WINDOW_AUTOSIZE);
		createTrackbar("value", "changing", &x, 255);*/
		//img = imread("k.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	 //avgborder(img);
		//median(img);
		//gauss(img);
		//namedWindow("s", WINDOW_AUTOSIZE);
		//imshow("s", img); int in = 0, up = 0;
		//createTrackbar("1", "s", &in, 255);
		//createTrackbar("2", "s", &up, 255);
		/*while (1)
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

		}*/
		//Mat img2 =prewett(img);
		//img2 = prewett(img2);
	//Mat img2=edge(bing);
		//invert();
		//histo();
	/*namedWindow("s", WINDOW_AUTOSIZE);
	imshow("s", img2);*/
		
		return 0;
	}