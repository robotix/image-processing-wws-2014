
#include"stdafx.h"
#include<opencv2\core\core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
Mat image = imread("F:\\picture000.jpg", CV_LOAD_IMAGE_COLOR);
Mat hsv(image.rows, image.cols, CV_8UC3);
Mat color(image.rows, image.cols, CV_8UC1);
cvtColor(image, hsv, CV_BGR2HSV);
int h,s,v, i, j;
for (i = 0; i < image.rows; i++)
{
for (j = 0; j < image.cols; j++)
{
v = hsv.at<Vec3b>(i, j)[2];
h = hsv.at<Vec3b>(i, j)[0];
s = hsv.at<Vec3b>(i, j)[1];
if ( h>150 && h<170 && s>200 )
color.at<uchar>(i, j) = 255;
else
color.at<uchar>(i, j) = 0;
}
}
namedWindow("hsv", WINDOW_AUTOSIZE);
imshow("hsv", hsv);
namedWindow("colordetect", WINDOW_AUTOSIZE);
imshow("colordetect", color);
namedWindow("original", WINDOW_AUTOSIZE);
imshow("original", image);
waitKey(0);

}