#include"stdafx.h"
//#include<conio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void flag(int row,int col){
	int i, x, y;
	Mat flag, image2, image(row, col, CV_8UC3), image_red;
	for (y = 0; y < row / 3; y++){
		for (x = 0; x < col; x++){
			image.at<Vec3b>(y, x)[0] = 0;
			image.at<Vec3b>(y, x)[1] = 128;
			image.at<Vec3b>(y, x)[2] = 255;
		}
	}
	for (y = (row / 3); y < (row * 2 / 3); y++){
		for (x = 0; x < col; x++){
			for (i = 0; i < 3; i++){
				image.at<Vec3b>(y, x)[i] = 255;
			}
		}
	}
	for (y = (row * 2 / 3); y < row; y++){
		for (x = 0; x < col; x++){
			image.at<Vec3b>(y, x)[0] = 76;
			image.at<Vec3b>(y, x)[1] = 177;
			image.at<Vec3b>(y, x)[2] = 34;
		}
	}
	namedWindow("My Flag", WINDOW_AUTOSIZE);
	imshow("My Flag", image);
	waitKey(0);
	destroyWindow("My Flag");
}
void grscale_avg(Mat image){
	Mat gr_img(image.rows, image.cols, CV_8UC1);
	int a, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			gr_img.at<uchar>(y, x) = a;
		}
	}
	namedWindow("My Grey Window avg", WINDOW_AUTOSIZE);
	imshow("My Grey Window avg", gr_img);
	waitKey(0);
	destroyWindow("My Grey Window avg");
}
void grscale(Mat image){
	Mat gr_img(image.rows, image.cols, CV_8UC3);
	int   x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			gr_img.at<Vec3b>(y, x)[0] = 0.56*image.at<Vec3b>(y, x)[0];
			gr_img.at<Vec3b>(y, x)[1] = 0.33*image.at<Vec3b>(y, x)[1];
			gr_img.at<Vec3b>(y, x)[2] = 0.11*image.at<Vec3b>(y, x)[2];

		}
	}
	imshow("My Grey Window", gr_img);
	waitKey(0);
	destroyWindow("My Grey Window");
}
void binary_img(Mat image){
	Mat bin_img(image.rows, image.cols, CV_8UC1);
	int a, i, x, y, t;
	cout << "Enter the thresh : " ;
	cin >> t;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y,x)[2]) / 3;
			if (a < t)
				i = 0;
			else
				i = 255;
			bin_img.at<uchar>(y, x) = i;
		}
	}
	namedWindow("My Binary Window",WINDOW_AUTOSIZE);
	imshow("My Binary Window", bin_img);
	waitKey(0);
	destroyWindow("My Binary Window");
}
void invert_h_img(Mat image){
	Mat inv_img(image.rows, image.cols, CV_8UC3);
	int a, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.rows - y -1);
			inv_img.at<Vec3b>(a, x)[0] = image.at<Vec3b>(y, x)[0];
			inv_img.at<Vec3b>(a, x)[1] = image.at<Vec3b>(y, x)[1];
			inv_img.at<Vec3b>(a, x)[2] = image.at<Vec3b>(y, x)[2];
		}
	}
	imshow("My Window", image);
	namedWindow("My Invert Window", WINDOW_AUTOSIZE);
	imshow("My Invert Window", inv_img);
	waitKey(0);
	destroyWindow("My Invert Window");
	destroyWindow("My Window");
}
void histogram_t_grscale(Mat image){
	Mat gr_img(image.rows, image.cols, CV_8UC1);
	Mat bin_img(image.rows, image.cols,CV_8UC1);
	Mat histogram(500, 256, CV_8UC1);
	int a, x, y, h[256], i, area, t = 0, cnt = 0, m, p;
	
	
	area = image.rows*image.cols;
	for (i = 0; i < 256; i++){
		h[i] = 0;
	}
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			gr_img.at<uchar>(y, x) = a;
			h[a]++;
		}
	}
	namedWindow("My Grey Window avg", WINDOW_AUTOSIZE);
	imshow("My Grey Window avg", gr_img);
	waitKey(0);

	m = area / 500;
	for (x = 0; x < 256; x++){
		p = h[x] / m;
		for (y = (499 - p); y < 500; y++){
			histogram.at<uchar>(y, x) = 0;
		}
	}
	imshow("My histogram", histogram);
	waitKey(0);
	
	for (t = 0; cnt <= (area / 2) && t < 256; t++){
		cnt += h[a];
	}
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = gr_img.at<uchar>(y,x);
			if (a < t)
				i = 0;
			else
				i = 255;
			bin_img.at<uchar>(y, x) = i;
		}
	}
	namedWindow("My Binary Window", WINDOW_AUTOSIZE);
	imshow("My Binary Window", bin_img);
	waitKey(0);
}
void track_bars_gr(Mat image);
Mat makebinary(Mat image, int t);

void track_bars_color(Mat image);
Mat makebinary_color(Mat image, int t1, int t2, int t3);


int main(){
	Mat image = imread("F:\\Facebook\\baby-girl-names-2014.jpg", CV_LOAD_IMAGE_COLOR);
	flag(360, 640);
	grscale_avg(image);
//	grscale(image);
	binary_img(image);
	invert_h_img(image);
	histogram_t_grscale(image);
	track_bars_gr(image);
	track_bars_color(image);
		
	return 0;
}


void track_bars_gr(Mat image){
	int t, c;
	cout << "ENTER AN INITIAL THRESH : ";
	cin >> t;
	namedWindow("Binary Window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Binary Window", &t, 255);
	while (1){
		Mat img = makebinary(image, t);
		imshow("Binary Window", img);
		c = waitKey(33);
		if (c == 27) break;
	}
//	destroyWindow("Binary Window");
}
Mat makebinary(Mat image, int t){
	Mat bin_img(image.rows, image.cols, CV_8UC1);
	int a, i, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			if (a < t)
				i = 0;
			else
				i = 255;
			bin_img.at<uchar>(y, x) = i;
		}
	}
	return bin_img;
}
void track_bars_color(Mat image){
	int t1, t2, t3, c;
	cin >> t1;
	cin >> t2;
	cin >> t3;
	namedWindow("Color Binary Window", WINDOW_AUTOSIZE);
	createTrackbar("Blue","Color Binary Window", &t1, 255);
	createTrackbar("Green","Color Binary Window", &t2, 255);
	createTrackbar("Red","Color Binary Window", &t3, 255);
	while (1){
		Mat img = makebinary_color(image, t1, t2, t3);
		imshow("Color Binary Window", img);
		c = waitKey(33);
		if (c == 27) break;
	}

}
Mat makebinary_color(Mat image, int t1, int t2, int t3){
	Mat bin_img(image.rows, image.cols, CV_8UC3);
	int a, i, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = image.at<Vec3b>(y, x)[0];
			if (a < t1) i = 0;
			else i = 255;
			bin_img.at<Vec3b>(y, x)[0] = i;
			
			a = image.at<Vec3b>(y, x)[1];
			if (a < t2) i = 0;
			else i = 255;
			bin_img.at<Vec3b>(y, x)[1] = i;
			
			a = image.at<Vec3b>(y, x)[2];
			if (a < t3) i = 0;
			else i = 255;
			bin_img.at<Vec3b>(y, x)[2] = i;
		}
	}
	return bin_img;
}
