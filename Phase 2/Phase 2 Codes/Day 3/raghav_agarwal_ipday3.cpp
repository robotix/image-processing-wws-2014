#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat convertbin(Mat image1, int threshold)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	for (j = 0; j < image1.rows; j++)
	{
		images.at<uchar>(j, i) = (uchar)(image1.at<Vec3b>(j, i)[0])*0.56 + (image1.at<Vec3b>(j, i)[1])*0.33 + (image1.at<Vec3b>(j, i)[2])*0.11;
		if ((images.at<uchar>(j, i)>threshold))
			images.at<uchar>(j, i) = 255;
		else
			images.at<uchar>(j, i) = 0;
	}
	return images;
}
Mat convertbin1(Mat image1, int threshold)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	{
		for (j = 0; j < image1.rows; j++)
		{

			if ((image1.at<uchar>(j, i)>threshold))
				images.at<uchar>(j, i) = 255;
			else
				images.at<uchar>(j, i) = 0;
		}
	}
	return images;
}
void Trackbar(Mat image)
{
	int x = 10;
	namedWindow("Trackbar1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Trackbar1", &x, 250);
	while (1)
	{
		Mat img = convertbin1(image,x);
		
		imshow("Trackbar1",img);
		char a = waitKey(33);
		if (a==27)
			break;
}	
}
void Trackbar1(Mat image)
{
	int x = 10,y=15;
	int i, j;
	namedWindow("Trackbar1", WINDOW_NORMAL);
	createTrackbar("blueThreshold", "Trackbar1", &x, 100);
	createTrackbar("greenThreshold", "Trackbar1", &y, 100-x);
	while (1)
	{
		Mat img(image.rows, image.cols, CV_8UC1);
		for (i = 0; i < image.cols; i++)
		for (j = 0; j < image.rows; j++)
		{
			img.at<uchar>(j, i) = (uchar)(image.at<Vec3b>(j, i)[0])*x / 100 + (image.at<Vec3b>(j, i)[1])*y / 100 + (image.at<Vec3b>(j, i)[2])*(100 - x - y) / 100;
		}
		imshow("Trackbar1", img);
			char a = waitKey(33);
			if (a == 27)
				break;
		
	}
}
Mat histogram(Mat image1,int * th)
{
	Mat imhist(256, (image1.rows*image1.cols)/1000, CV_8UC1);
	long long int a[256],i,j,sum=0;
	for (i = 0; i < 256; i++)
		a[i] = 0;
	for (i = 0; i < image1.cols; i++)
	for (j = 0; j < image1.rows; j++)
		a[image1.at<uchar>(j, i)]++;
	for (j = 0; j < 256; j++)
	for (i = 0; i < (image1.rows*image1.cols) / 1000; i++)
	{
		if (i < (a[j]/40 ))
			imhist.at<uchar>(j, i) = 0;
		else
			imhist.at<uchar>(j, i) = 255;
	}
	for (i = 0; i < 256; i++)
	{
		sum += a[i];
		if (sum>(image1.rows*image1.cols) / 2)
		{
			*th = i;
			break;
		}
	}

	return imhist;
}

Mat patchmaker()
{
	Mat images(1000,1000,CV_8UC3);
	int i, j;
	for (i = 0; i <1000; i++)
	{
		for (j = 0; j <1000; j++)
		{
			images.at<Vec3b>(j, i)[(i + j) % 3] = 255;
			images.at<Vec3b>(j, i)[(i + j + 1) % 3] = 0;
			images.at<Vec3b>(j, i)[(i + j + 2) % 3] = 0;
		}
	}
	return images;
}
Mat reverse(Mat image1)
{
	Mat images(image1.rows, image1.cols, CV_8UC3);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	{
		for (j = 0; j < image1.rows; j++)
		{
			images.at<Vec3b>(j, image1.cols-i-1)[0] = image1.at<Vec3b>(j, i)[0];
			images.at<Vec3b>(j, image1.cols-i-1)[1] = image1.at<Vec3b>(j, i)[1];
			images.at<Vec3b>(j, image1.cols-i-1)[2] = image1.at<Vec3b>(j, i)[2];
		}
	}
	return images;
}
Mat convert(Mat image1)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	{
		for (j = 0; j < image1.rows; j++)
		{
			images.at<uchar>(j, i) = (image1.at<Vec3b>(j, i)[0] + image1.at<Vec3b>(j, i)[1] + image1.at<Vec3b>(j, i)[2]) / 3;
		}
	}
	return images;
}

Mat convert1(Mat image1)
{
	Mat images(image1.rows, image1.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image1.cols; i++)
	for (j = 0; j < image1.rows; j++)
	images.at<uchar>(j, i) = (uchar)(image1.at<Vec3b>(j, i)[0])*0.56 + (image1.at<Vec3b>(j, i)[1])*0.33 + (image1.at<Vec3b>(j, i)[2])*0.11;
		return images;
}
int findmax(Mat image1, int x, int y)
{
	int i, j,max;
	max = 0;
	for (i = -1; i <= 1;i++)
	for (j = -1; j <= 1;j++)
	if (image1.at<uchar>(x + i, y + j)>max)
		max = image1.at<uchar>(x + i, y + j);
	return max;
}
int findmin(Mat image1, int x, int y)
{
	int i, j, min;
	min = 255;
	for (i = -1; i <= 1; i++)
	for (j = -1; j <= 1; j++)
	if (image1.at<uchar>(x + i, y + j)<min)
		min= image1.at<uchar>(x + i, y + j);
	return min;
}
int nblack(Mat image, int x, int y)
{
	int i, j, n = 0;
	for (i = -1; i <= 1; i++)
	for (j = -1; j <= 1; j++)
	{
	if (image.at<uchar>(x + i, y + j) == 0)
		n++;
}
	return n;

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
	Mat image(image1.rows,image1.cols,CV_8UC1);
	int i, j,nb,nw;
	for (i = 0; i < image1.rows;i++)
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
Mat edgedetection(Mat image1,int th)
{
	int i, j, max, min;
	Mat image(image1.rows, image1.cols, CV_8UC1);
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		if (i == 0 || j == 0 || i == (image.rows - 1) || j == (image.cols - 1))
			image.at<uchar>(i,j) = 0;
		else{
			max = findmax(image1, i,j);
			min = findmin(image1,i,j);
			if (max - min>th) 
				image.at<uchar>(i, j) = 255;
			else
				image.at<uchar>(i, j) = 0;
		}
	}
		return image;
	
}
Mat edgedetection1(Mat image1)
{

	int i, j, x, y, k;
	x = 0;
	y = 0;
	Mat image(image1.rows, image1.cols, CV_8UC1);
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		x = 0;
		y = 0;
		if (i == 0 || j == 0 || i == (image.rows - 1) || j == (image.cols - 1))
			image.at<uchar>(i, j) = 0;
		else
		{
			for (k = -1; k <= 1; k++)
			{
				x += image1.at<uchar>(i + k, j + 1) - image1.at<uchar>(i + k, j - 1);
				y += image1.at<uchar>(i + 1, j + k) - image1.at<uchar>(i - 1, j + k);
			}
			x = sqrt(x*x + y*y);
			if (x < 255)
				image.at<uchar>(i, j) = x;
			else
				image.at<uchar>(i, j) = 255;
		}

	}
	return image;
}
Mat edgedetectionsob(Mat image1)
{

	int i, j, x, y, k;
	x = 0;
	y = 0;
	Mat image(image1.rows, image1.cols, CV_8UC1);
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		x = 0;
		y = 0;
		if (i == 0 || j == 0 || i == (image.rows - 1) || j == (image.cols - 1))
			image.at<uchar>(i, j) = 0;
		else
		{
			for (k = -1; k <= 1; k++)
			{
				if (k != 0){
					x += image1.at<uchar>(i + k, j + 1) - image1.at<uchar>(i + k, j - 1);
					y += image1.at<uchar>(i + 1, j + k) - image1.at<uchar>(i - 1, j + k);
				}
				else
				{
					x += 2*(image1.at<uchar>(i + k, j + 1) - image1.at<uchar>(i + k, j - 1));
					y += 2*(image1.at<uchar>(i + 1, j + k) - image1.at<uchar>(i - 1, j + k));
				}
			}
			x = sqrt(x*x + y*y);
			if (x < 255)
				image.at<uchar>(i, j) = x;
			else
				image.at<uchar>(i, j) = 255;
		}

	}
	return image;
}
Mat smoothavg(Mat image1)
{
	int i, j,k,l,n;
	Mat image(image1.rows, image1.cols, CV_8UC1);
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		n = 0;
		if (i == 0 || j == 0 || i == (image.rows - 1) || j == (image.cols - 1))
			image.at<uchar>(i, j) = 0;
		else{
			for (k = -1; k <= 1; k++)
			for (l = -1; l <= 1; l++)
				n += image1.at<uchar>(i + k, j + l);
		}
		image.at<uchar>(i, j) = n / 9;
	}
	return image;
}
int median(Mat image1, int i, int j)
{
	int a[9], n, k, l;
	n = 0;
	for (k = -1; k <= 1; k++)
	for (l = -1; l <= 1; l++)
		a[n++] = image1.at<uchar>(i + k, j + l);
	sort(a, a + 9);
	return a[4];
}
Mat smoothmedian(Mat image1)
{
	int i, j, k, l, n;
	Mat image(image1.rows, image1.cols, CV_8UC1);
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		if (i == 0 || j == 0 || i == (image.rows - 1) || j == (image.cols - 1))
			image.at<uchar>(i, j) = image1.at<uchar>(i, j);
		else
		{
			image.at<uchar>(i, j) = median(image1, i, j);
		}
	}
	return image;
}
Mat smoothgaussian(Mat image1)
{
	int i, j, k, l, n;
	Mat image(image1.rows, image1.cols, CV_8UC1);
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		n = 0;
		if (i == 0 || j == 0 || i == (image.rows - 1) || j == (image.cols - 1))
			image.at<uchar>(i, j) = 0;
		else{
			for (k = -1; k <= 1; k++)
			for (l = -1; l <= 1; l++)
			{
				if (abs(k) + abs(l) == 2)
					n += 0.06*	image1.at<uchar>(i + k, j + l);
				else if (abs(k) + abs(l) == 1)
					n += 0.098*	image1.at<uchar>(i + k, j + l);
				else
					n += 0.162*	image1.at<uchar>(i + k, j + l);
			}
			image.at<uchar>(i, j) = n;
		}

	}
	return image;
}
int main()
{

	Mat image1,imgray,imgra,imgrad,imgrad1,imgrad2,imgrad3;
	int th,lth,uth;
	th = 50;
	lth = 50;
	uth = 70;
	char a=0;
	
	
    image1 = imread("C:\\sachin.jpg", CV_LOAD_IMAGE_COLOR);
   	namedWindow("hello sachin", WINDOW_AUTOSIZE);
	
	imshow("hello sachin", image1);
	waitKey(0);/*
	imgray = convert(image1);
    imshow("hello sachin", imgray);
	waitKey(0);*/
	imgray = convert1(image1);
	imshow("hello sachin", imgray);
	waitKey(0);
	/*imgra = convertbin1(imgray,th);
	imshow("hello sachin", imgra);
	waitKey(0);
	imgray = reverse(image1);
	Mat histo = histogram(imgray,&th);
	imshow("hello sachin", histo);
	waitKey(0);
	imgray = convertbin(image1, th);
	imshow("hello sachin", imgray);
	waitKey(0);*/
	//Trackbar1(image1);
	//namedWindow("smoothavg", WINDOW_AUTOSIZE);
	
	//namedWindow("smoothmedian", WINDOW_AUTOSIZE);
	
	namedWindow("Canny", WINDOW_AUTOSIZE);
	//namedWindow("edgedetectionsobel", WINDOW_AUTOSIZE);
	//namedWindow("erosed", WINDOW_AUTOSIZE);*/
	createTrackbar("lower threshold", "Canny", &lth, 255);
	createTrackbar("upper threshold", "Canny", &uth, 255);
	//while (a != 27){
		/*imgra = edgedetection(imgray,70);
		imshow("edge", imgra);
	
		imgrad = dilation(imgra);
		imshow("dilated", imgrad);
	
		imgrad2 = dilation(imgrad);
		imshow("dilated1", imgrad2);
		
		imgrad3 = dilation(imgrad2);
		imshow("dilated2", imgrad3);

		imgrad1 = erosion(imgrad);
		imshow("erosed", imgrad1);*/
	//imgra = smoothavg(imgray);
	//imshow("smoothavg", imgra);
	//imgrad = smoothmedian(imgray);
	//imshow("smoothmedian", imgrad);

	//imgrad2 =smoothgaussian(imgray);
	//imshow("smoothgaussian", imgrad2);
	//imgra = edgedetectionsob(imgrad2);
	//imshow("edgedetectionsobel", imgra);
	while (a != 27)
	{
		Canny(imgray, imgrad, lth, uth, 5);
		imshow("Canny", imgrad);
		a = waitKey(33);

	}
		waitKey(0);
	//}
	return(0);
}