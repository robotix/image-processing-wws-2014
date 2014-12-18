/*video*/

#include"stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<math.h>
using namespace std;
using namespace cv;

Mat convert_to_gs(Mat image)
{
	Mat copy(image.rows, image.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			copy.at<uchar>(i, j) = ((image.at<Vec3b>(i, j)[0] * 0.56) + (image.at<Vec3b>(i, j)[1] * 0.33) + (image.at<Vec3b>(i, j)[2] * 0.11));
		}
	}
	return(copy);
}

Mat convert_to_binary(Mat image, int thresh)
{
	Mat binary(image.rows, image.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) <= thresh)
				binary.at<uchar>(i, j) = 0;
			else if (image.at<uchar>(i, j) > thresh)
				binary.at<uchar>(i, j) = 255;
		}
	}
	return(binary);
}

Mat detection1(Mat image)
{
	Mat detect(image.rows, image.cols, CV_8UC1);

	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols - 1; j++)
		{
			int dx, dy;
			dx = (image.at<uchar>(i - 1, j + 1)) - (image.at<uchar>(i - 1, j - 1)) +(2* ((image.at<uchar>(i, j + 1)) - (image.at<uchar>(i, j - 1))))+ (image.at<uchar>(i + 1, j + 1)) - (image.at<uchar>(i + 1, j - 1));
			dy = (image.at<uchar>(i + 1, j - 1)) - (image.at<uchar>(i - 1, j - 1)) +(2*( (image.at<uchar>(i + 1, j)) - (image.at<uchar>(i - 1, j)) ))+ (image.at<uchar>(i + 1, j + 1)) - (image.at<uchar>(i - 1, j + 1));
			detect.at<uchar>(i, j) = (int)(sqrt(pow(dx, 2) + pow(dy, 2)));
		}
	}

	for (int j = 0; j < image.cols; j++)
	{
		detect.at<uchar>(0, j) = 0;
		detect.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		detect.at<uchar>(j, 0) = 0;
		detect.at<uchar>(j, image.cols - 1) = 0;
	}
	return(detect);
}

int main()
{
	VideoCapture v(0); int x, y;
	namedWindow("Window1",WINDOW_AUTOSIZE);
	createTrackbar("lowerthresh","Window1",&x,255);
	createTrackbar("upprethresh","Window1",&y,255);
	while (1)
	{
		Mat frame;
		v >> frame;
		Mat gs = convert_to_gs(frame);
		Mat result;
		Canny(gs,result,x,y);
		imshow("Window1",result);
		char a = waitKey(33);
		if (a == 27)break;
	}
	return(0);
}

/*finding objects of some color using hue value*/

#include"stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<math.h>
using namespace std;
using namespace cv;

Mat hsvcompare(Mat image, int hue, int threshH)
{
	Mat result(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<Vec3b>(i, j)[0]>(hue - threshH) && image.at<Vec3b>(i, j)[0] < (hue + threshH))
				result.at<uchar>(i, j) = 255;
			else
				result.at<uchar>(i, j) = 0;
		}
	}
	return(result);
}

int main()
{
	Mat image = imread("c:\\Users\\V.Uday\\Desktop\\fb pics\\minions.jpg");
	Mat hsvimage;
	int hue, thresh;
	namedWindow("Window1", WINDOW_AUTOSIZE);
	createTrackbar("hue", "Window1", &hue, 239);
	createTrackbar("thresh limit", "Window1", &thresh, 50);
	while (1)
	{
		cvtColor(image, hsvimage, CV_BGR2HLS);
		Mat result = hsvcompare(hsvimage, hue, thresh);
		imshow("Window1", result);
		char a = waitKey(33);
		if (a == 27)break;
	}
}