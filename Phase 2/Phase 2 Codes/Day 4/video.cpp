#include<stdafx.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

 /* int main()
{
	int i, j,min,max,t;
	VideoCapture video1(0);
	namedWindow("WINDOW", WINDOW_NORMAL);
	createTrackbar("waitkey", "WINDOW", &t, 255);
	
	while (1)
	{
		Mat frame;
		video1 >> frame;
		Mat img(frame.rows, frame.cols, CV_8UC1);
		for (i = 0; i < frame.rows; i++)
		{
			for (j = 0; j < frame.cols; j++)
			{
				img.at<uchar>(i, j) = (0.56*frame.at<Vec3b>(i, j)[0] + 0.33*frame.at<Vec3b>(i, j)[1] + 0.11*frame.at<Vec3b>(i, j)[2]);
			}
		} // Canny(img, img, min, max);
		imshow("WINDOW", img);
		waitKey(t);
	}  return 0;


}  */