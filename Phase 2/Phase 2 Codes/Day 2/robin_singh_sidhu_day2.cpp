// vision2.cpp : Defines the entry point for the console application.
//     pastebin.com
// sengoku basara?? attack on titans
//abhinav.jain@robotix.in
#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

Mat gtob(int, Mat);
Mat grayscale(int, int, int);
int rw();
int flag();
void invert(Mat& img);
int histo();
int main()
{
	int x = 100, slut = 100, y = 100;
	int i, j;
	string str = "C:\\Users\\Hellblazer\\Documents\\Visual Studio 2013\\Projects\\vision2\\cw.png";
	Mat img = imread(str, 1);
	namedWindow("Bitch", WINDOW_AUTOSIZE);
	createTrackbar("Red", "Bitch", &slut, 255);
	while (1 && x+slut <= 255)
	{
		createTrackbar("Blue", "Bitch", &x, 255-slut);
		imshow("Bitch", img);
		waitKey(33);
	}


	return 0;
}
int tb1()
{
	int fuck = 50;
	Mat img = grayscale(55, 33, 11);
	namedWindow("wind", WINDOW_AUTOSIZE);
	createTrackbar("Meter", "wind", &fuck, 255);
	while (1)
	{

		Mat im = gtob(fuck, img);
		imshow("wind", im);
		char a = waitKey(33);
		if (a == 27)
			break;

	}
	return 0;
}
int histo()
{
	int i, j;
	//string str = "A:\\1.png";
	long long int hist[256] = { 0 };
	Mat img = grayscale(55, 33, 11);
	//int threshold;
	//cout << "enter threshold\n";
	///cin >> threshold;
	//gtob(threshold, img);
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			hist[img.at<uchar>(i, j)]++;
		}
	}
	long long int no_pix = img.rows * img.cols;
	long long int sum = 0, threshold;
	for (i = 0; i < 256 && sum <= (no_pix / 2); i++)
	{
		sum += hist[i];
	}
	threshold = i;
	cout << threshold;
	Mat his(300, 256, CV_8UC1, Scalar(0));
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < hist[i] / 10; j++)
		{
			his.at<uchar>(j, i) = 255;
		}
	}
	invert(his);
	imshow("bitch", his);
	waitKey(0);
	return 0;
}
void invert(Mat& img)
{
	int i, j, k;
	for (i = 0; i <= (img.rows) / 2; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			// img is bgr
			/*
			Vec3b col1 = img.at<Vec3b>(i, j);
			Vec3b col2 = img.at<Vec3b>(img.rows - 1 - i, j);
			Vec3b tmp = col1;
			col1 = col2;
			col2 = tmp;
			img.at<Vec3b>(i, j) = col1;
			img.at<Vec3b>(img.rows - 1 - i, j) = col2;
			*/
			// img is bw
			uchar tmp = img.at<uchar>(i, j);
			img.at<uchar>(i, j) = img.at<uchar>(img.rows - 1 - i, j);
			img.at<uchar>(img.rows - 1 - i, j) = tmp;



		}
	}
}

Mat gtob(int threshold, Mat im)
{
	Mat img(im.rows, im.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < im.rows; i++)
	{
		for (j = 0; j < im.cols; j++)
		{
			if (im.at<uchar>(i, j) > threshold)
			{
				img.at<uchar>(i, j) = 255;
			}
			else
				img.at<uchar>(i, j) = 0;
		}
	}

	return img;

}





Mat grayscale(int red, int blue, int green)
{
	string str = "A:\\1.png";
	Mat img = imread(str, 1);
	Mat im(img.rows, img.cols, CV_8UC1);
	Mat im1(img.rows, img.cols, CV_8UC1);
	Mat im2(img.rows, img.cols, CV_8UC1);
	Mat im12(img.rows, img.cols, CV_8UC1);

	// best grayscale from colored (.56, .33, .11)
	int i, j;
	for (i = 0; i < img.cols; i++)
	{
		for (j = 0; j < img.rows; j++)
		{

			Vec3b color = img.at<Vec3b>(j, i);
			im.at<uchar>(j, i) = color[0];
			im1.at<uchar>(j, i) = color[1];
			im2.at<uchar>(j, i) = color[2];
			im12.at<uchar>(j, i) = color[0] *(blue/100) + (green/100)*color[1] + color[2] *(red/100);
		}
	}

	//namedWindow("bitch", WINDOW_AUTOSIZE);
	//namedWindow("bitch1", WINDOW_AUTOSIZE);
	//namedWindow("bitch2", WINDOW_AUTOSIZE);
	//namedWindow("bitch12", WINDOW_AUTOSIZE);
	//imshow("bitch", im);
	//imshow("bitch1", im1);
	//imshow("bitch2", im2);
	//imshow("bitch12", im12);
	waitKey(0);
	return im12;
}

int rw()
{
int x, y;
string str = "A:\\1.png";
Mat im = imread(str, CV_LOAD_IMAGE_COLOR);
// imread(, 1) colored in bgr
// imread(, 0) grayscale

//Mat im = imread("A:\\zY5euSP.jpg", CV_LOAD_IMAGE_COLOR);
//namedWindow("sc", WINDOW_AUTOSIZE);
namedWindow("sb", WINDOW_AUTOSIZE);
imshow("sb", im);
waitKey(0);
for (y = 0; y < im.rows; y++)
{


for (x = 0; x < im.cols; x++)
{
Vec3b color = im.at<Vec3b>(y, x); // a vector of dim 3
color[1] = color[2] = 0;
im.at<Vec3b>(y, x) = color;
}

}
namedWindow("sb", WINDOW_AUTOSIZE);
imshow("sb", im);
waitKey(0);
//	imshow("sb", image);
return 0;
}


int flag()
{

Mat img (300, 300, CV_8UC3, Scalar(0,0,0));
int i, j;

for (i = 0; i < 300; i++)
{

for (j = 0; j < 100; j++)
{
img.at<Vec3b>(i, j)[0] = 120; // 0 128 255
img.at<Vec3b>(i, j)[1] = 128;
img.at<Vec3b>(i, j)[2] = 255;
}
for (j = 100; j < 200; j++)
{
img.at<Vec3b>(i, j)[0] = 255; // 255 255 255
img.at<Vec3b>(i, j)[1] = 255;
img.at<Vec3b>(i, j)[2] = 255;
}
for (j = 200; j < 300; j++)
{
img.at<Vec3b>(i, j)[0] = 10; // 0 255 0
img.at<Vec3b>(i, j)[1] = 255;
img.at<Vec3b>(i, j)[2] = 110;
}
}

namedWindow("bitch", WINDOW_AUTOSIZE);
imshow("bitch", img);
waitKey(0);
return 0;
}