#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <queue>
#include <math.h>

using namespace std;
using namespace cv;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	Mat* rgb = (Mat*)userdata;

	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		cout << "Red=" << (int)(*rgb).at<Vec3b>(y, x)[2] << endl;;
		cout << "Green=" << (int)(*rgb).at<Vec3b>(y, x)[1] << endl;
		cout << "Blue=" << (int)(*rgb).at<Vec3b>(y, x)[0] << endl;
	}
	/*else if (event == EVENT_RBUTTONDOWN)
	{
	cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
	cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
	cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

	}*/
}

int main()
{
	Mat img = imread("F:\\picture000.jpg");

	namedWindow("My Window", CV_WINDOW_AUTOSIZE);

	setMouseCallback("My Window", CallBackFunc, &img);

	imshow("My Window", img);

	waitKey(0);
	return 0;
}