// opencv_11th_2nd_blob.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<queue>
#include <stdlib.h>

using namespace std;
using namespace cv;

void detect_bw_blob_bfs(Mat input,int level)
{
	Point p;
	int count_blob = 1;
	queue<Point> q;
	Mat visited(input.rows,input.cols,CV_8SC1,Scalar(-1));
	for(int i = 1; i<input.rows-3;i++)
	{
		for(int j = 1; j<input.cols-3;j++)
		{
			if(input.at<uchar>(i,j) >level && visited.at<char>(i,j) == -1)
			{
				visited.at<char>(i,j) = 0;
				p.x = i; p.y = j;
				q.push(p);
				for(int a = -1; a<2;a++)
				{
					for(int b = -1; b<2; b++)
					{
						if(input.at<uchar>(i+a,j+b) > level && visited.at<char>(i+a,j+b) == -1)
						{
							visited.at<char>(i+a,j+b) = 0;
							p.x = i+a; p.y = j+b;
							q.push(p);
						}
					}
				 }
				visited.at<char>(i,j) = count_blob;
				q.pop();

				while(q.empty()==false)
				{
					p = q.front();
					int i = p.x;
					int j = p.y;
					for(int a = -1; a<2;a++)
					{
						for(int b = -1; b<2; b++)
						{
							if(input.at<uchar>(i+a,j+b) > level && visited.at<char>(i+a,j+b) == -1)
								{
									visited.at<char>(i+a,j+b) = 0;
									p.x = i+a; p.y = j+b;
									q.push(p);
								}
						}
					}
					visited.at<char>(i,j) = count_blob;
					q.pop();
				}// end of while loop

				count_blob++;

			}
		}
	}
	Mat blob(input.rows,input.cols,CV_8UC1,Scalar(0));
	for(int i = 0; i<input.rows;i++)
	{
		for(int j = 0; j<input.cols;j++)
		{
			if(visited.at<char>(i,j) != -1)
			{
				int m = visited.at<char>(i,j);
				blob.at<uchar>(i,j) = 255/(m);
			}
		}
	}
	imshow("Blob",blob);
}

void detect_color_blob_bfs(Mat input,int level)
{
	Point p;
	int count_blob = 1;
	queue<Point> q;
	Mat visited(input.rows,input.cols,CV_8SC1,Scalar(-1));
	for(int i = 1; i<input.rows-3;i++)
	{
		for(int j = 1; j<input.cols-3;j++)
		{
			if(input.at<Vec3b>(i,j)[1] > level && visited.at<char>(i,j) == -1)
			{
				visited.at<char>(i,j) = 0;
				p.x = i; p.y = j;
				q.push(p);
				for(int a = -1; a<2;a++)
				{
					for(int b = -1; b<2; b++)
					{
						if(input.at<Vec3b>(i+a,j+b)[1] > level && visited.at<char>(i+a,j+b) == -1)
						{
							visited.at<char>(i+a,j+b) = 0;
							p.x = i+a; p.y = j+b;
							q.push(p);
						}
					}
				 }
				visited.at<char>(i,j) = count_blob;
				q.pop();

				while(q.empty()==false)
				{
					p = q.front();
					int i = p.x;
					int j = p.y;
					for(int a = -1; a<2;a++)
					{
						for(int b = -1; b<2; b++)
						{
							if(input.at<Vec3b>(i+a,j+b)[1] > level && visited.at<char>(i+a,j+b) == -1)
								{
									visited.at<char>(i+a,j+b) = 0;
									p.x = i+a; p.y = j+b;
									q.push(p);
								}
						}
					}
					visited.at<char>(i,j) = count_blob;
					q.pop();
				}// end of while loop

				count_blob++;

			}
		}
	}
	//cout<<count_blob<<endl;
	Mat blob(input.rows,input.cols,CV_8UC1,Scalar(0));
	int *Amta;
	Amta = new int[count_blob-1];
	for(int i = 0;i<count_blob-1;i++)
	{
		Amta[i]=0;
	}
	//Amta[0] = 5;

	int red = 0;
	int blue = 0;
	int green = 0;
	int count_index = 1;
	int last_count = 0;
	for(int i = 0; i<input.rows;i++)
	{
		for(int j = 0; j<input.cols;j++)
		{
			if(visited.at<char>(i,j) != -1)
			{
				count_index = visited.at<char>(i,j);
				if(Amta[count_index-1] != 5)
				{
					Amta[count_index-1] = 5;

					/*for(int i = 0;i<count_blob-1;i++)
						{
							cout<<Amta[i]<<" , ";
						}
					cout<<endl;*/

				int color_local = input.at<Vec3b>(i,j)[0];
				//cout<<count_index<<" , "<<color_local<<endl;
				if(color_local >= 0 && color_local < 40)
				{
					red++;
				}
				else if(color_local > 60 && color_local < 100)
				{
					green++;
				}
				else if(color_local > 140 && color_local < 180)
				{
					blue++;
				}
				}
				//int m = visited.at<char>(i,j);
				blob.at<uchar>(i,j) = 255;
			}
		}
	}
	cout<<"Red = "<<red<<" Blue = "<<blue<<" Green = " <<green<<endl;
	//imshow("Blob",blob);
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	void detect_color_blob_bfs(Mat input,int level) level = 20
	void detect_bw_blob_bfs(Mat input,int level) level = 200
	*/
	Mat image = imread("C:\\Users\\acer\\Desktop\\blob.jpg",CV_LOAD_IMAGE_GRAYSCALE); // use CV_LOAD_IMAGE_COLOR for color and CV_LOAD_IMAGE_COLOR for bw
	//imshow("Original",image);
	//cvtColor(image,image,CV_BGR2HLS_FULL); // uncomment this for detect_color_blob_bfs function
	imshow("Original",image);
	//cout<<(int)image.at<Vec3b>(0,0)[1];
	detect_bw_blob_bfs(image,200);
	waitKey(0);
	return 0;
}