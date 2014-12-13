#include<stdafx.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;



int Maximum(int a,int Max)
{
	
	

	if (a > Max)
		return a;
	else 
return Max;
}

int Minimum(int b,int Min)
{
	
	

	if (b < Min)
		return b;
	else
	return Min;
}












int main()
{
	int i, j, k, l;
	//int Max = 0;
	//int Min = 255;
	Mat image;
	image = imread("school-building-hi.png");
	Mat img(image.rows, image.cols, CV_8UC1);
	Mat img1(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			img.at<uchar>(i, j) = (0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}


	for (i = 0; i < (img.rows-2); i++)
	{
		for (j = 0; j < (img.cols-2); j++)
		{
			int Max = 0;
			int Min = 255;
			for (k = 0; k<3; k++)
			{
				for (l = 0; l<3; l++)
				{

					Max = Maximum(img.at<uchar>(i + k, j + l),Max);
					Min = Minimum(img.at<uchar>(i + k, j + l),Min);
				}
			} 
			if ((Max - Min)> 10)
				img1.at<uchar>(i + 1, j + 1) = 255;
		}
	}


	imshow("WINDOW", img1);
	waitKey(0);
	return 0;
}