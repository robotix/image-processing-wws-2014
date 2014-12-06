#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;
Mat NoiseReduction(Mat img, int block = 5) //block=5 is our threshold for blob size. Less than that is noise
{
	Mat noise_reduced(img.rows, img.cols, CV_8UC1); //stores final corrected image
	int i, j, m, n, r = img.rows, c = img.cols, white, black;

	for (i = 0; i<r - block; i += block){
		for (j = 0; j<c - block; j += block){

			white = black = 0;
			//to check for large enough blob.
			for (m = i; m<i + block; m++){
				for (n = j; n<j + block; n++){

					if (img.at<uchar>(m, n) == 0)
						black++;
					else
						white++;
				}
			}
			//to remove the identified noise from the image
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


	Mat image;
	Mat noise_reduced;
	image = imread("samantha.jpg", CV_LOAD_IMAGE_COLOR);
	Mat final(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < final.rows; i++)
	{
		for (int j = 0; j < final.cols; j++)
		{
			if (((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3) > 120)
			{
				final.at<uchar>(i, j) = 255;
			}
			else
				final.at<uchar>(i, j) = 0;
		}
	}

	noise_reduced = NoiseReduction(final);
	imshow("Original image", final);
	imshow("Reduced image", noise_reduced);
	waitKey(0);
	
	return 0;
}