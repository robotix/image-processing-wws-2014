#include<stdafx.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

int main()
{
	Mat image;
	int min, max;
	image = imread("school-building-hi.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat image2(image.rows, image.cols, CV_8UC1);
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);

	createTrackbar("LowerThreshold", "Canny", &min, 255);
	createTrackbar("UpperThreshold", "Canny", &max, 255);
	while (1)
	{
		Canny(image, image2, min, max);
		imshow("Canny", image2);
		int a = waitKey(33);
		if (a == 27)
			break;
	} return 0;
}