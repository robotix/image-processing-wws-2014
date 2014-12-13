// opencv_9th_1st.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <math.h>

using namespace std;
using namespace cv;


int _tmain(int argc, _TCHAR* argv[])
{
	Mat flag(450,900,CV_8UC3);

	for(int i=0;i<150;i++)
	{
		for(int j = 0; j<900;j++)
		{
			flag.at<Vec3b>(i,j)[0] = 51;
			flag.at<Vec3b>(i,j)[1] = 153;
			flag.at<Vec3b>(i,j)[2] = 255;
		}
	}
	for(int i=0;i<150;i++)
	{
		for(int j = 0; j<900;j++)
		{
			flag.at<Vec3b>(i+150,j)[0] = 255;
			flag.at<Vec3b>(i+150,j)[1] = 255;
			flag.at<Vec3b>(i+150,j)[2] = 255;
		}
	}
	
	for(int i=0;i<150;i++)
	{
		for(int j = 0; j<900;j++)
		{
			flag.at<Vec3b>(i+300,j)[0] = 8;
			flag.at<Vec3b>(i+300,j)[1] = 136;
			flag.at<Vec3b>(i+300,j)[2] = 19;
		}
	}

	for(int i=0;i<450;i++)
	{
		for(int j = 0; j<900;j++)
		{
			if(sqrt(pow((double)(j-450),2)+pow((double)(i-225),2)) < 76 && sqrt(pow((double)(j-450),2)+pow((double)(i-225),2)) > 70)
			{
				flag.at<Vec3b>(i,j)[0] = 128;
				flag.at<Vec3b>(i,j)[1] = 0;
				flag.at<Vec3b>(i,j)[2] = 0;
			}
			
		}
	}

	flag.at<Vec3b>(225,450)[0] = 128;
	flag.at<Vec3b>(225,450)[1] = 0;
	flag.at<Vec3b>(225,450)[2] = 0;

	namedWindow("My",CV_WINDOW_AUTOSIZE);
	imshow("My",flag);
	waitKey(0);
	return 0;
}