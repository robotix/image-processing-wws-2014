// opencv_9th_3rd.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>


using namespace std;
using namespace cv;


int y = 100;
Mat image,image1;
double alpha = 100;
int beta = 100;	


void on_trackbar(int,void*)
{
	alpha = ((y + 200) - 300)/100;
	beta = beta - 100;
	Mat newim;
	image1.copyTo(newim);
	for(int i = 0; i<image1.rows;i++)
		{
			for(int j = 0; j<image1.cols;j++)
			{
				for(int c = 0; c<3;c++)
				{
					newim.at<Vec3b>(i,j)[c] =  saturate_cast<uchar>( alpha*( image1.at<Vec3b>(i,j)[c] ) + beta );
				}
			}
		}
	imshow("Brightness Image",newim);

}


int _tmain(int argc, _TCHAR* argv[])
{
	int x = 50;
	namedWindow("Binary Image",WINDOW_AUTOSIZE);
	namedWindow("Brightness Image",WINDOW_AUTOSIZE);
	createTrackbar("Threshold","Binary Image",&x,255);
	createTrackbar("Brightness","Brightness Image",&beta,200,on_trackbar);
	createTrackbar("Contrast","Brightness Image",&y,600,on_trackbar);
	image = imread("a.jpg",CV_LOAD_IMAGE_GRAYSCALE);	
	image1 = imread("a.jpg",CV_LOAD_IMAGE_COLOR);
	Mat newimg(image.rows,image.cols,CV_8UC1);

	on_trackbar(1,0);

	while(1)
	{
		for(int i = 0; i<image.rows;i++)
		{
			for(int j = 0; j<image.cols;j++)
			{
				if(image.at<uchar>(i,j) > x)
				{
					newimg.at<uchar>(i,j) = 255;
				}
				else
				{
					newimg.at<uchar>(i,j) = 0;
				}
			}
		}
		imshow("Binary Image",newimg);
		char a = waitKey(33);
		if(a == 27) break;
	}

	return 0;
}