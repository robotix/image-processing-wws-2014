#include"stdafx.h"

#include<iostream>
#include<stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>
#include<queue>
using namespace std;
using namespace cv;

Mat border(Mat img1)
{
	
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
			if ((max - min)>50) img2.at<uchar>(i, j) = 255;
		}
	}
	return(img2);
}

Mat border2(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max,x=0,y=0;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows-1) || (j == 0) || (j == img1.cols-1)) continue;
			x = 0; y = 0;
			for (int k = -1; k <= 1; k++)
			{
				x+= img1.at<uchar>(i + k, j + 1) - img1.at<uchar>(i + k, j - 1);
				y += img1.at<uchar>(i + 1, j + k) - img1.at<uchar>(i - 1, j + k);

			}
			img2.at<uchar>(i, j) = sqrt(x*x + y*y);
		}
	}
	return(img2);
}

Mat dilation(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
			img2.at<uchar>(i, j) =max;
		}
	}
	return(img2);
}
Mat erosion(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
		img2.at<uchar>(i, j) =min;
		}
	}
	return(img2);
}
Mat noisemean(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, avg = 0;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			avg = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
	
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					avg += img1.at<uchar>(i + k, j + l);
				}
			}
			img2.at<uchar>(i, j) = avg / 9;
		}
	}
	return(img2);
}
int sort(int a[])
{
	int temp;
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	return 0;
}
Mat noisemedian(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, n=0,a[9];
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					a[n++] = img1.at<uchar>(i + k, j + l);
				}
			}
			sort(a);
			img2.at<uchar>(i, j) = a[4];
		}
	}
	return(img2);
}
Mat gausian(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, n = 0,sum;
	float a[9] = { 0.06, 0.098, 0.06, 0.098, 0.162, 0.098, 0.06, 0.098, 0.06 };
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = 0;
			sum = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					sum += a[n++] * (img1.at<uchar>(i + k, j + l));
				}
			}
			img2.at<uchar>(i, j) = sum;
		}
	}
	return(img2);
}
Mat grey(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			img2.at<uchar>(i, j) = img1.at<Vec3b>(i, j)[0] * 0.55 + img1.at<Vec3b>(i, j)[1] * 0.33 + img1.at<Vec3b>(i, j)[2] * 0.11;
		}
	}
	return img2;

}
Mat bnw(Mat img1, int thresh)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int n;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = img1.at<uchar>(i, j);
			if (n>thresh)
			{
				img2.at<uchar>(i, j) = 0;
			}
			else img2.at<uchar>(i, j) = 255;
		}
	}
	return img2;
}
Mat hsv_to_rgb(Mat img1)
{
	Mat img2;
	cvtColor(img1, img2, CV_BGR2HSV);
	return (img2);
}
Mat detectcolor(Mat img1,int h)
{
	Mat img2(img1.rows,img1.cols,CV_8UC1,Scalar(0));
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((img1.at<Vec3b>(i, j)[0]<128 + h) && (img1.at<Vec3b>(i, j)[0]>128 - h)) img2.at<uchar>(i, j) = 255;
		}
	}
	return(img2);
}

Mat cont(int a, int b, Mat img1, Mat img2, queue<Point> q, int x)
{
	q.push(Point(a, b));
	img2.at<schar>(a, b) = 0;
	int i = a, j = b;
	while (1)
	{

		for (int k = -1; k < 2; k++)
		{
			for (int l = -1; l < 2; l++)
			{
				if ((img1.at<uchar>(i + k, j + l) == 255) && (img2.at<schar>(i + k, j + l) == -1))
				{
					q.push(Point(i + k, j + l));
					img2.at<schar>(i + k, j + l) = 0;

				}
			}
		}
		q.pop();
		img2.at<schar>(i, j) = x;
		Point pointPop = q.front();
		i = pointPop.x;
		j = pointPop.y;
		if (q.empty())  break;
	}
	return img2;
}
Mat blobdetect(Mat img1)
{
	int x = 1;
	Mat img2(img1.rows, img1.cols, CV_8SC1, Scalar(-1));
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((img1.at<uchar>(i, j) == 255) && (img2.at<schar>(i,j)==-1))
			{
				queue<Point> q;
				img2=cont(i,j,img1,img2,q,x);
				x++;

			}
		}
	}
	return img2;

}
void printblob(Mat img1,int x)
{
	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0));
	for (int i = 0; i < img1.rows;i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if (img1.at<schar>(i, j) == x) img2.at<uchar>(i, j) = 255;
		}
	}
	namedWindow("blob", WINDOW_AUTOSIZE);
	imshow("blob", img2);
	waitKey(0);
}
int main()
{
	
	Mat img1;
	img1 = imread("blobs.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = blobdetect(img1);
	printblob(img2,1);
/*	Mat img1;
	img1 = imread("hqdefault.jpg", CV_LOAD_IMAGE_GRAYSCALE);*/
	//namedWindow("toll", WINDOW_AUTOSIZE);
	//imshow("edgedetect", img1);
	/*int thresh = 10;
	int lower = 0, upper = 0;
	createTrackbar("lower", "video", &lower, 256);
	createTrackbar("upper", "video",&upper,256);
	VideoCapture V(0);*/
	//createTrackbar("trackbar", "video",&thresh, 256);
	//int h = 0;
	//createTrackbar("hsv", "toll", &h, 100);
	/*while (1)
	{
		Mat img2;*/
	    ///Canny(img1, img2, lower, upper, 3);
		//img2 = dilation(img2);
		//img2 = erosion(img2);
		//imshow("edgedetect", img2);
		/*Mat frame;
		V >> frame;
		frame = grey(frame);
		Canny(frame, frame, lower, upper, 3);*/
		//frame = gausian(frame);
		//frame = bnw(frame,thresh);
		//frame = border2(frame);
		//frame = dilation(frame);
		//frame = erosion(frame);
		/*img2 = hsv_to_rgb(img1);
		Mat img3 = detectcolor(img2,h);
		imshow("toll", img3);
		char a = waitKey(33);
		if (a == 27) break;
	}*/

	/*Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	img2 = noisemean(img1);
	namedWindow("mean",WINDOW_AUTOSIZE);
	imshow("mean", img2);
	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	img3 = noisemedian(img1);
	namedWindow("median", WINDOW_AUTOSIZE);
	imshow("median", img3);
	img3 = gausian(img1);
	namedWindow("gausian", WINDOW_AUTOSIZE);
	imshow("gausian", img3);*/
	/*img2 = border(img1);
	namedWindow("dilated", WINDOW_AUTOSIZE);
	imshow("dilated", img2);
	img2 = dilation(img2);
	namedWindow("eroded", WINDOW_AUTOSIZE); 
	imshow("eroded", img2);
	img2 = erosion(img2);
	//img2 = border2(img1);
	//img2 = border2(img2);
	//imshow("edgedetect", img2);
	waitKey(0);*/

}