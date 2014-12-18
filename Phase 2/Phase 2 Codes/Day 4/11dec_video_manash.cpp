// opencv_10th_1st_edge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<math.h>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int my_threshold = 50;
Mat image;
Mat frame;



//float gaussian_filter[3][3] = {{0.06,0.098,0.06},{0.098,0.162,0.098},{0.06,0.098,0.06}};  
float gaussian_filter[3][3] = {{0.0625,0.125,0.0625},{0.125,0.25,0.125},{0.0625,0.125,0.0625}};

int sobel_x[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
int sobel_y[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

void insertion_sort(int arr[], int length) 
{
	int i, j ,tmp;
	for (i = 1; i < length; i++) 
	{
		j = i;
		while (j > 0 && arr[j - 1] > arr[j]) 
		{
			tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			j--;
		}
	}
 }

Mat make_grayscale(Mat picture)
{
	Mat img2(picture.rows,picture.cols,CV_8UC1);
	for (int i = 0; i<picture.rows;i++)
	{
		for(int j = 0; j<picture.cols;j++)
		{
		
			img2.at<uchar>(i,j) = picture.at<Vec3b>(i,j)[0]*0.56 + picture.at<Vec3b>(i,j)[1]*0.33 + picture.at<Vec3b>(i,j)[2]*0.11;
		}
	}
	
	return img2;
}

Mat make_binary(Mat picture,int threshold)
{
	Mat img2(image.rows,image.cols,CV_8UC1);

	for (int i = 0; i<image.rows;i++)
	{
		for(int j = 0; j<image.cols;j++)
		{
		
			img2.at<uchar>(i,j) = image.at<Vec3b>(i,j)[0]*0.56 + image.at<Vec3b>(i,j)[1]*0.33 + image.at<Vec3b>(i,j)[2]*0.11;
			if(img2.at<uchar>(i,j)>threshold)
			{
				img2.at<uchar>(i,j) = 255;
			}

			else
			{
				img2.at<uchar>(i,j) = 0;
			}
		}
	}
	return img2;
}

Mat detect_edge_3X3(Mat input)
{
	Mat edge(input.rows,input.cols,CV_8UC1,Scalar(0));	
	for(int i = 0; i<input.rows-3;i += 3)
	{
		for(int j = 0; j<input.cols-3;j += 3)
		{
			
			int max = 0;
			int min = 255;
			for(int a = 0; a<3;a++)
			{
				for(int b = 0; b<3;b++)
				{
					int value = input.at<uchar>(a+i,b+j);
					if(value>max)
					{
						max = value;						
					}

					else if(value < min)
					{
						min = value;
					}
					
				}
			}
			if(max-min > my_threshold)
			{
				edge.at<uchar>(i+1,j+1) = 255;
			}
		}
	}
	return edge;
}

Mat detect_edge_1X1(Mat input)
{
	Mat edge(input.rows,input.cols,CV_8UC1,Scalar(0));	
	for(int i = 0; i<input.rows-3;i++)
	{
		for(int j = 0; j<input.cols-3;j += 1)
		{
			
			int max = 0;
			int min = 255;
			for(int a = 0; a<3;a++)
			{
				for(int b = 0; b<3;b++)
				{
					int value = input.at<uchar>(a+i,b+j);
					if(value>max)
					{
						max = value;						
					}

					else if(value < min)
					{
						min = value;
					}
					
				}
			}
			if(max-min > my_threshold)
			{
				edge.at<uchar>(i+1,j+1) = 255;
			}
		}
	}
	return edge;
}

Mat detect_edge_Plus(Mat input)
{
	Mat edge(input.rows,input.cols,CV_8UC1,Scalar(0));	
	for(int i = 0; i<input.rows-3;i++)
	{
		for(int j = 0; j<input.cols-3;j += 1)
		{
			
			int max = 0;
			int min = 255;
			for(int a = 0; a<3;a++)
			{
				for(int b = 0; b<3;b++)
				{
					if((a == 0 && b == 1)||(a == 1 && b == 0)||(a == 1 && b == 1)||(a == 1 && b == 2)||(a == 2 && b == 1))
					{

					
					int value = input.at<uchar>(a+i,b+j);
					if(value>max)
					{
						max = value;						
					}

					else if(value < min)
					{
						min = value;
					}
					}

					
				}
			}
			if(max-min > my_threshold)
			{
				edge.at<uchar>(i+1,j+1) = 255;
			}
		}
	}
	return edge;
}

Mat detect_edge_3X1(Mat input)
{
	Mat edge(input.rows,input.cols,CV_8UC1,Scalar(0));	
	for(int i = 0; i<input.rows;i++)
	{
		for(int j = 0; j<input.cols-3;j += 1)
		{
			
			int max = 0;
			int min = 255;
			for(int a = 0; a<3;a++)
			{
				
					
					int value = input.at<uchar>(i,a);
					if(value>max)
					{
						max = value;						
					}

					else if(value < min)
					{
						min = value;
					}
				
			}
			if(max-min > my_threshold)
			{
				edge.at<uchar>(i,j+1) = 255;
			}
		}
	}
	return edge;
}

Mat detect_edge_vector(Mat input)
{
	Mat edge(input.rows,input.cols,CV_8UC1,Scalar(0));	
	for(int i = 0; i<input.rows-3;i++)
	{
		for(int j = 0; j<input.cols-3;j++)
		{
			int dx = 0;
			int dy = 0;

			dx = -input.at<uchar>(i,j) - input.at<uchar>(i+1,j) - input.at<uchar>(i+2,j) + input.at<uchar>(i,j+2) + input.at<uchar>(i+1,j+2) + input.at<uchar>(i+2,j+2);
			dy = -input.at<uchar>(i,j) - input.at<uchar>(i,j+1) - input.at<uchar>(i,j+2) + input.at<uchar>(i+2,j) + input.at<uchar>(i+2,j+1) + input.at<uchar>(i+2,j+2);
			int strength = sqrt(pow((double)dx,2)+pow((double)dy,2));

			//strength = sqrt((double)(dx+dy));

			strength = strength - my_threshold;
			if(strength>255)
			{
				strength = 255;
			}

			else if(strength<0)
			{
				strength = 0;
			}
			edge.at<uchar>(i+1,j+1) = strength;
			
		}
	}
	return edge;
}

Mat refine_edge(Mat input)
{
	Mat edge;
	input.copyTo(edge);
	for(int i = 0; i<input.rows-3;i++)
	{
		for(int j = 0; j<input.cols-3;j++)
		{
			int max = 0;
			int index = 0;
			for(int a = 0; a<3;a++)
			{
				if(edge.at<uchar>(i,j+a) - 10 < 0)
				{
					edge.at<uchar>(i,j+a) = 0;
				}
				if(input.at<uchar>(i,j+a) > max)
				{
					max = input.at<uchar>(i,j+a);
					index = a;
				}
			}
			//edge.at<uchar>(i,j+index) = edge.at<uchar>(i,j+index) - 10;
			edge.at<uchar>(i,j+index) = edge.at<uchar>(i,j+index) + 30;
		}
	}
	return edge;
}

Mat dilate(Mat input,int size)
{
	Mat edge(input.rows,input.cols,CV_8UC1,Scalar(0));	
	for(int i = 0; i<input.rows-size;i++)
	{
		for(int j = 0; j<input.cols-size;j++)
		{
			int local_sum = 0;
			for(int a = 0; a<size; a++)
			{
				for(int b = 0; b<size;b++)
				{
					local_sum += input.at<uchar>(i+a,j+b);
				}
			}
			int no_white = local_sum / 255;
			if(no_white > ((size*size)-1)/2)
			{
				edge.at<uchar>(i+((size-1)/2),j+((size-1)/2)) = 255;				
			}

			else
			{
				edge.at<uchar>(i+((size-1)/2),j+((size-1)/2)) = 0;	
			}
		}
	}
	return edge;
}

Mat erode(Mat input,int size)
{
	//Mat edge(input.rows,input.cols,CV_8UC1,Scalar(0));	
	Mat edge;
	input.copyTo(edge);
	for(int i = 0; i<input.rows-size;i++)
	{
		for(int j = 0; j<input.cols-size;j++)
		{
			int local_sum = 0;
			for(int a = 0; a<size; a++)
			{
				for(int b = 0; b<size;b++)
				{
					local_sum += input.at<uchar>(i+a,j+b);
				}
			}
			int no_white = local_sum / 255;
			if(no_white > ((size*size)-1)/2 && no_white < (size*size))
			{
				edge.at<uchar>(i+((size-1)/2),j+((size-1)/2)) = 0;				
			}

			else if(no_white < ((size*size)-1)/2 && no_white > 0)
			{
				edge.at<uchar>(i+((size-1)/2),j+((size-1)/2)) = 255;	
			}
		}
	}
	return edge;
}

Mat my_gaussianBlur(Mat input)
{
	Mat output(input.rows,input.cols,CV_8UC1,Scalar(0));
	for(int i = 0;i<input.rows-3;i+=1)
	{
		for(int j = 0; j<input.cols-3;j+=1)
		{
			int g = 0;
			for(int a = 0; a<3;a++)
			{
				for(int b = 0; b<3;b++)
				{
					g += input.at<uchar>(i+a,j+b)*gaussian_filter[a][b];
				}
			}
			//g+=10;
			if(g>255)
			{
				g == 255;
			}
			else if(g<0)
			{
				g = 0;
			}
			output.at<uchar>(i+1,j+1) = g;
		}
	}

	return output;
}

Mat my_medianBlur(Mat input)
{	
	Mat output(input.rows,input.cols,CV_8UC1,Scalar(0));
	for(int i = 0;i<input.rows-3;i+=1)
	{
		for(int j = 0; j<input.cols-3;j+=1)
		{
			int g = 0;
			int values[9];
			int index = 0;
			for(int a = 0; a<3;a++)
			{
				for(int b = 0; b<3;b++)
				{					
					values[index] = input.at<uchar>(i+a,j+b);
					index++;
				}
			}

			insertion_sort(values, 9);		
			output.at<uchar>(i+1,j+1) = values[5];
		}
	}

	return output;
}

Mat my_averageBlur(Mat input,int size)
{	
	Mat output(input.rows,input.cols,CV_8UC1,Scalar(0));
	for(int i = 0;i<input.rows-size;i+=1)
	{
		for(int j = 0; j<input.cols-size;j+=1)
		{
			int avb = 0;
			for(int a = 0; a<size;a++)
			{
				for(int b = 0; b<size;b++)
				{					
					avb += input.at<uchar>(i+a,j+b);
				}
			}

			avb = avb/(size*size);
			output.at<uchar>(i+1,j+1) = avb;
		}
	}

	return output;
}

Mat my_Canny(Mat input,int t1,int t2)
{	
	Mat output(input.rows,input.cols,CV_8UC1,Scalar(0));

	// Noise Reduction
	GaussianBlur(input,input,Size(5,5),0,0);

	// Finding Intensity Gradient of the Image

	for(int i = 0;i<input.rows-3;i+=1)
	{
		for(int j = 0; j<input.cols-3;j+=1)
		{
			double gx = 0,gy = 0;

			for(int a = 0; a<3;a++)
			{
				for(int b = 0; b<3;b++)
				{					
					gx += input.at<uchar>(a+i,b+j)*sobel_x[a][b];
					gy += input.at<uchar>(a+i,b+j)*sobel_y[a][b];
				}
			}

			double G = sqrt(pow(gx,2)+pow(gy,2));
			double g_angle = atan(gy/gx)* 180 / 3.14;
			
			//output.at<uchar>(i+1,j+1) = avb;
		}
	}

	return output;
}



int _tmain(int argc, _TCHAR* argv[])
{	
	int t2 = 50;
	int t1 = 100;
	namedWindow("Camera",CV_WINDOW_AUTOSIZE);
	//createTrackbar("T1","Camera",&t2,255,on_trackbar);
	//createTrackbar("T2","Camera",&t1,255,on_trackbar);
	VideoCapture camera(1);
	camera>>frame;
	//Mat frame;
	while(1)
	{
		camera>>frame;
		
		cvtColor(frame,frame,CV_BGR2HSV);
		//Mat img = detect_edge_1X1(frame);
		imshow("Camera",frame);
		int a = waitKey(1);
		if(a == 27)
		{
			return 0;
		}
	}
	return 0;
}