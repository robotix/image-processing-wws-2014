#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void flag_display(){													//display flag
	Mat image(300, 1000, CV_8UC3, Scalar(0, 0, 0));
	for (int x = 0; x < 1000; x++){
		for (int y = 0; y < 300; y++){
			if (y < 100)
			{
				image.at<Vec3b>(y, x)[1] = 165;
				image.at<Vec3b>(y, x)[2] = 255;
			}
			else if (y > 200)
				image.at<Vec3b>(y, x)[1] = 255;
			else{
				image.at<Vec3b>(y, x)[0] = 255;
				image.at<Vec3b>(y, x)[1] = 255;
				image.at<Vec3b>(y, x)[2] = 255;
			}

		}
	}
	namedWindow("flag", WINDOW_AUTOSIZE);
	imshow("flag", image);

}

Mat grayscale(Mat M,int thres,int thres2){																//return grayscale image with a ratio
	Mat gray(M.rows, M.cols, CV_8UC1);
	for (int x = 0; x < M.cols; x++){
		for (int y = 0; y < M.rows; y++){
			gray.at<uchar>(y, x) = (M.at<Vec3b>(y, x)[0] * thres +thres2*M.at<Vec3b>(y, x)[1] + (100-thres-thres2)*M.at<Vec3b>(y, x)[2])/100;

		}
	}
	return gray;

}

Mat grayscale_avg(Mat M){															//return grayscale image of input using average
	Mat gray(M.rows, M.cols, CV_8UC1);
	for (int x = 0; x < M.cols; x++){
		for (int y = 0; y < M.rows; y++){
			gray.at<uchar>(y, x) = (M.at<Vec3b>(y, x)[0] + M.at<Vec3b>(y, x)[1] + M.at<Vec3b>(y, x)[2])/3;

		}
	}
	return gray;

}

Mat black_white(Mat m,int threshold){												//return black and white image acc to threshold
	Mat gray = grayscale_avg(m);
	for (int x = 0; x < gray.cols; x++){
		for (int y = 0; y < gray.rows; y++){
			gray.at<uchar>(y, x) = (gray.at<uchar>(y, x))<threshold?0:255;
		}
	}
	return gray;

}

Mat patches(){																		//display 10x10 patches
	int rows = 10, cols = 10;
	Mat m(1000, 1000, CV_8UC3, Scalar(0, 0, 0));

	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			for (int i = (m.cols/cols)*col; i < (m.cols/cols)*(col+1); i++){
				for (int j = (m.rows/rows)*row; j < (m.rows/rows)*(row+1); j++){
					if ((row + col) % 3 == 0)
						m.at<Vec3b>(j, i)[0] = 255;
					else if ((row + col) % 3 == 2)
						m.at<Vec3b>(j, i)[1] = 255;
					else
						m.at<Vec3b>(j, i)[2] = 255;

				}

			}
		}
	}
	return m;
	
}

Mat reverse(Mat m){																//upside down
	uchar temp;
	for (int x = 0; x < m.cols*3; x++){
		for (int y = 0; y < m.rows/2; y++){
			temp = m.at<uchar>(y, x);
			m.at<uchar>(y, x) = m.at<uchar>(m.rows - y-1, x);
			m.at<uchar>(m.rows - y-1, x) = temp;
		}
	}
	return m;
}

Mat rot_lateral(Mat m){															//mirror image
	uchar temp;
	for (int x = 0; x < m.cols/2; x++){
		for (int y = 0; y < m.rows; y++){
			temp = m.at<Vec3b>(y,x)[0];
			m.at<Vec3b>(y, x)[0] = m.at<Vec3b>(y, m.cols-x-1)[0];
			m.at<Vec3b>(y,m.cols-1-x)[0] = temp;
			temp = m.at<Vec3b>(y, x)[1];
			m.at<Vec3b>(y, x)[1] = m.at<Vec3b>(y, m.cols - x - 1)[1];
			m.at<Vec3b>(y, m.cols - 1 - x)[1] = temp;
			temp = m.at<Vec3b>(y, x)[2];
			m.at<Vec3b>(y, x)[2] = m.at<Vec3b>(y, m.cols - x - 1)[2];
			m.at<Vec3b>(y, m.cols - 1 - x)[2] = temp;
		}
	}
	return m;
}

Mat histogram(Mat m,int *thres){                                         //return histogram image and threshold
	Mat gray = grayscale_avg(m);
	int freq[256];
	unsigned int sum = 0;
	for (int i = 0; i < 256; i++)
		freq[i] = 0;
	for (int x = 0; x < gray.cols; x++){									//get frequency in freq array
		for (int y = 0; y < gray.rows; y++){
			freq[gray.at<uchar>(y, x)]++; 
			}
	}
	int scale=0;
	for (int x = 0; x < 256; x++){											//threshold frequency and scaling factor
		sum += freq[x];
		if (sum<(gray.total()/2))
		{
			*thres = x;
		}
		scale = (freq[x]>scale) ? freq[x] : scale;
		
	}
	Mat hist(400, 260, CV_8UC1,Scalar(255));
	for (int x = 0; x < 256; x ++){											//plotting histogram
		for (int y = hist.rows-((freq[x]*399)/scale)-1; y< hist.rows; y++){
			hist.at<uchar>(y, x) = 0;

		}
	}
	return hist;

}

void main(){
	Mat m = imread("V:\\wallpaper\\12.jpg", CV_LOAD_IMAGE_COLOR);
	if (m.data)
	{
		int  thres = 50,thres2=50;
		int wait = 0;
		//cout << "Enter threshold for black and white image:  ";
		//cin >> thres;
		namedWindow("original", WINDOW_AUTOSIZE);
		imshow("original", m);
		Mat returned;
		//Mat returned = histogram(m,&thres);
		//namedWindow("disp", WINDOW_AUTOSIZE);
		//imshow("disp", returned);
		namedWindow("grayscale", WINDOW_AUTOSIZE);

		createTrackbar("BLUE Threshold:  ", "grayscale", &thres, 100);
		while (wait != 27){
			createTrackbar("GREEN Threshold:  ", "grayscale", &thres2, 100 - thres);
			if (thres2 > (100 - thres))
				thres2 = 100 - thres;
			returned = grayscale(m, thres,thres2);
			imshow("grayscale", returned);
			wait = waitKey(20);
			
		}
	}

	else{
		cout << "image not found" << endl << endl;
		int m;
		cin >> m;
	}

}