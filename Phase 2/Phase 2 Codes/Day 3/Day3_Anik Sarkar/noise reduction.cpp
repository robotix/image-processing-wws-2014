#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include<math.h>
#include <string>

using namespace std;
using namespace cv;

Mat NoiseReduction(Mat img, int block = 5) 
{
	Mat noise_reduced(img.rows, img.cols, CV_8UC1); 
	int i, j, m, n, r = img.rows, c = img.cols, white, black;

	for (i = 0; i<r - block; i += block){
		for (j = 0; j<c - block; j += block){

			white = black = 0;
		
			for (m = i; m<i + block; m++){
				for (n = j; n<j + block; n++){

					if (img.at<uchar>(m, n) == 0)
						black++;
					else
						white++;
				}
			}
			
			int val;
			if (black >= white)
				val = 0;
			else
				val = 255;

			for (m = i; m<i + block; m++){
				for (n = j; n<j + block; n++){
					noise_reduced.at<uchar>(m, n) = val;
				}
			}
		}
	}

	return noise_reduced;
}

int main(){

	string file_name;
	Mat image = imread("tulip.jpg", 0);
	Mat noise_reduced = NoiseReduction(image);
	imshow("Original image", image);
	imshow("Reduced image", noise_reduced);
	waitKey(0);
	image.release();
	noise_reduced.release();
	return 0;
}