#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include<opencv2/imgproc/imgproc.hpp>



using namespace std;
using namespace cv;
void bfs();
void rec(Mat , Mat , int , int , int );


void bfs()
{
	
		 Mat img = imread("E:\\untitled1.jpg", CV_LOAD_IMAGE_COLOR);

		 Mat temp(img.rows, img.cols, CV_8UC1, Scalar(0));
	
	 Mat visited(img.rows, img.cols, CV_8SC1);


	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			visited.at<uchar>(i, j) = -1;
		}
	}
	int count = 0;
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			if (img.at<uchar>(i, j) == 255 && visited.at<char>(i, j) == -1)
			{
				count++; visited.at<char>(i, j) = count;

				rec(img, visited, i, j, count);
			}
		}
	}for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			if (visited.at<char>(i, j) == 1)

				temp.at<uchar>(i, j) = 255;
		}
	}
	imshow("mywindow", temp);
}

	void rec(Mat img, Mat visited, int i, int j, int count)
	{
		int a = 0;
		if (i >=(img.rows - 2) || j >=(img.cols - 2))
			return ;
		for (int k = -1; k < 2; k++)
		{
			for (int m = -1; m < 2; m++)
			{
				if ((img.at<uchar>((i + k), (j + m)) == 255) && (visited.at<char>((i + k), (j + m)) == -1))a++;
				
			}
		}if (a == 0)return;
				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						if (img.at<uchar>((i + k),(j + m)) == 255 && visited.at<char>((i + k), (j + m)) == -1)
						{
							visited.at<char>((i + k), (j + m)) = count;
							rec(img, visited, i + k, j + m, count);
						}
					}
				}
			
		
	}




	void main()
	{
		bfs();
	}
void retainingshapes(Mat src)
	 {
		 Mat dest;
		 Mat res(src.rows, src.cols, CV_8UC1, Scalar(0));
		 cvtColor(src, dest, CV_BGR2HLS_FULL);
		 for (int i = 0; i < src.rows ; i++)
		 {
			 for (int j = 0; j < src.cols ; j++)
			 {
				 if (dest.at<Vec3b>(i, j)[0] == 129 && dest.at<Vec3b>(i, j)[1] == 183 && dest.at<Vec3b>(i, j)[2] == 157)
					 res.at<uchar>(i, j) = 255;
			 }
		 }

		 imshow("windowa", res);
	 }
	 **/