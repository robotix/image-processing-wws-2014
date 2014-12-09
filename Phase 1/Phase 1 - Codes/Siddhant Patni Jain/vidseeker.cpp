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
VideoCapture vid("F:\\alcoholic.mp4");
namedWindow("Output", CV_WINDOW_AUTOSIZE);
int thres;
createTrackbar("Track", "Output", &thres,60*1000*3);
while (1)
{
Mat image;
vid.read(image);
imshow("Output", image);
double thres1 = thres;
double pos = vid.get(CV_CAP_PROP_POS_MSEC);
setTrackbarPos("Track", "Output", thres);
vid.set(CV_CAP_PROP_POS_MSEC,thres1);
if (waitKey(30) == 27)
break;

}
return 0;
}