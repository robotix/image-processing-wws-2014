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
	while (1)
	{


		Mat image, final;
		vid.read(image);
		//image = imread("line.jpg", CV_LOAD_IMAGE_COLOR);
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
		HoughLines(final, lines, 1, CV_PI / 180, 50);
		for (size_t i = 0; i < lines.size(); i++){
			float theta = lines[i][1];
			float rho = lines[i][0];
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			Point pt1(cvRound(x0 + 1000 * (-b)),
				cvRound(y0 + 1000 * (a)));
			Point pt2(cvRound(x0 - 1000 * (-b)),
				cvRound(y0 - 1000 * (a)));
			line(color_dst, pt1, pt2, Scalar(0, 0, 255), 3, 0);
		}

		namedWindow("Detected Lines", 1);
		imshow("Detected Lines", color_dst);
		double s = 0.0;

		for (size_t i = 0; i < lines.size(); i++)
		{
			//cout << " " << lines[i][1] << endl;
			s = s + lines[i][1];
		}
		if (((s / lines.size()) < .45) || (((s / lines.size()) >= 3.05) && ((s / lines.size()) <= 3.25))) cout << "w" << endl;
		else if (((s / lines.size()) > 0) || ((s / lines.size()) < 1.7)) cout << "d" << endl;
		else if (((s / lines.size()) > 1.57) || ((s / lines.size()) < 3.25)) cout << "a" << endl;
		else cout << "s" << endl;


		if (waitKey(33) == 27)			
		break;
		//waitKey(0);
	}
	return 0;
}