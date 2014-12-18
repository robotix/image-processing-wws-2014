#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <queue>

using namespace cv;
using namespace std;



void TrakerBar_Creater_Grey(Mat);
Mat conv_grey(Mat);
Mat conv_binary(Mat, int);
Mat invert_color_img(Mat);
Mat invert_grey_img(Mat);
Mat build_Histogram(Mat);
int Binary_Thresh(Mat);
void TrakerBar_Creater_Grey(Mat);
void TrakerBar_Creater_Color(Mat);
Mat Display_Border(Mat, int);
Mat Border_Creater_Algo(Mat);
void Display_Border_With_Trackbar(Mat);
Mat Delation(Mat);
Mat Erosion(Mat);
Mat Median_Filter(Mat);
Mat Gaussian_Filter(Mat);
void swap(int *, int *);
void insert_sort(int *, int);
Mat Invert_Color(Mat);
int Check_Kernel(int , int , int , int , int , int);
Mat Blob_Detection_GREYSCALE(Mat);
Mat Blob_Detection_GREYSCALE1(Mat);
Mat Blob(Mat);

Mat Blob(Mat img)
{
	queue<Point> q;
	int i, j, c = 1, m, n;
	Mat x(img.rows, img.cols, CV_8SC1, Scalar(-1));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			m = i; n = j;
			if (img.at<uchar>(i, j) == 255 && x.at<schar>(i, j) == -1)
			{
				Point temp(m,n);
				q.push(temp);
				x.at<schar>(i, j) = c;
				while (!q.empty())
				{for (int k = m - 1; k <= m + 1; k++)
				  {for (int l = n - 1; l <= n + 1; l++)
			  	     {
					  if (img.at<uchar>(k, l) == 255 && x.at<schar>(k, l) == -1)
					  {
						Point temp3(k, l);
						q.push(temp3);
						x.at<schar>(k, l) = c;
				      }
				     }
				  }

					q.pop();
					if (!q.empty())
					{
						Point temp2;
						temp2 = q.front();
						m = temp2.x;
						n = temp2.y;
					}
				}
				c++;
			}
		}
	}
	Mat y(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (x.at<schar>(i, j) != -1)
				y.at<uchar>(i, j) = 50*x.at<schar>(i, j);
		}
	}
	return y;
}


void Check_Kernel(int **img, int **temp, int x, int y, int Blob_Count,int *check)
{
	int k, m;
	for (k = -1; k < 2; k++)
	for (m = -1; m < 2; m++)
	 if ((temp[x + m][y + k] == -1) && (img[x + m][y + k] == 255) && (x + m >= 0) && (x + m <= 9) && (y + k >= 0) && (y + k <= 9))
	 {
		++(*check);
		temp[x + m][y + k] = Blob_Count;
	    Check_Kernel(img, temp, x + m, y + k, Blob_Count,check);
	  }
	 return;
}

Mat Blob_Detection_GREYSCALE(Mat image)
{
	int i, j, Blob_Color = 50,rows=image.rows,cols=image.cols;
	 int check_;
	 int **img;
		 img = new int*[rows];

	 for (i = 0; i < rows; i++)
		 img[i] = new int[cols];

	 for (i = 0; i < (rows); i++)   // iniialising temp with -1 .
	 for (j = 0; j < (cols); j++)
		 img[i][j] = image.at<uchar>(i,j);

		 
		 int **temp;
	temp = new int*[rows];

	for (i = 0; i < rows; i++)
		temp[i] = new int[cols];

	for (i = 0; i < (rows); i++)   // iniialising temp with -1 .
	for (j = 0; j < (cols); j++)
		temp[i][j] = -1;

	for (i = 0; i < (rows); i++)
	  for (j = 0; j < (cols); j++)
	  {
		check_ = 0;
		if ((img[i][j]) == 255 && temp[i][j] == -1)
		{
			temp[i][j] = Blob_Color;
			Check_Kernel(img, temp, i, j, Blob_Color , &check_);           
		}

		if (check_>0)	 Blob_Color += 50;
	  }

	for (i = 0; i < (rows); i++)
	for (j = 0; j < (cols); j++)
	{
		if ((temp[i][j])> 0)
			img[i][j] = temp[i][j];
		else
			img[i][j] = img[i][j];
	}


	Mat x(image.rows,image.cols,CV_8UC1);
	for (i = 0; i < (rows); i++)
	for (j = 0; j < (cols); j++)
	{
		if ((temp[i][j])> 0)
			x.at<uchar>(i,j) = temp[i][j];
		else
			x.at<uchar>(i,j) = 255;
	}

	return x;
}


Mat Invert_Color(Mat img)
{
	Mat invert(img.rows, img.cols, CV_8UC3,Scalar(0));
	int i, j;
	
	for (i = 0; i < (img.cols); i++)
	for (j = 0; j < (img.rows); j++)
	{
		invert.at<Vec3b>(j, i)[0] = 255 - img.at<Vec3b>(j, i)[0];
		invert.at<Vec3b>(j, i)[1] = 255 - img.at<Vec3b>(j, i)[1];
		invert.at<Vec3b>(j, i)[2] = 255 - img.at<Vec3b>(j, i)[2];
	}

	return invert;
}

void swap(int *x, int *y)
{
	int t;
	t = *x;
	*x = *y;
	*y = t;
}


void insert_sort(int A[], int n)  //In iscending Order.
{
	for (int i = 1; i<n; i++)
	{
		int j = i;
		while (j>0 && (A[j]<A[j - 1]))
		{
			swap(A[j], A[j - 1]);
			j--;
		}
	}
}



Mat Median_Filter(Mat img)
{
	int i, k, m, temp, j, sum_bl, sum_wh;
	int A[9];
	Mat img_out(img.rows, img.cols, CV_8UC1); // To return
	img_out = img;

	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{   
		temp = 0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			A[temp] = (img_out.at<uchar>(j + k, i + m));
			temp++;
		}

		insert_sort(A,9);
		img_out.at<uchar>(j, i) = A[4];
	}

	return img_out;
}

Mat Gaussian_Filter(Mat img)
{
	int i, k, m, temp, j, sum_bl, sum_wh;
	int B, A[9] = { 60, 96, 60, 96, 159, 96, 60, 96, 60 };
	Mat img_out(img.rows, img.cols, CV_8UC1); // To return
	img_out = img;

	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{
		temp = 0,B=0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			B += (img_out.at<uchar>(j + k, i + m))*A[temp];
			img_out.at<uchar>(j, i) = B/786;
			temp++;
		}
	}

	return img_out;
}


Mat Erosion(Mat img) //Has bug, pls check
{
	int i, k,m,temp, j, sum_bl, sum_wh;

    Mat img_out(img.rows, img.cols, CV_8UC1,Scalar(0)); // To return
	img.copyTo(img_out);
	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{
		sum_bl = 0; sum_wh = 0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			if ((img.at<uchar>(j + k, i + m)) == 0)
				sum_bl++;
			else
				sum_wh++;
		}

		if (sum_bl<sum_wh)
		{
			if (sum_bl != 0)
				img_out.at<uchar>(j, i) = 0;
			else
				img_out.at<uchar>(j, i) = 255;
		}
		
		else if (sum_bl>sum_wh)
		{
			if (sum_wh != 0)
				img_out.at<uchar>(j, i) = 255;
			else
				img_out.at<uchar>(j, i) = 0;
		}
		else
			img_out.at<uchar>(j, i) = img.at<uchar>(j, i);
	}

	return img_out;
}

Mat Delation(Mat img)
{
	int i, thresh, temp,k,m, j, sum_bl, sum_wh;

	Mat x(img.rows, img.cols, CV_8UC1); //To use
	Mat img_out(img.rows, img.cols, CV_8UC1); // To return
	img.copyTo(x);
	
	for (i = 1; i < (img.cols - 1); i++)
	for (j = 1; j < (img.rows - 1); j++)
	{
		sum_bl = 0; sum_wh = 0;
		for (k = -1; k < 2; k++)
		for (m = -1; m < 2; m++)
		{
			if ((x.at<uchar>(j + k, i + m)) <128 )
				sum_bl++;
				else
				sum_wh++;
		}
				if (sum_bl>sum_wh )
				img_out.at<uchar>(j, i) = 0;
				else
				img_out.at<uchar>(j, i) = 255;
			
	}
	

	return img_out;
}

Mat Border_Creater_Algo(Mat img) //Enter color img  , get binary img
{ 
	int i, m, k, temp, j, sum_x, sum_y;

	Mat x(img.rows, img.cols, CV_8UC1);
	Mat img_out(img.rows, img.cols, CV_8UC1);
	
	x = conv_grey(img);
	
	for (i = 1; i < (img.cols-1); i++)
	for (j = 1; j < (img.rows-1); j++)
	{
		sum_x = 0; sum_y = 0;

		for (k = -1; k < 2; k++)
		{
			sum_x += (x.at<uchar>(j + k, i - 1)) - (x.at<uchar>(j + k, i + 1));
			sum_y += (x.at<uchar>(j - 1, i + k)) - (x.at<uchar>(j + 1, i + k));
		}

		temp = sqrt( (sum_x*sum_x) + (sum_y*sum_y) );
		
		if (temp<256)
		img_out.at<uchar>(j, i) = temp;
		else
		img_out.at<uchar>(j, i) = 0;

	}

	return img_out;
}


Mat conv_grey(Mat img)
{
	int i, j, temp;
	Mat img_grey(img.rows, img.cols, CV_8UC1);

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		temp = ((img.at<Vec3b>(j, i)[0])*(0.56)) + ((img.at<Vec3b>(j, i)[1])*(0.33)) + ((img.at<Vec3b>(j, i)[2])*(0.11));
		img_grey.at<uchar>(j, i) = temp;
	}

	return img_grey;
}

Mat conv_binary(Mat img,int thresh)  //Input grey img.
{
	int i, j;

	Mat img_bin(img.rows, img.cols, CV_8UC1);
	img_bin = img;

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		if ((img_bin.at<uchar>(j, i)) > thresh)
		img_bin.at<uchar>(j, i) = 255;
		else
		img_bin.at<uchar>(j, i) = 0;
    }
	return img_bin;
}

Mat invert_color_img(Mat img)
{
	int i, j;
	Vec3b temp;
	for (i = 0; i < img.cols; i++)
	for (j = 0; j < (img.rows)/2; j++)
	{
		temp.val[0] = img.at<Vec3b>(j, i)[0];
		temp.val[1] = img.at<Vec3b>(j, i)[1];
		temp.val[2] = img.at<Vec3b>(j, i)[2];

		img.at<Vec3b>(j, i)[0] = img.at<Vec3b>(((img.rows-1) - j), i)[0];
		img.at<Vec3b>(j, i)[1] = img.at<Vec3b>(((img.rows-1) - j), i)[1];
		img.at<Vec3b>(j, i)[2] = img.at<Vec3b>(((img.rows-1) - j), i)[2];

		img.at<Vec3b>(((img.rows-1) - j), i)[0] = temp.val[0];
		img.at<Vec3b>(((img.rows-1) - j), i)[1] = temp.val[1];
		img.at<Vec3b>(((img.rows-1) - j), i)[2] = temp.val[2];
	}

	return img;
}

Mat invert_grey_img(Mat img)
{
	int i, j,temp;

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < (img.rows) / 2; j++)
	{
		temp=img.at<uchar>(j, i);
		img.at<uchar>(j, i) = img.at<uchar>(((img.rows - 1) - j), i);
		img.at<uchar>(((img.rows - 1) - j), i) = temp;
	}

	return img;
}


Mat build_Histogram(Mat img)  //Pass any greyscale image.
{
	long N = img.rows * img.cols;
	
	int i, j, temp;
	long A[256] = { 0 };


	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		temp = img.at<uchar>(j,i);
		A[temp]++;
	}
	
	//for finding max.m pixel .
	int max = A[i];
	for (i = 0; i < 256;i++)
	if (A[i]>max)
		max = A[i];
	
	Mat x( ( (max+20)/20 ), 260, CV_8UC1);
	//For making Histgram .
	for (i = 0; i < 256; i++)
	for (j = 0; j < max/20; j++)
	{
		if (j<A[i]/20)
			x.at<uchar>(j, i) = 0;
		else
			x.at<uchar>(j, i) = 255;
	}
   x = invert_grey_img(x);

	return x;
}

int Binary_Thresh(Mat img) //Pass any greyscale image. 
{
	Mat x(260, 260, CV_8UC1);
	int N, s = 0, i, j, temp;
	long A[256] = { 0 };

	N = (img.rows) * (img.cols);

	for (i = 0; i < img.cols; i++)
	for (j = 0; j < img.rows; j++)
	{
		temp = img.at<uchar>(j, i);
		A[temp]++;
	}


	for (i = 0; i < 256; i++)
	{
		if ((s + A[i]) <= (N / 2))
			s += A[i];
		else
			break;
	}

	return i;
}


Mat Display_Border(Mat img, int Border_Thesh)
{
	Mat x(img.rows, img.cols, CV_8UC1), image(img.rows, img.cols, CV_8UC1);
	image = conv_grey(img);
	int i, j, k, m, max, min;
	for (i = 0; i < (img.cols); i++)
	{
		for (j = 0; j < (img.rows); j++)
		{
			if (i == 0 || j == 0 || i == (img.cols - 1) || j == (img.rows - 1))
				x.at<uchar>(j, i) = 0;
			else
			{
				max = image.at<uchar>(j, i); min = image.at<uchar>(j, i);
				for (k = -1; k < 2; k++)
				for (m = -1; m < 2; m++)

				{
					if ((image.at<uchar>(j + m, i + k))>max)
						max = x.at<uchar>(j + m, i + k);
					if ((image.at<uchar>(j + m, i + k)) < min)
						min = x.at<uchar>(j + m, i + k);
				}

				if (max - min >= Border_Thesh)
					x.at<uchar>(j, i) = 0;
				else
					x.at<uchar>(j, i) = 255;
			}
		}
	}
	return x;
}

void TrakerBar_Creater_Color(Mat img_load)
{
	int default_thresh = 10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
	createTrackbar("TC1", "WINDOWS1", &default_thresh, 255);
	createTrackbar("TC2", "WINDOWS1", &default_thresh, 255);
	createTrackbar("TC3", "WINDOWS1", &default_thresh, 255);

	while (1)
	{
		Mat bin = conv_binary(img_load, default_thresh);
		imshow("WINDOWS1", bin);
		char a = waitKey(33);
		if (a == 27)break;
	}
}

void TrakerBar_Creater_Grey(Mat img)
{
int default_thresh = 10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "WINDOWS1", &default_thresh, 255);

	while (1)
	{
		Mat bin = conv_binary(img, default_thresh);
		imshow("WINDOWS1", bin);
		char a = waitKey(33);
		if (a == 27)break;
	}

}


void Display_Border_With_Trackbar(Mat img)
{
	Mat x;
	int default_thresh = 10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "WINDOWS1", &default_thresh, 255);

	while (1)
	{
		x = Display_Border(img, default_thresh);
		imshow("WINDOWS1", x);
		char a = waitKey(33);
		if (a == 27)break;
	}

}

//Prog to conv RGB to HSL.
int main()
{
	int i, j;
	Mat img_load;
	img_load = imread("H://wallpapers//test2.png", CV_LOAD_IMAGE_COLOR);

	Mat temp(img_load.rows, img_load.cols, CV_8UC3);

	img_load.copyTo(temp);
	namedWindow("Original",WINDOW_AUTOSIZE);
	imshow("Original",img_load);

	Mat x(img_load.rows, img_load.cols, CV_8UC3);
	
	cvtColor(temp, x, CV_BGR2HLS_FULL);
	namedWindow("HSV Applied", WINDOW_AUTOSIZE);
	namedWindow("HSV", WINDOW_AUTOSIZE);
	
	int lower_h = 0, upper_h = 239, lower_s = 0, upper_s = 240, lower_l = 0, upper_l = 240;
	
	createTrackbar("lower_h", "HSV Applied", &lower_h, 239);
	createTrackbar("upper_h", "HSV Applied", &upper_h, 239);
	createTrackbar("lower_s", "HSV Applied", &lower_s, 240);
	createTrackbar("upper_s", "HSV Applied", &upper_s, 240);
	createTrackbar("lower_l", "HSV Applied", &lower_l, 240);
	createTrackbar("upper_l", "HSV Applied", &upper_l, 240);

	
	while (1)
	{
		for (i = 0; i < (img_load.cols); i++)
		for (j = 0; j < (img_load.rows); j++)
		{
			if ( (x.at<Vec3b>(j, i)[0] >= lower_h) && (x.at<Vec3b>(j, i)[0] <= upper_h) && (x.at<Vec3b>(j, i)[1] >= lower_s) && (x.at<Vec3b>(j, i)[1] <= upper_s) && (x.at<Vec3b>(j, i)[2] >= lower_l) && (x.at<Vec3b>(j, i)[2] <= upper_l) )
			{
				img_load.at<Vec3b>(j, i)[0] = img_load.at<Vec3b>(j, i)[0];
				img_load.at<Vec3b>(j, i)[1] = img_load.at<Vec3b>(j, i)[1];
				img_load.at<Vec3b>(j, i)[2] = img_load.at<Vec3b>(j, i)[2];
			}
			else
			{
                img_load.at<Vec3b>(j, i)[0] = 255;
				img_load.at<Vec3b>(j, i)[1] = 255;
				img_load.at<Vec3b>(j, i)[2] = 255;
			}
		}

		imshow("HSV", img_load);

		char a=waitKey(33);

		if (a == 27) break;
	}

	return 0;
}

*/

//Prog for Blob detection .

int main()
	{
		int i, j;
		Mat img_load;
		img_load = imread("H://wallpapers//test_img.png", CV_LOAD_IMAGE_GRAYSCALE);
	
		
		int **img;

		img = new int*[img_load.rows];

		for (i = 0; i < img_load.rows; i++)
			img[i] = new int[img_load.cols];

		for (i = 0; i < (img_load.rows); i++)
		for (j = 0; j < (img_load.cols); j++)
			img[i][j] = img_load.at<uchar>(i,j) ;   // Initialising temp. 2D array

		namedWindow("Original", WINDOW_AUTOSIZE);  // For Original img
		imshow("Original", img_load);
		waitKey(2000);

		Mat img_out;
		img_out=Blob(img_load);

	/*	for (i = 0; i < (img_load.rows); i++)
		for (j = 0; j < (img_load.cols); j++)
			img_load.at<uchar>(i, j) = img[i][j];   // Initialising temp. 2D array
			*/
		namedWindow("Blob", WINDOW_AUTOSIZE);  // For Original img
		imshow("Blob", img_out);
		waitKey(0);


		return 0;
	}