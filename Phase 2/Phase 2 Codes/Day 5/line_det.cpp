#include <cmath>
#include <vector>
#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <queue>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("u2.png", 0);
	Mat dst, cdst;
	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, CV_GRAY2BGR);

	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0+1000*(-b));
		pt1.y = cvRound(y0+1000*(a));
		pt2.x = cvRound(x0-1000*(-b));
		pt2.y = cvRound(y0-1000*(a));
		line(cdst,pt1,pt2,Scalar(0,0,255),3,CV_AA);
	}

	imshow("source",src);
	imshow("lines",cdst);
	waitKey();
	return 0;
}