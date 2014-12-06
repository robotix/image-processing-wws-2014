#include "stdafx.h"
#include "opencv2/core/core.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <queue>

using namespace std;
using namespace cv;


typedef struct pt_{
	int x, y;
}pt;

typedef struct blob_{

	int min_x, max_x;
	int min_y, max_y;
	int cen_x, cen_y;
	int n_pixels;
	int ID;
}blob;

void GetBlobs(Mat img, vector<blob> blobs)
{

	int i, j, k, l, r = img.rows, c = img.cols, id = 1;
	vector<vector<int> > pixel_ID(r, vector<int>(c, -1)); 
	queue<pt> open_list; 

	for (i = 1; i<r - 1; i++)
	{
		for (j = 1; j<c - 1; j++)
		{
			//if (img.at<uchar>(i, j) == 0) pixel_ID[i][j] = 0;
			if (img.at<uchar>(i, j) == 0 || pixel_ID[i][j]>-1)
				continue;
			pt start = { j, i };

			open_list.push(start);
			int sum_x = 0, sum_y = 0, n_pixels = 0, max_x = 0, max_y = 0;
			int min_x = c + 1, min_y = r + 1;
			while (!open_list.empty()){
				
				pt top = open_list.front();
				open_list.pop();
				pixel_ID[top.y][top.x] = id;
				n_pixels++;

				
				min_x = (top.x<min_x) ? top.x : min_x;
				min_y = (top.y<min_y) ? top.y : min_y;
				max_x = (top.x>max_x) ? top.x : max_x;
				max_y = (top.y>max_y) ? top.y : max_y;
				sum_y += top.y; sum_x += top.x;

				
				for (k = top.y - 1; k <= top.y + 1; k++){
					for (l = top.x - 1; l <= top.x + 1; l++){
						if (img.at<uchar>(k, l) == 0 || pixel_ID[k][l]>-1)
							continue;
						pt next = { l, k };
						pixel_ID[k][l] = id;
						open_list.push(next);
					}
				}
			}
			if (n_pixels < 15) 
				continue;
			blob nextcentre = { min_x, max_x, min_y, max_y, sum_x / n_pixels, sum_y / n_pixels, id };
			blobs.push_back(nextcentre);
			id++;
			
		}
	}

	cout << blobs.size();
}

int main(){

	
/*	cout << "Enter name of file:";
	cin >> fname;*/
	Mat image = imread("blobs.jpg",CV_LOAD_IMAGE_COLOR);
	
	if (image.empty())
		exit(1);
	imshow("in", image);
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
	namedWindow("My Window", CV_WINDOW_AUTOSIZE);
	

	vector<blob> blobs;
	GetBlobs(final, blobs);
	imshow("My Window", final);
	waitKey(0);

	return 0;


}