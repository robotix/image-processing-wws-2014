#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include<stdlib.h>
using namespace std;
using namespace cv;
int main()
{
	VideoCapture vid(0);
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	int LT=0, HT=0;
	cvCreateTrackbar("LT", "My Window", &LT, 255);
	cvCreateTrackbar("HT", "My Window", &HT, 255);

	while (1)
	{
		Mat image;
		vid.read(image);
		vector<int> arr(255);
		int sum = 0, Sum = 0;
		int i, j, T;
		int h = 0;

		if (image.empty())
			exit(1);
		Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));

		Mat final1(image.rows, image.cols, CV_8UC1, Scalar(0));
		for (i = 0; i < 255; i++) arr[i] = 0;
		for (i = 0; i < final.rows; i++)
		{
			for (j = 0; j < final.cols; j++)

			{
				T = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
				arr[T] = arr[T] + 1;
			}
		}
		for (i = 0; (i < 255); i++)
		{
			sum = sum + arr[i];
		}
		for (i = 0; (i < 255); i++)
		{
			Sum = Sum + arr[i];
			if (Sum> sum / 2)
			{
				h = i;
				break;
			}
		}
		//LT = h / 3;
		//HT = h * 2 / 3;
		Canny(image, final, LT, HT, 3);
		//HoughLines(final, final1, 1, (CV_PI / 180), 20);
		imshow("My Window", final);
		//imshow("Output", final1);
		int ikey = waitKey(33);
		if (ikey == 27)
			break;

	}
	waitKey(0);
	return 0;
}