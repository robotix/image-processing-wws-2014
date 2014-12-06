#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace std;
using namespace cv;
#define MAX_KERNEL_LENGTH 10

int main()
{
	Mat image;
	image = imread("sh1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat Grey(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat Canny_output(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat binary(image.rows, image.cols, CV_8UC1, Scalar(0));
	


	int i, j, T, h = 0;
//brg to binary
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3) > 120)
			{
				binary.at<uchar>(i, j) = 255;
			}
			else
				binary.at<uchar>(i, j) = 0;
		}
	}
	imshow("Binary", binary);


	//brg to Grey
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int grey = (0.33 * (image.at<Vec3b>(i, j)[0]) + 0.33 * (image.at<Vec3b>(i, j)[1]) + .33*(image.at<Vec3b>(i, j)[2]));
			Grey.at<uchar>(i, j) = grey;
		}
	}
	imshow("Grey_output", Grey );

	//Canny Grey to Cnny_output
	int sum = 0, Sum = 0;
	Vector<int> arr(256);
	for (i = 0; i < 256; i++) arr[i] = 0;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)

		{
			T = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
			arr[T] = arr[T] + 1;
		}
	}
	for (i = 0; (i < 256); i++)
	{
		sum = sum + arr[i];
	}
	for (i = 0; (i < 256); i++)
	{
		Sum = Sum + arr[i];
		if (Sum> sum / 2)
		{
			h = i;
			break;
		}
	}
	int LT = h / 3;
	int HT = h * 2 / 3;
	Canny(image, Canny_output, LT, HT, 3);
	imshow("Canny", Canny_output );
	vector<vector<Point>> contour_output;
	findContours(Canny_output, contour_output, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	//vector<vector<Point>> contours;
	vector<Point> approx;
	
	for (int k = 0; k < contour_output.size(); ++k)
	{
		approxPolyDP(Mat(contour_output[k]), approx, arcLength(contour_output[k], true)*0.02, true); 
		cout << approx.size() << endl;
		if (approx.size() == 3)
		{
			cout << approx.size() << "Triangle" << endl;

		}
		if (approx.size() == 4)
		{
			cout << approx.size() << "Quadrilateral" << endl;
			cout << approx[0].x << "   " << approx[1].x << "   " << approx[2].x << "   " << approx[3].x << endl;
			cout << approx[0].y << "   " << approx[1].y << "   " << approx[2].y << "   " << approx[3].y << endl;


		}
		if (approx.size() > 6)
		{
			cout << approx.size() << "circle" << endl;

		}

		
	}

	//cout << contours.size();
	imshow("test", image);

	waitKey(0);
	return 0;

}