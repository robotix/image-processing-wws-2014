#include "stdafx.h"
#include <iostream>
#include<vector>
#include<math.h>
#include<queue>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
void prnimage(Mat);
Mat prngrey(Mat);
Mat binaryimg(Mat,int);
void bincolourimg(Mat, int, int, int);
void invertimg(Mat);
int threshhold(Mat);
Mat outlinebinimg1(Mat,int);
Mat outlinebinimg2(Mat, int);
Mat outlinebinimg3(Mat);
Mat outlinebinimgx(Mat);
Mat outlinebinimgy(Mat);
Mat blurimg(Mat);
Mat smoothenmedian(Mat);
Mat dilationbin(Mat);
Mat erosionbin(Mat);
void bubble_sort(int[], int);
Mat smoothenmedian(Mat);
Mat gaussianimg(Mat);
void webcamcanny();
Mat HSLcolourchange(Mat, int, int);
Mat blobdetection(Mat);
void hough(Mat,int,Point[],int&);
Mat houghline(int,int, Point[],int);
int main()
{
	//int p,q,r,d=109;
	Mat image;
	int thresh=5,t=0;
	Point p[1000];
	namedWindow("Line", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshhold", "Line", &thresh, 255);
	while (1)
	{

		image = imread("line.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		hough(image, thresh, p, t);
		Mat x = houghline(image.rows, image.cols, p, t);
		//Mat img = blobdetection(image);
		imshow("Line", x);
		char a=waitKey(33);
		if (a == 32)break;
	}
	/*Mat img = prngrey(image);
	Mat x = blurimg(img);
	Mat y = blurimg(img);
	Mat z = blurimg(img); */
	//namedWindow("Binary", CV_WINDOW_AUTOSIZE);
	
	
	//createTrackbar("Threshhold", "Binary", &d, 255);
	//while (1)
	//{
		//image = imread("F:\\image processing\\10847904_10204565576051151_4759441167489822037_n.jpg");
		//Mat img = prngrey(image);
		//Mat x = gaussianimg(img);
		//Mat x = binaryimg(image, d);
		//imshow("Binary", x);
		//Mat y = dilationbin(x);
		//namedWindow("Dilation", CV_WINDOW_AUTOSIZE);
		//imshow("Dilation", y);
		//Mat z = erosionbin(y);

		//namedWindow("erosion", CV_WINDOW_AUTOSIZE);
		//imshow("Binary",z);
		//waitKey(0); 
		//char a=waitKey(33);
		//if (a == 32)break;
	//} 
	//int t = threshhold(image);
	//binaryimg(image, t);
	/*namedWindow("My window", CV_WINDOW_AUTOSIZE);
	createTrackbar("Blue", "My window", &p, 255);
	createTrackbar("Green", "My window", &q, 255);
	createTrackbar("Red", "My window", &r, 255);
	while (1)

	{
		image = imread("F:\\image processing\\10847904_10204565576051151_4759441167489822037_n.jpg");
		 bincolourimg(image, p,q,r);
		char a = waitKey(33);
		if (a == 27)break;

	} */
	/*namedWindow("My window1", CV_WINDOW_AUTOSIZE);
	namedWindow("My window2", CV_WINDOW_AUTOSIZE);
	namedWindow("My window3", CV_WINDOW_AUTOSIZE);
	imshow("My window1", x);
	imshow("My window2", y);
	imshow("My window3", z);
	waitKey(0); */
	cout << "No. of rows" << image.rows << "\nNo. of columns" << image.cols;
	getchar();
	return 0; 
}
Mat prngrey(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			img.at<uchar>(i, j) = 0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2];
		}
	}
	return(img);
}
Mat binaryimg(Mat image,int threshhold)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j, temp;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			temp = (int)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
			if (temp < threshhold) 
				img.at<uchar>(i, j) = 0;
			else img.at<uchar>(i, j) = 255;
		}
	}
	return(img);

}
void prnimage(Mat image)
{
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	imshow("my window", image);
	waitKey(0);
}
void invertimg(Mat image)
{
	int i, j,temp[3];
	for (i =0; i < image.rows/2; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			temp[0] = image.at<Vec3b>(i, j)[0]; image.at<Vec3b>(i, j)[0] = image.at<Vec3b>(image.rows - i - 1, j)[0]; image.at<Vec3b>(image.rows - i - 1, j)[0] = temp[0];
			temp[1] = image.at<Vec3b>(i, j)[1]; image.at<Vec3b>(i, j)[1] = image.at<Vec3b>(image.rows - i - 1, j)[1]; image.at<Vec3b>(image.rows - i - 1, j)[1] = temp[1];
			temp[2] = image.at<Vec3b>(i, j)[2]; image.at<Vec3b>(i, j)[2] = image.at<Vec3b>(image.rows - i - 1, j)[2]; image.at<Vec3b>(image.rows - i - 1, j)[2] = temp[2];
		}
	}
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	imshow("my window", image);
	waitKey(0);
}
int threshhold(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j,A[256],k;
	int n = image.rows*image.cols;
	for (int k = 0; k < 256; k++) A[k] = 0;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			img.at<uchar>(i, j) = 0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2];
			A[img.at<uchar>(i, j)]++;
		}
	}
	
	for (k = 0; k < 256; k++)
	{
		A[k]/= 50;
	}
	
	Mat hist(500, 256, CV_8UC1, Scalar(255));
	for (k = 0; k < 256; k++)
	{
		for (int l = 0; l <= A[k]; l++)
		{
			hist.at<uchar>(l, k) = 0;
		}
	}
	//invertimg(hist);
	int temp;
	for (i = 0; i < hist.rows / 2; i++)
	{
		for (j = 0; j < hist.cols; j++)
		{
			temp = hist.at<uchar>(i, j); hist.at<uchar>(i, j) = hist.at<uchar>(hist.rows - i - 1, j); hist.at<uchar>(hist.rows - i - 1, j)= temp;
	
		}
	}
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	imshow("my window", hist);
	waitKey(0);    
	int sum = 0; k = 0;
	while (sum <= (n /50)/2)
	{
		sum += A[k++];
	}
	return(k - 1);
}
void bincolourimg(Mat image, int p, int q, int r)
{
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<Vec3b>(i, j)[0] < p) image.at<Vec3b>(i, j)[0] = 0;
			else image.at<Vec3b>(i, j)[0] = 255;
			if (image.at<Vec3b>(i, j)[1] < q) image.at<Vec3b>(i, j)[1] = 0;
			else image.at<Vec3b>(i, j)[1] = 255;
			if (image.at<Vec3b>(i, j)[2] < r) image.at<Vec3b>(i, j)[2] = 0;
			else image.at<Vec3b>(i, j)[2] = 255;
		}
	}
	imshow("My window", image);
}
Mat outlinebinimg1(Mat image,int d)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j;
	for (i = 1; i < image.rows-1; i++)
	{
		for (j = 1; j < image.cols-1; j++)
		{
			//if (i != 0 && j != 0&&i!=image.rows-1&&j!=image.cols-1)
			if ((abs(image.at<uchar>(i - 1, j) - image.at<uchar>(i + 1, j)) < d) || (abs(image.at<uchar>(i, j-1) - image.at<uchar>(i, j+1)) < d))
				img.at<uchar>(i, j) = 0;
		}
	}
	return(img);
} 
Mat outlinebinimg2(Mat image, int d)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j,k,l,max,min;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			for (k = -1; k < 2; k++)
			{
				max = image.at<uchar>(i - 1, j - 1);
				min = image.at<uchar>(i - 1, j - 1);
				for (l = -1; l < 2; l++)
				{
					if (max < image.at<uchar>(i + k, j + l)) max = image.at<uchar>(i + k, j + l);
					if (min > image.at<uchar>(i + k, j + l)) min = image.at<uchar>(i + k, j + l);
				}
			}
			if (abs(max-min)>=d)
			img.at<uchar>(i, j) = 0;

		}
	}
	return(img);
}
Mat outlinebinimg3(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j,x,y;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			x = image.at<uchar>(i - 1, j + 1) + image.at<uchar>(i, j + 1) + image.at<uchar>(i + 1, j + 1) - image.at<uchar>(i - 1, j - 1) - image.at<uchar>(i, j - 1) - image.at<uchar>(i + 1, j - 1);
			y = image.at<uchar>(i + 1, j - 1) + image.at<uchar>(i + 1, j) + image.at<uchar>(i + 1, j + 1) - image.at<uchar>(i - 1, j - 1) - image.at<uchar>(i - 1, j) - image.at<uchar>(i - 1, j + 1);
			img.at<uchar>(i, j) = sqrt(x*x + y*y);
		}  
	}
	return(img);
}
Mat outlinebinimgx(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j, x, y;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			x = image.at<uchar>(i - 1, j + 1) + image.at<uchar>(i, j + 1) + image.at<uchar>(i + 1, j + 1) - image.at<uchar>(i - 1, j - 1) - image.at<uchar>(i, j - 1) - image.at<uchar>(i + 1, j - 1);
			
			img.at<uchar>(i, j) = x;
		}
	}
	return(img);
}
Mat outlinebinimgy(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j, x, y;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			
			y = image.at<uchar>(i + 1, j - 1) + image.at<uchar>(i + 1, j) + image.at<uchar>(i + 1, j + 1) - image.at<uchar>(i - 1, j - 1) - image.at<uchar>(i - 1, j) - image.at<uchar>(i - 1, j + 1);
			img.at<uchar>(i, j) = y;
		}
	}
	return(img);
}
Mat blurimg(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j,k,l,sum;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			sum = 0;
			for (k = -1; k < 2; k++)
			{
				for (l = -1; l < 2; l++)
				{
					sum += image.at<uchar>(i + k, j + l);
				}
			}
			img.at<uchar>(i, j) = sum/9;
		}
	}
	return(img);
  
}
Mat dilationbin(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j, k, l, black, white;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			black = white = 0;
			for (k = -1; k < 2; k++)
			{
				for (l = -1; l < 2; l++)
				{
					if (image.at<uchar>(i + k, j + l) == 0) black++;
					else white++;
				}
			}
			if (black>white) img.at<uchar>(i, j) = 0;
			else img.at<uchar>(i, j) = 255;
		}
	}
	return(img);
}
Mat erosionbin(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1);
	int i, j, k, l, black, white;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			black = white = 0;
			for (k = -1; k < 2; k++)
			{
				for (l = -1; l < 2; l++)
				{
					if (image.at<uchar>(i + k, j + l) == 0) black++;
					else white++;
				}
			}
			if (black>white&&white) img.at<uchar>(i, j) = 255;
			if(black<white&&black) img.at<uchar>(i, j) = 0;
			if (black == 0)  img.at<uchar>(i, j) = 255;
			if (white == 0) img.at<uchar>(i, j) = 0;
		}
	}
	return img;
}
Mat smoothenmedian(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j, k, l,A[9],t=0;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			t = 0;
			for (k = -1; k < 2; k++)
			{
				for (l = -1; l < 2; l++)
				{
					A[t++] =image.at<uchar>(i + k, j + l);
				}
			}
			bubble_sort(A, 9);
			img.at<uchar>(i, j) = A[4];
		}
	}
	return(img);

}
void bubble_sort(int list[], int n)
{
	long c, d, t;

	for (c = 0; c < (n - 1); c++)
	{
		for (d = 0; d < n - c - 1; d++)
		{
			if (list[d] > list[d + 1])
			{	t = list[d];
				list[d] = list[d + 1];
				list[d + 1] = t;
			}
		}
	}
}
Mat gaussianimg(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));
	int i, j, x;
	for (i = 1; i < image.rows - 1; i++)
	{
		for (j = 1; j < image.cols - 1; j++)
		{
			x = image.at<uchar>(i - 1, j - 1)*0.06 + image.at<uchar>(i + 1, j - 1)*0.06 + image.at<uchar>(i + 1, j + 1)*0.06 + image.at<uchar>(i - 1, j + 1)*0.06 + image.at<uchar>(i, j - 1)*0.098 + image.at<uchar>(i, j + 1)*0.098 + image.at<uchar>(i - 1, j)*0.098 + image.at<uchar>(i + 1, j)*0.098 + image.at<uchar>(i, j)*0.162;
			img.at<uchar>(i, j) = x/0.794;
		}
	}
	return(img);
} 
void webcamcanny()
{
	VideoCapture V(0);
	while (1)
	{
		Mat temp,frame;
		int p, q;
		namedWindow("Canny", CV_WINDOW_AUTOSIZE);
		createTrackbar("M1", "Canny", &p, 255);
		createTrackbar("M2", "Canny", &q, 255);
		while (1)
		{
			V >> frame;
			Mat x = prngrey(frame);

			//Mat y = binaryimg(x,25);
			Canny(frame, temp, p, q);
			imshow("Canny", temp);
			char a = waitKey(33);
			if (a == 32)break;
		}
		char b = waitKey(33);
	}
}
Mat HSLcolourchange(Mat image, int Hue, int tolerance)
{
	Mat dest, bin(image.rows,image.cols,CV_8UC1);
	cvtColor(image, dest, CV_BGR2HLS_FULL);
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (dest.at<Vec3b>(i, j)[0]>=Hue - tolerance&&dest.at<Vec3b>(i, j)[0] <= Hue + tolerance)
				bin.at<uchar>(i, j) = 0;
			else bin.at<uchar>(i, j) = 255;
		}
	}
	return(bin); 
	
}
/*Mat blobdetection(Mat image)
{
	Mat img(image.rows, image.cols, CV_8UC1,Scalar(0));
	int i, j, k, l, t = 0;
	int A[10000][10000];
	for (i = 0; i < 10000; i++)
	{
		for (j = 0; j < 10000; j++)
		{
			A[i][j] = -1;
		}
	}
	queue<Point> q;
	for (i = 1; i < image.rows-1; i++)
	{
		for (j = 1; j < image.cols-1; j++)
		{
			if (image.at<uchar>(i, j) == 255 && A[j][i] == -1)
			{
				t++;
				Point p;
				p.x = j;
				p.y = i;
				q.push(p);
				A[j][i] = 0;
				while (!q.empty())
				{
					for (k = -1; k < 2; k++)
					{
						for (l = -1; l < 2; l++)
						{
							if (image.at<uchar>(i + k, j + l) == 255 && A[j + l][i + k] == -1)
							{
								p.x = j + l;
								p.y = i + k;
								q.push(p);
								A[j + l][i + k] = 0;
							}
						}
					}
					Point temp = q.front();
					q.pop();
					A[temp.x][temp.y] = t;
					i = q.front().y;
					j = q.front().x;

				}
			}
		}
	}
		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				if (A[j][i] != -1&&image.at<uchar>(i,j)==255)
				{
					img.at<uchar>(i, j) = 255 / A[j][i];
				}
			}
		}
	return(img);

	
}*/
void hough(Mat image,int threshhold,Point p[],int &t )
{
	int i, j, r;
	double temp;
	int theta_max = 180, r_max = (int)sqrt(image.rows*image.rows + image.cols*image.cols);
	int **Acc;
	Acc = (int**)malloc(theta_max * sizeof(int*));
	for (i = 0; i < theta_max; i++)
	{
		Acc[i] = (int*)malloc(r_max*sizeof(int));
		for (j = 0; j < r_max; j++)
		{
			Acc[i][j]=0;
		}
	}
	
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			
			if (image.at<uchar>(i,j)>250)
			{
				for (int k = 0; k < theta_max; k++)
				{
					temp = (double)(j*cos(k*CV_PI / 180)) + (double)(i*sin(k*CV_PI / 180));
					r = abs((int)temp);
					Acc[k][r]++;
					//cout << r <<"  "<< k<<endl;

				}
			}
		}
	}
	 t=0;
	for (i = 0; i < theta_max; i++)
	{
		for (j = 0; j < r_max; j++)
		{
			if (threshhold <= Acc[i][j])
			{
				p[t].x = j;
				p[t].y = i;
				t++;
			}
		}
	}
}
Mat houghline(int imgrows, int imgcols, Point p[],int t)
{
	int theta,r,i,j;
	double temp;
	Mat img(imgrows, imgcols, CV_8UC1, Scalar(0));
	for (int k = 0; k < t; k++)
	{
		theta = p[k].y;
		r = p[k].x;
		for (i = 0; i < imgcols; i++)
		{
			temp = ((double)r - i*cos(theta*CV_PI / 180)) / sin(theta*CV_PI / 180);
			j = abs((int)temp);
			//cout << j << " " << i << "\n";
			//system("Pause");
			if (j < imgrows)
				img.at<uchar>(j, i) = 255;

		}
	}
	return(img);
}