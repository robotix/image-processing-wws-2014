#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <queue>
#include <vector>

using namespace cv;
using namespace std;

typedef struct Point2D{
	int x, y;
}Point2D;

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
void Hough_Trans(Mat img);



void Hough_Trans(Mat img)
{
	namedWindow("LINE", WINDOW_AUTOSIZE);
	imshow("LINE", img);
	waitKey(2000);
	cout << " OK";
	int k, l, x, y,max;

	max = sqrt((img.rows*img.rows) + (img.cols*img.cols));
	const int cols = 181;
	const int rows = max;

	int r_max = sqrt((img.cols*img.cols) + (img.rows*img.rows));
	max = (cols > rows) ? cols : rows;
	


	int **A;
	A = new int*[r_max+2];    //A - r_x,theta_y
	for (x = 0; x < r_max+2; x++)
		A[x] = new int[r_max+2];

	for (x = 0; x < r_max+2; x++)
	for (y = 0; y < r_max+2; y++)
		A[x][y] = 0;

	
	for (y = 0; y < img.rows; y++)
	for (x = 0; x < img.cols; x++)
	{	
		if ( (img.at<uchar>(y,x)) >5 )
		{
			int m, r;
			float t=0;
			for (m = 0; m < 181; m++)
			{
				r = abs( (int)(x*1.0*(cos(t)) + y*1.0*(sin(t))) );
				t = m*CV_PI / 180;  //Converting angle to radians
				
			   	A[m][r] ++;
			}
		}
	}
	
//Creating Threshold.
	int thresh = 5;
	namedWindow("LINE1", WINDOW_AUTOSIZE);
	createTrackbar("Line Thresh", "LINE1", &thresh, 100000);


	max = A[0][0];
	int x_max = 0, y_max = 0;

	for (y = 0; y < rows; y++)
	for (x = 0; x < 181; x++)
	if (max < A[x][y])
	{
		x_max = x;
		y_max = y;
		max = A[x][y];
	}
	
//Giving thresh.
	if (max >= thresh)
	{
		Mat Display(img.rows, img.cols, CV_8UC1, Scalar(0));
		int i, j, x;
		float t = x_max*1.0*(CV_PI) / 180;

		for (x = 1; x < img.cols; x++)
		{
			int y = (y_max / (sin(t))) + ((0 - x) / tan(t));
			if (y >= 0 && y < (img.rows))
				Display.at<uchar>(y, x) = 255;
		}

		imshow("LINE1", Display);
		char a = waitKey(0);
	}

	
	while (1)
	{
		while (1)
		{
			if (max >= thresh)
			{
				Mat Display(img.rows, img.cols, CV_8UC1, Scalar(0));
				int i, j, x;
				float t = x_max*1.0*(CV_PI) / 180;

				for (x = 1; x < img.cols; x++)
				{
					int y = (y_max / (sin(t))) + ((0 - x) / tan(t));
					if (y >= 0 && y < (img.rows))
						Display.at<uchar>(y, x) = 255;
				}

				imshow("LINE1", Display);
			}
			
			char a = waitKey(33);
			if (a == 27)
			{
				max = 0;
				A[y_max][x_max] = 0;

				for (y = 0; y < rows; y++)
				for (x = 0; x < 181; x++)
				if (max < A[x][y])
				{
					x_max = x;
					y_max = y;
					max = A[x][y];
				}

				break;
			}
		}
		char b = waitKey(0);
		if (b == 27)break;
	}
}		

Mat Blob(Mat img)
{
	queue<Point> q;
	int i, j, c = 1, m, n,check;
	Mat x(img.rows, img.cols, CV_8SC1, Scalar(-1));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
		//	check = 0;
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
						 // check++;
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
			c=c+10;
			}
		}
	}
	Mat y(img.rows, img.cols, CV_8UC1, Scalar(255));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (x.at<schar>(i, j) != -1)
				y.at<uchar>(i, j) = x.at<schar>(i, j);
		}
	}
	return y;
}

//Blob_Recursive function has load.
/*void Check_Kernel(Mat image, int **temp, int x, int y, int Blob_Count)
{
	int k, m;
	for (k = -1; k < 2; k++)
	for (m = -1; m < 2; m++)
	 if ((temp[y+k][x + m] == -1) && (image.at<uchar>(y + k,x + m) == 255) && (x + m >= 0) && (x + m <= image.rows-1) && (y + k >= 0) && (y + k <= image.cols-1))
	 {
		temp[y+k][x + m] = Blob_Count;
		Check_Kernel(image, temp, x + m, y + k, Blob_Count);
	 }
	 return;
}

Mat Blob_Detection_GREYSCALE(Mat image)   //It has a bug.
{
	int i, j, Blob_Color = 1,rows=image.rows,cols=image.cols;
	int max;
	max = image.rows > image.cols ? image.rows : image.cols;
	
     int **img;
 	 img = new int*[max];
     for (i = 0; i < max; i++)
		 img[i] = new int[max];

	 for (i = 0; i < (rows); i++)   // iniialising img with image .
	 for (j = 0; j < (cols); j++)
		 img[i][j] = image.at<uchar>(i,j);  //Colums then Rows.

		 
	 // Creating Accumulator Array
	 int **accu;
	 accu = new int*[max];
	 for (i = 0; i < max; i++)
		 accu[i] = new int[max];

	 for (i = 0; i < (rows); i++)   // iniialising accu with -1 .
	 for (j = 0; j < (cols); j++)
		 accu[i][j] = -1;  //Colums then Rows.


	for (i = 0; i < (rows); i++)
	  for (j = 0; j < (cols); j++)
	  {
		if ((img[i][j]) == 255 && accu[i][j] == -1)
		{
			accu[i][j] = Blob_Color;
			Check_Kernel(image, accu, i, j, Blob_Color);// , &check_);           
		
			Blob_Color+=10;
		}
	  }

	for (i = 0; i < (rows); i++)
	for (j = 0; j < (cols); j++)
	{
		if ((accu[i][j])> 0)
			img[i][j] = accu[i][j];
		else
			img[i][j] = img[i][j];
	}


	Mat x(image.rows,image.cols,CV_8UC1);
	for (i = 0; i < (rows); i++)
	for (j = 0; j < (cols); j++)
	{
		if ((accu[i][j])>= 0)
			x.at<uchar>(i,j) = accu[i][j];
		else
			x.at<uchar>(i,j) = 255;
	}

	return x;
}
*/


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

Mat Prewit(Mat img) //Enter color img  , get binary img
{ 
	int i, k, temp, j, sum_x, sum_y;

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




#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "functions.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;



//Code for histogram (Uncomment it to use and comment the trackbar code main())
/*
int main()
{
	int i,j,N;
	int thresh;
	Mat img_load;
	img_load=imread("H://wallpapers//fruits.jpg",CV_LOAD_IMAGE_COLOR);
	
	N = img_load.rows*img_load.cols;

	Mat histogram(((N + 20) / 20),260, CV_8UC1);
	Mat img_out(img_load.rows,img_load.cols,CV_8UC1);

	img_out = conv_grey(img_load);
	histogram = build_Histogram(img_out);

	namedWindow("MyWindow",WINDOW_AUTOSIZE);
	
	//To print greyscale;
	imshow("MyWindow",img_out);
	waitKey(2000);

	//To print histogram; 	
	imshow("MyWindow", histogram);
	waitKey(4000);

	
	//Finding threshhold ;
	thresh = Binary_Thresh(img_load);
	//Converting to binary;
	img_out = conv_binary(img_load, thresh);


	//To print Binary img ;
	imshow("MyWindow", img_out);
	waitKey(0);

	return 0;
}

*/

//Program for track bar , uncomment it to use and comment the histogram main() ;

int main()
{
	int x = 10;

	
	Mat img_load;
	img_load = imread("H://wallpapers//test3.png", CV_LOAD_IMAGE_COLOR);
	Mat HSL_img(img_load.rows, img_load.cols, CV_8UC3);
	Mat temp_img(img_load.rows, img_load.cols, CV_8UC1);

	cvtColor(img_load, HSL_img, CV_BGR2HLS_FULL);
	int lower_h=0, upper_h=255, i, j, lower_s=0, upper_s=255, lower_l=0, upper_l=255;
	
	namedWindow("WINDOW1",WINDOW_AUTOSIZE);

	createTrackbar("h1", "WINDOW1", &lower_h, 255);
	createTrackbar("h2", "WINDOW1", &upper_h, 255);
	createTrackbar("s1", "WINDOW1", &lower_s, 255);
	createTrackbar("s2", "WINDOW1", &upper_s, 255);
	createTrackbar("l1", "WINDOW1", &lower_l, 255);
	createTrackbar("l2", "WINDOW1", &upper_l, 255);

	while (1)
	{
		/*for (i = 0; i < (img_load.cols); i++)
		for (j = 0; j < (img_load.rows); j++)
		{
			temp_img.at<uchar>(j, i) = HSL_img.at<uchar>(j, i);
		}*/

		for (i = 0; i < (img_load.cols); i++)
		for (j = 0; j < (img_load.rows); j++)
		{
			if (((HSL_img.at<Vec3b>(j, i)[0] >= lower_h) && (HSL_img.at<Vec3b>(j, i)[0] <= upper_h)) && ((HSL_img.at<Vec3b>(j, i)[1] >= lower_s) && (HSL_img.at<Vec3b>(j, i)[1] <= upper_s)) && ((HSL_img.at<Vec3b>(j, i)[2] >= lower_l) && (HSL_img.at<Vec3b>(j, i)[2] <= upper_l)))
				temp_img.at<uchar>(j, i) = 255;
			else
				temp_img.at<uchar>(j, i) = 0;
		}

		imshow("WINDOWx", temp_img);
		char a = waitKey(33);
		if (a == 27)break;
	}

	return 0;  
}


//Program for using canny.
/*
int main()
{
	int i, j;
	Mat img_load;
	img_load = imread("H://wallpapers//test2.png", CV_LOAD_IMAGE_COLOR);

	Mat x(img_load.rows, img_load.cols, CV_8UC1);
	
	int default_ = 10,lower=10,upper=10;
	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);

	createTrackbar("Binary_Threshold", "WINDOWS1", &default_, 255);
	createTrackbar("lower", "WINDOWS1", &lower, 255);
	createTrackbar("upper", "WINDOWS1", &upper, 255);

	while (1)
	{
		conv_binary(img_load, default_);
		Canny(img_load, x, lower, upper);
		imshow("WINDOWS1", x);
		char a = waitKey(33);
		if (a == 27)break;
	}

return 0;
}
*/

//Prog for Delation and Erosiom ;
/*
int main()
{
	int i, j;
	Mat img_load;
	img_load = imread("H://wallpapers//minions.jpg", CV_LOAD_IMAGE_COLOR);

	Mat x(img_load.rows, img_load.cols, CV_8UC1);
	x = Border_Creater_Algo(img_load);
	
	int thresh = Binary_Thresh(x);
	x = conv_binary(x, 20);

	namedWindow("MyWindow_Bin", WINDOW_AUTOSIZE);
	imshow("MyWindow_Bin", x);
	
	
	x = Delation(x);
	
	namedWindow("MyWindow_Delation", WINDOW_AUTOSIZE);
	imshow("MyWindow_Delation", x);
	
	
	x = Erosion(x);

	namedWindow("MyWindow_Erosion", WINDOW_AUTOSIZE);
	imshow("MyWindow_Erosion", x);

	waitKey(0);

	return 0;
}
*/

//Applying various filters(Mean,Median,Gaussian)..
/*
int main()
{
	int i, j;
	Mat img_load;
	img_load = imread("H://wallpapers//Capture1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	Mat x(img_load.rows, img_load.cols, CV_8UC1);
	x = img_load; //x = conv_grey(img_load);
	namedWindow("MyWindow_grey", WINDOW_AUTOSIZE);
	imshow("MyWindow_grey", x);
	Mat y(img_load.rows, img_load.cols, CV_8UC1);
	y = x;
	y = Median_Filter(x);
	namedWindow("MyWindow_Median", WINDOW_AUTOSIZE);
	imshow("MyWindow_Median", y);


	x = Gaussian_Filter(x);
	namedWindow("MyWindow_Gaussian", WINDOW_AUTOSIZE);
	imshow("MyWindow_Gaussian", x);

	waitKey(0);


	return 0;
}
*/


//To work with a Video

//int main()
//{
//	VideoCapture V("H:\\wallpapers\\PS.mp4");
//	Mat frame;
//
//	//int default_ = 100, lower = 60, upper = 10;
//
//	/*createTrackbar("Binary_Threshold", "WINDOWS1", &default_, 255);
//	createTrackbar("lower", "WINDOWS1", &lower, 255);
//	createTrackbar("upper", "WINDOWS1", &upper, 255);*/
//
//	namedWindow("WINDOWS1", WINDOW_AUTOSIZE);
//
//	while (1)
//	{
//		V >>frame;
//		Mat img_load(frame.rows,frame.cols,CV_8UC1);
//
//		Mat img_out(frame.rows, frame.cols, CV_8UC1);
//		img_out = Color_Detection(frame, 1);
//
//		imshow("Blue Circle", img_out);
//
//		Point2D C;
//		C = Obj_Center(img_out);
//
//		Mat img_shape(frame.rows, frame.cols, CV_8UC1);
//		C = Shape_Detection(img_out, 8);
//
//		if (C.x>0 && C.y>0)
//			cout << "(" << C.x << "," << C.y << ")  & Blue Circle exhists";
//			char a = waitKey(5);
//		if (a == 27)break;
//	}
//}



//Main ref Prog .