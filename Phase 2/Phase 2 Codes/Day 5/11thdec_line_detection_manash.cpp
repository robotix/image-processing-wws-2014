// opencv_12th_1st_linedetection.cpp : Defines the entry point for the console application.
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


bool found = false;

int kernelx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
int kernely[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

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

void detect_lines(Mat input,int level,int my_threshold)
{
	int a_r = sqrt(pow((double)input.rows,2)+pow((double)input.cols,2)) + 1;
	int a_c = 181;
	Mat accumulator(a_r,a_c,CV_8UC1,Scalar(0));
	Mat accumulator1(a_r,a_c,CV_8UC1,Scalar(0));
	Mat output(input.rows,input.cols,CV_8UC1,Scalar(0));
	for(int i = 0; i<input.rows;i++)
	{
		for(int j = 0; j<input.cols;j++)
		{
			if(input.at<uchar>(i,j) > level)
			{
				found = true;
				for(int a = 0; a<a_c;a++)
				{
					int b = abs((j * cos((double)a*CV_PI/180)) + (i * sin((double)a*CV_PI/180)));
					int strength = accumulator.at<uchar>(b,a)+1;

					if(strength>255)strength = 255;
					
					accumulator.at<uchar>(b,a) = strength;
				}
			}

			if(found == true)
			{
				found = false;
				//imshow("accumulator",accumulator);
				//waitKey(0);

			}
			
		}
	}
	int max = 0;
	for(int i = 0; i<a_r;i++)
	{
		for(int j = 0; j<a_c;j++)
		{
			if(accumulator.at<uchar>(i,j) > max)
			{
				max = accumulator.at<uchar>(i,j);
			}
		}
	}

	//cout<<"1";

	for(int i = 0; i<a_r;i++)
	{
		for(int j = 0; j<a_c;j++)
		{
			//cout<<"2";
			if(accumulator.at<uchar>(i,j) > max-my_threshold)
			{
				// i = r; j = theta
				
				//double cc = i/sin(j * CV_PI/180);
				for(int a = 0; a< input.cols;a++)
				{
					//int b = tan((j-90)*CV_PI/180)*a + cc;

					int b = (i-a * cos(j * CV_PI/180)) / (sin(j * CV_PI/180));
					if(b<input.rows && b>-1)
					{
						output.at<uchar>(b,a) = 255;
					}
					
				}
			}
		}
	}

	cout<<"Number of Pixels in the longest line: "<<max<<endl;

	imshow("Huogh Diagram",accumulator);
	//imshow("accumulator1",accumulator1);
	imshow("Output",output);
	waitKey(0);
}

void detect_lines_gradient(Mat input,int level,int my_threshold)
{
	int i_r = input.rows;
	int i_c = input.cols;
	Mat output(input.rows,input.cols,CV_8UC1,Scalar(0));
	int **slopes;
	slopes = (int**)malloc(i_r*(sizeof(int*)));
	for(int i = 0; i<i_r;i++)
	{
		slopes[i] = (int*)malloc(i_c*(sizeof(int)));
	}

	int max = 0;
	int min = 999;

	for(int i = 0; i<i_r-3;i++)
	{
		for(int j = 0;j<i_c-3;j++)
		{
			int g_x = 0,g_y=0;
			for(int a = 0; a<3;a++)
			{
				for(int b = 0; b<3;b++)
				{
					g_x += input.at<uchar>(i+a,j+b)*kernelx[a][b];
					g_y += input.at<uchar>(i+a,j+b)*kernely[a][b];
				}
			}			

			if((g_x != 0 && g_y !=0))
			{
				//cout<<"g_y: "<<g_y<<" g_x: "<<g_x<<endl;
				int slope; 
				if(g_x !=0)
				{
					slope = g_y/g_x;
				}

				else
				{
					slope = 765;
				}
				
				slopes[i+1][j+1] = slope;
				if(max<slope)max=slope;
				if(min>slope)min=slope;
			}
		}
	}

	cout<<"min: "<<min<<" max: "<<max<<endl;

	for(int i = 0; i<input.rows;i++)
	{
		for(int j = 0; j<input.cols;j++)
		{
			if(slopes[i][j] > max-50)
			{
				output.at<uchar>(i,j) = 255;
			}
		}
	}

	imshow("Output",output);
	waitKey(0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	detect_lines(Mat input,int level,int my_threshold) level if the pixel value above which it will detect white pixel, threshold in the no of pixels in the smallest line you want to consider.
	*/
	Mat image = imread("C:\\Users\\acer\\Desktop\\lines3.jpg",CV_LOAD_IMAGE_GRAYSCALE); 
	int threshld = 0;
	cout<<"Enter the no of pixels of the smallest line that you want to include: "<<endl;
	cin>>threshld;
	imshow("Original",image);
	detect_lines(image,100,threshld);
	return 0;
}