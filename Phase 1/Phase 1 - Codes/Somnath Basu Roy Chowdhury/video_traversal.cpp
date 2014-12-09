//Computer_Vision.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
using namespace cv;
int main()
{
	VideoCapture vid("blah1.mp4");
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	int thres=0;
	int fps = vid.get(CV_CAP_PROP_FPS);
	int time = vid.get(CV_CAP_PROP_FRAME_COUNT) / fps;
	cout << fps << " " << time;
	createTrackbar("Track", "Output", &thres,1000*time);
	while (1)
	{
		Mat image;
		vid.read(image);
		imshow("Output", image);
		double thres1 = thres;
		double pos = vid.get(CV_CAP_PROP_POS_MSEC);
		setTrackbarPos("Track", "Output", thres);
		vid.set(CV_CAP_PROP_POS_MSEC, thres1);
		
		thres += 1000/fps;
		if (waitKey(30) == 27)
			break;

	}
	return 0;
}


