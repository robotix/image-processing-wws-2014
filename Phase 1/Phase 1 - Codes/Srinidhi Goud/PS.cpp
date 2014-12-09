#include"stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;




int main(){
	VideoCapture vid(0);
	int lowthresh = 20, highthresh = 100;
	while (1){
		Mat image, final;
		vid.read(image);
		vector<int> arr(255);
		int sum = 0, Sum = 0;
		int i, j, T, t = 0;
		int h = 0;
		string win_name = "Edge-extracted image";
		namedWindow(win_name, CV_WINDOW_AUTOSIZE);
		Mat grayscale(image.rows, image.cols, CV_8UC1);
		for (int i = 0; i < grayscale.rows; i++)
		{
			for (int j = 0; j < grayscale.cols; j++)
			{
				int grey = (0.33 * (image.at<Vec3b>(i, j)[0]) + 0.33 * (image.at<Vec3b>(i, j)[1]) + .33*(image.at<Vec3b>(i, j)[2]));
				grayscale.at<uchar>(i, j) = grey;
			}
		}

		Mat result = grayscale.clone();
		for (i = 1; i < 20; i += 2)
		{
			GaussianBlur(result, final, Size(i, i), 0, 0);
		}
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
		Mat color_dst;
		Canny(final, final, h / 3, (h * 2 / 3), 3);
		cvtColor(final, color_dst, CV_GRAY2BGR);
		imshow(win_name, final);
		image.release();

		vector<Vec2f> lines;
		HoughLines(final,
			lines,
			1,
			CV_PI / 180,
			50);
		for (size_t i = 0; i < lines.size(); i++){
			float theta = lines[i][1];
			float rho = lines[i][0];
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			Point pt1(cvRound(x0 + 1000 * (-b)),
				cvRound(y0 + 1000 * (a)));
			Point pt2(cvRound(x0 - 1000 * (-b)),
				cvRound(y0 - 1000 * (a)));
			line(color_dst, pt1, pt2, Scalar(0, 0, 255), 3, 8);
		}
		namedWindow("Detected Lines", 1);
		imshow("Detected Lines", color_dst);
		double sum = 0.0;

		for (size_t i = 0; i < lines.size(); i++)
		{
			//cout << " " << lines[i][1] << endl;
			sum = sum + lines[i][1];
		}
               sum=(sum/lines.size)
		if((sum < .5) || ((sum >= 3.04) && (sum <= 3.24)) cout << "Straight" << endl;
		else if ((sum > 0) || (sum < 1.67)) cout << "Right" << endl;
		else if ((sum > 1.57) || (sum < 3.24)) cout << "a" << endl;
		else cout << "Back" << endl;

		char ch = waitKey(33);
		if (ch == 27)	 break;

	}
	return 0;
}