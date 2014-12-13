
#include<iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
int main()
{
int t = 11, h=149;
Mat img = imread("/home/codeboy/Pictures/10670130_718209918257787_6233843121027313804_n.jpg");
Mat image;
cvtColor(img, image, CV_BGR2HLS_FULL);
imshow("Original", img);
waitKey(0);
namedWindow("Colour Detection", WINDOW_NORMAL);
createTrackbar("Tolerance", "Colour Detection", &t, 50);
createTrackbar("Hue", "Colour Detection", &h, 255);
while (1)
{
Mat final(img.rows, img.cols, CV_8UC1, Scalar(0));
for (int i = 0; i < image.rows; i++)
{
for (int j = 0; j < image.cols; j++)
{
if (image.at<Vec3b>(i, j)[0]>(h - (t*255/360)) && image.at<Vec3b>(i, j)[0] < (h + (t*255/360)))
final.at<uchar>(i, j) = 255;
}
}
imshow("Colour Detection", final);
int a;
a=waitKey(20);
if (a == 27)
break;
}
return 0;
}
