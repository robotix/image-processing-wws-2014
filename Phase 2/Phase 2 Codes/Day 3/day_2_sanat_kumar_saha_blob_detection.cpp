// Sample_Project _Blob_Detection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <queue>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>

using namespace std;
using namespace cv;



int _tmain(int argc, _TCHAR* argv[])
{
	int count = 0;
	Mat input = imread("C:\\Users\\Sanat Kumar Saha\\Desktop\\blob1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat a(input.rows, input.cols, CV_8SC1, Scalar(-1));
	for (int i = 1; i < input.rows-1; i++)
	{
		for (int j = 1; j < input.cols-1; j++){
			if ((input.at<uchar>(i, j) > 200) && (a.at<char>(i,j) == -1)){
				//func(a, i, j, input);
				count++;
				int i1=i, j1=j;
				queue <Point> q;
				Point P;
				P.x = j1; P.y = i1;
				q.push(P);
				a.at<char>(i1, j1) = 0;
				for (int l = -1; l <= 1; l++)
				{
					for (int m = -1; m <= 1; m++){
						if ((a.at<char>(i1 + l, j1 + m) ==-1 ) && input.at<uchar>(i1 + l, j1 + m) >200){
							P.x = j1 + m; P.y = i1 + l;
							q.push(P);
							a.at<char>(P.y, P.x) = 0;
						}
					}
				}
				a.at<char>(i1,j1)=count;
				q.pop();
				while (1){
					P = q.front();
					i1 = P.y; j1 = P.x;
					for (int l = -1; l <= 1; l++)
					{
						for (int m = -1; m <= 1; m++){
							if ((a.at<char>(i1 + l, j1 + m) ==-1 ) && input.at<uchar>(i1 + l, j1 + m) > 200){
								P.x = j1 + m; P.y = i1 + l;
								q.push(P);
								a.at<char>(P.y, P.x) = 0;
							}
						}
					}
					q.pop(); a.at<char>(i1, j1) = count;
					if (q.empty()) break;
				}
			}
		}
	}
	Mat output(input.rows, input.cols, CV_8UC1,Scalar(0));

	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++){
			if (a.at<char>(i, j) != -1){ 
				output.at<uchar>(i, j) = 255 / a.at<char>(i, j);
			}
		}
	}
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	imshow("My Window", output);
	waitKey(0);
	return 0;
}