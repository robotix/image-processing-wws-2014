// ConsoleApplication2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<queue>
#include<iostream>
using namespace std;
using namespace cv;




void makeflag()
{
	Mat img(132, 999, CV_8UC3, Scalar(255, 255, 255));
	
	for (int i = 0; i < 132; i++)
	{
		for (int j = 0; j < 999; j++)
		{
			if (i < 44)
			{
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 165;
				img.at<Vec3b>(i, j)[2] = 255;
			}
			else if ((i > 44) && (i < 88))
			{
				img.at<Vec3b>(i, j)[0] = 255;
				img.at<Vec3b>(i, j)[1] = 255;
				img.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 255;
				img.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	namedWindow("sonal", WINDOW_AUTOSIZE);
	imshow("sonal", img);
}
Mat Grayscale(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	Mat img3(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	int av;
	int i, j;

	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			img2.at<uchar>(i, j) = img1.at < Vec3b>(i, j)[0] * 0.55 + img1.at < Vec3b>(i, j)[1] * 0.33 + img1.at < Vec3b>(i, j)[2] * 0.11;
			
		}
	}

	//namedWindow("sonal", WINDOW_AUTOSIZE);
	//imshow("sonal", img2);
return img2;
}
Mat bin(Mat img1,int x)
{
	Mat img2(img1.rows,img1.cols,CV_8UC3,Scalar(0,0,0));
	Mat img3(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	int av;
	int i , j ;

	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			//img2.at<uchar>(i, j) = img1.at < Vec3b>(i, j)[0] * 0.55 + img1.at < Vec3b>(i, j)[1] * 0.33 + img1.at < Vec3b>(i, j)[2] * 0.11;
			if (img1.at<uchar>(i, j)<x)
			{
				img3.at<uchar>(i, j) = 0;
			}
			else
			{
				img3.at<uchar>(i, j) = 255;
			}
		}
	}


	/*namedWindow("sonal", WINDOW_AUTOSIZE);
	imshow("sonal", img3);*/
	return img3;
}
void invert()
{
	Mat img1 = imread("haha.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0, 0, 0));
	int i, j,k=0,m=0;
	for (i = 0, k = img1.rows-1; (i < img1.rows)&&(k>=0); k--, i++)
	{
		for (j = 0; j < img1.cols ; j++)
		{
			//for (m = 0; m < 3; m++)
			
				img2.at<Vec3b>(i, j)[0] = img1.at<Vec3b>(k, j)[0];
				img2.at<Vec3b>(i, j)[1] = img1.at<Vec3b>(k, j)[1];
				img2.at<Vec3b>(i, j)[2] = img1.at<Vec3b>(k, j)[2];
			
		}
	}
	namedWindow("sonal", WINDOW_AUTOSIZE);
	imshow("sonal", img2);
}
void histo()
{
	Mat img1;
	img1 = imread("haha.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2(500, 256, CV_8UC1, Scalar(255));
	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int i, j, k = 0, m = 0;
	int a[256];
	for (i = 0; i < 256; i++) a[i] = 0;
	int n;
	int sum = 0, s = 0;
	int t;
	for (k = 0; k < 256; k++)
	{
		for (i = 0; i < img1.rows; i++)
		{
			for (j = 0; j < img1.cols; j++)
			{
				if (img1.at<uchar>(i, j) == k)
					a[k]++;

			}
		}
	}
	for (i = 0; i < 256; i++)
	{
		a[i] /= 50;
		sum += a[i];
	}
	
	
		for (j = 0; j < img2.cols; j++)
		{
			for (i = img2.rows - 1; img2.rows - i <= a[j];i--)
			{
			img2.at<uchar>(i, j) = 0;
		}
	}
	namedWindow("histo",WINDOW_AUTOSIZE);
	imshow("histo", img2);

	for (i = 0; i < 256; i++)
	{

			s+=a[i]++;
			if (s >= sum / 2)
				break;
			else
				continue;
	}
	m = i;
	for (i = 0; i < img1.rows; i++)
	{
		for (j = 0; j < img1.cols; j++)
		{
			
			if (img1.at<uchar>(i, j)>m)
			{
				img3.at<uchar>(i, j) = 0;
			}
			else
			{
				img3.at<uchar>(i, j) = 255;
			}
		}
	}
	namedWindow("pic", WINDOW_AUTOSIZE);
	imshow("pic",img3);
	
	}
Mat prewett(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	int dx = 0, dy = 0;
	for (h = 1; h < img1.rows-1; h++)
	{
		for (n = 1; n < img1.cols-1; n++)
		{
			for (i = -1; i < 2; i++)
			{
				dx = 0; dy = 0;
				for (j = -1; j<2; j++)
				{
					dx+= img1.at<uchar>(i + h, j + n)*i;
					dy+= img1.at<uchar>(i + h, j + n)*j;
				}
			}
			d = sqrt(dx*dx + dy*dy);
			img2.at<uchar>(h, n) = d;
			
		}
	}
	return(img2);

}

Mat edge(Mat img1,int x)
{
	int a[9];
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	//cout << "enter the value of threshold";
	//cin >> px;
	for (h = 0; h < img1.rows; h++)
	{
		for (n = 0; n < img1.cols; n++)
		{
			if ((h == 0) || (h == img1.rows - 1) || (n == 0) || (n == img1.cols - 1)) continue;
			max = img1.at<uchar>(h-1,n-1);
			min = img1.at<uchar>(h - 1, n - 1);
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2;j++)
				{
					if (img1.at<uchar>(i + h, j + n)>max)max = img1.at<uchar>(i + h, j + n);
					if (img1.at<uchar>(i + h, j + n)<min)min = img1.at<uchar>(i + h, j + n);
				}
			}
			if ((max - min)>x)

				img2.at<uchar>(h, n) = 255;
			else
				img2.at<uchar>(h, n) = 0;
		}
	}
	return(img2);

}
Mat erode(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows - 1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			max = img1.at<uchar>(h - 1, n - 1);
			min = img1.at<uchar>(h - 1, n - 1);
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2; j++)
				{
					if (img1.at<uchar>(i + h, j + n)>max)max = img1.at<uchar>(i + h, j + n);
					if (img1.at<uchar>(i + h, j + n) < min)min = img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h, n) = min;
		}
	}
	return(img2);
}
Mat dilate(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, m = 0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows-1; h++)
	{
		for (n = 1; n < img1.cols-1; n++)
		{
			max = img1.at<uchar>(h - 1, n - 1);
			min = img1.at<uchar>(h - 1, n - 1);
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2; j++)
				{
					if (img1.at<uchar>(i + h, j + n)>max)max = img1.at<uchar>(i + h, j + n);
					if (img1.at<uchar>(i + h, j + n) < min)min = img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h, n) = max;
		}
	}
	return(img2);
}
void avgborder(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int i = 0, j = 0, k = 0, m = 0,sum=0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows -1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			sum = 0;
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j<2; j++)
				{
					sum = sum+img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h,n) = sum / 9;
		}
	}
	namedWindow("sp", WINDOW_AUTOSIZE);
	imshow("sp", img2);
	

}
void median(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, l = 0, m = 0, sum = 0;
	int px = 0, h = 0, n = 0, d = 0;
	int a[9];
	for (h = 1; h < img1.rows - 1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			m = 0;
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j < 2; j++)
				{
					a[m++] = img1.at<uchar>(i + h, j + n);
				}
			}
			for (int f = 7; f >=0; f--)
			{
				for (l = 0; l <=f; l++)
				{
					if (a[l] > a[l + 1])
					{
						px = a[l];
						a[l] = a[l + 1];
						a[l + 1] = px;
					}
				}
			}
			img2.at<uchar>( h, n) = a[4];
		}
	}
	namedWindow("si", WINDOW_AUTOSIZE);
	imshow("si", img2);
}
void gauss(Mat img1)
{ 
	float a[9] = { 0.06, 0.098, 0.06, 0.098, 0.162, 0.098, 0.06, 0.098, 0.06 };
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int max = 0, min = 999;
	int i = 0, j = 0, k = 0, l = 0, m = 0, sum = 0;
	int px = 0, h = 0, n = 0, d = 0;
	for (h = 1; h < img1.rows - 1; h++)
	{
		for (n = 1; n < img1.cols - 1; n++)
		{
			m = 0; sum = 0;
			for (i = -1; i < 2; i++)
			{
				for (j = -1; j < 2; j++)
				{
					sum += a[m++] * img1.at<uchar>(i + h, j + n);
				}
			}
			img2.at<uchar>(h,n) = sum;
		}
	}
	namedWindow("s", WINDOW_AUTOSIZE);
	imshow("s", img2);

}
//Mat identifyingHSV(Mat img1, int hue/*,int sat,int light*/)
//{
//	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
//	int av;
//	int i, j;
//
//	for (i = 0; i < img1.rows; i++)
//	{
//		for (j = 0; j < img1.cols; j++)
//		{
//			if ((img1.at<Vec3b>(i, j)[0]<hue + 128) && (img1.at<Vec3b>(i, j)[0]> 128 - hue))
//				img3.at<uchar>(i, j) = 255;
//			//if ((img1.at<Vec3b>(i, j)[1]<sat + 128) && (img1.at<Vec3b>(i, j)[1]> 128 - sat))
//			//img3.at<uchar>(i, j) = 255;
//			//if ((img1.at<Vec3b>(i, j)[2]<light + 128) && (img1.at<Vec3b>(i, j)[2]> 128 - light))
//			//img3.at<uchar>(i, j) = 255;
//		}
//	}
//
//	/*namedWindow("sonal", WINDOW_AUTOSIZE);
//	imshow("sonal", img3);*/
//	return img3;
//}
//Mat searchforcontinuity(int a, int b, Mat img1, Mat img2,int x)
//{
//	queue<Point> q;
//	Point temp(a, b);
//	q.push(temp);
//	img2.at<schar>(a, b) = 0;
//	while (1)
//	{
//		cout << "break1"<<endl;
//		for (int i = a - 1; i < a + 2; i++)
//		{
//			for (int j = b - 1; j < b + 2; j++)
//			{
//				if ((img1.at<uchar>(i ,j) == 255) && (img1.at<uchar>(i, j)==-1))
//				{
//					Point temp2(i, j);
//					q.push(temp2);
//					img2.at<schar>(i, j) = 0;
//					cout << "break2"<<endl;
//				}
//			}
//		}
//		img2.at<schar>(a, b) = x;
//		q.pop();
//		
//		if (q.empty())break;
//		cout << "break3"<<endl;
//		Point n = q.front();
//		a = n.x;
//		b = n.y;
//	}
//	cout << "break4"<<endl;
//	return img2;
//}

//void printblob(Mat img1, int x)
//{
//
//	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0));
//	int counter = 0;
//	for (int h = 0; h < img1.rows; h++)
//	{
//		for (int n = 0; n < img1.cols; n++)
//		{
//			if (img1.at<schar>(h, n) == x)
//			{
//				img2.at<uchar>(h, n) = 255;
//				cout << "break5 " << counter << endl;
//				counter++;
//			}
//			
//		}
//	}
//	namedWindow("blob", WINDOW_AUTOSIZE);
//	imshow("blob", img2);
//	waitKey(0);
//}
Mat blob(Mat img)
{
	queue<Point> q;
	int i, j, c = 1, m, n;
	Mat x(img.rows, img.cols, CV_8SC1, Scalar(-1));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			m = i; n = j;
			if (img.at<uchar>(i, j) == 255 && x.at<char>(i, j) == -1)
			{
				Point temp(m, n);
				q.push(temp);
				x.at<char>(i, j) = c;
				while (!q.empty())
				{
					for (int k = m - 1; k <= m + 1; k++)
					{
						for (int l = n - 1; l <= n + 1; l++)
						{
							if (img.at<uchar>(k, l) == 255 && x.at<char>(k, l) == -1)
							{
								Point temp3(k, l);
								q.push(temp3);
								x.at<char>(k, l) = c;
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
			if (x.at<char>(i, j) != -1)
				y.at<uchar>(i, j) = 50 * x.at<char>(i, j);
		}
	}
	return y;


}
void hough(Mat image, int threshhold, Point p[], int &t)
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
			Acc[i][j] = 0;
		}
	}
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j)>250)
			{
				for (int k = 0; k < theta_max; k++)
				{
					temp = (double)(j*cos(k*CV_PI / 180)) + (double)(i*sin(k*CV_PI / 180));
					r = abs((int)temp);
					Acc[k][r]++;
					//cout << r <<" "<< k<<endl;
				}
			}
		}
	}
	t = 0;
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
	for (i = 0; i < theta_max; i++)
	{
		free(Acc[i]);
	}
	free(Acc);
}
Mat houghline(int imgrows, int imgcols, Point p[], int t)
{
	int theta, r, i, j;
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
void houghlinecreate(Mat image)
{
	int thresh = 50, t = 0;
	int theta_max = 180, r_max = (int)sqrt(image.rows*image.rows + image.cols*image.cols);
	Point *p;
	p = (Point*)malloc((theta_max*r_max)*sizeof(Point));
	if (!p) exit(0);
	namedWindow("Line", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshhold", "Line", &thresh, 255);
	while (1)
	{
		hough(image, thresh, p, t);
		Mat x = houghline(image.rows, image.cols, p, t);
		//Mat img = blobdetection(image);
		imshow("Line", x);
		//char a = waitKey(33);
		//if (a == 32)break;
	}
	free(p);
}
Mat NoiseReduction(Mat img, int block = 5) //block=5 is our threshold for blob size. Less than that is noise
{
	Mat noise_reduced(img.rows, img.cols, CV_8UC1); //stores final corrected image
	int i, j, m, n, r = img.rows, c = img.cols, white, black;

	for (i = 0; i<r - block; i += block){
		for (j = 0; j<c - block; j += block){

			white = black = 0;
			//to check for large enough blob.
			for (m = i; m<i + block; m++){
				for (n = j; n<j + block; n++){

					if (img.at<uchar>(m, n) == 0)
						black++;
					else
						white++;
				}
			}
			//to remove the identified noise from the image
			int val;
			if (black >= white)
				val = 0;
			else
				val = 255;

			for (m = i; m<i + block; m++){
				for (n = j; n<j + block; n++){
					noise_reduced.at<uchar>(m, n) = val;
				}
			}
		}
	}

	return noise_reduced;
}


Mat bgrtohls(Mat img1)
{
	Mat img2;
	cvtColor(img1, img2, CV_BGR2HLS);
	namedWindow("2", WINDOW_AUTOSIZE);
	imshow("2", img2);
	return (img2);
}
Mat detectcolor(Mat img1, int h,int colour)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));

	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			//cout << (int)img1.at<Vec3b>(i, j)[0]<<" " ;
			//if (colour == 2)//green
			//{
				if ((img1.at<Vec3b>(i, j)[0]<69 + h)  && (img1.at<Vec3b>(i, j)[0]>69 - h))
					img2.at<uchar>(i, j) = 255;

			//}
			//if (colour == 3)//blue
			//{
				if ((img1.at<Vec3b>(i, j)[0]<120 + h) && (img1.at<Vec3b>(i, j)[0]>120 - h))
					img2.at<uchar>(i, j) = 255;
				if ((img1.at<Vec3b>(i, j)[0]<35 + h) && (img1.at<Vec3b>(i, j)[0]>35 - h))
					img2.at<uchar>(i, j) = 255;
				if ((img1.at<Vec3b>(i, j)[0]<45 + h) && (img1.at<Vec3b>(i, j)[0]>45 - h))
					img2.at<uchar>(i, j) = 255;

			//}
			//if (colour == 1)//red
			//{
				if ((img1.at<Vec3b>(i, j)[0]<179 + h) && (img1.at<Vec3b>(i, j)[0]>179 - h))
					img2.at<uchar>(i, j) = 255;

			//}//
		}
	}
	namedWindow("1", WINDOW_AUTOSIZE);
	imshow("1", img2);

	return(img2);
}


Point centroids(int n, vector<Point> a)
{
	int x, y;
	Point centroid;
	if (n == 3)
	{
		x = (a[0].x + a[1].x + a[2].x) / 3;
		y = (a[0].y + a[1].y + a[2].y) / 3;
		centroid.x = x;
		centroid.y = y;
		cout << endl << "centroid of triangle is - {" << centroid.x << "," << centroid.y << "}" << endl;
	}
	else if (n == 4)
	{
		 x = (a[0].x + a[2].x) / 2;
		 y = (a[0].y + a[2].y) / 2;
		 centroid.x = x;
		 centroid.y = y;
		cout << endl << "centroid of square is - {" << centroid.x << "," << centroid.y << "}" << endl;
	}
	else
	{
		int x1 = a[0].x, x2 = a[1].x, x3 = a[2].x;
		int y1 = a[0].y, y2 = a[1].y, y3 = a[2].y;

		float mr = (float)(y1 - y2)/(float)(x1 - x2);
		float mt = (float)(y2 - y3) /(float) (x2 - x3);

		centroid.x = (mr*mt*(y3 - y1) + mr*(x2 + x3) - mt*(x1 + x2)) / (2 * (mr - mt));
		centroid.y = (-1 / mr)*(centroid.x - (x1 + x2) / 2) + (y1 + y2) / 2;
		cout << endl << "centroid of circle is - {" << centroid.x << "," << centroid.y << "}" << endl;
	}
	return centroid;
}
void movebot(Mat frame, int c)
{
	namedWindow("base", WINDOW_AUTOSIZE);
	Mat a(frame.rows, frame.cols, CV_8UC1, Scalar(0));
	/*for (int i = frame.rows; i > frame.rows - 50; i--)
	{
		for (int j = frame.cols; j > frame.cols - 300; j--)
		{
			a.at<uchar>(i, j) = 255;
		}
	}*/
	for (int i = 2; i < 3; i++)
	{
		for (int j = 3; j < frame.cols; j++)
		{
			a.at<uchar>(c+i, j) = 255;
		}
	}
	imshow("base", a);
}

Mat shape_detect(Mat img1,int colour)
{
	vector<vector<Point>> c;
	Mat img2;
	int tol = 5;
	//namedWindow("value", WINDOW_AUTOSIZE);
	//createTrackbar("tollerence", "value", &tol, 255);

	//while (1)
	//{
		img2 = bgrtohls(img1);
	img2 = detectcolor(img2, 5,colour);
	img2 = NoiseReduction(img2);
	img2 = erode(img2);
	img2 = dilate(img2);
	movebot(img2,1);
	
	imshow("value", img2);
	//char a = waitKey(33);
	//if (a == 27)
		//break;
	//}
	findContours(img2, c, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	vector<Point> app;
	int x = 0, t = 0, s = 0, cr = 0;
	Point centroid1,centroid2,centroid3;
	for (int i = 0; i < c.size(); i++)
	{
		int cx1=0,cx2=0;
		double epsilon = 0.05*arcLength(c[i], true);
		approxPolyDP(c[i], app, epsilon, true);
		x = app.size();
		if (x == 3) 
		{
			cx1 = ((app[0].x - app[1].x)*(app[0].x - app[1].x) + pow((app[0].y - app[1].y), 2));
			cx2 = ((app[1].x - app[2].x)*(app[1].x - app[2].x) + pow((app[1].y - app[2].y), 2));
			if ((cx1 >> 10) && (cx2 >> 20))
			{
				t++;
				centroid1=centroids(3, app);
			}
		}
		if (x == 4) {
		

				cx1 = ((app[0].x - app[1].x)*(app[0].x - app[1].x) + pow((app[0].y - app[1].y), 2));
				cx2 = ((app[1].x - app[2].x)*(app[1].x - app[2].x) + pow((app[1].y - app[2].y), 2));
				if ((cx1 >> 10) && (cx2 >> 20))
				{
				s++;
				centroid2=centroids(4, app);
			}
		}

		if (x >6) {
			cx1 = ((app[0].x - app[1].x)*(app[0].x - app[1].x) + pow((app[0].y - app[1].y), 2));
			cx2 = ((app[1].x - app[2].x)*(app[1].x - app[2].x) + pow((app[1].y - app[2].y), 2));
			if ((cx1 >> 10) && (cx2 >> 20))
			{

				cr++;
				centroid2=centroids(7, app);
			}
		}
	}

	if (t) cout << "the number of red triangles is" << t << endl;
	if (s) cout << "the number of red squares is " << s << endl;
	if (cr) cout << "the number of red circles is " << cr << endl;
	
	
	return img2;
	getchar();

}


	int main()
	{
		Mat img1;
		int colour = 3;
		
		VideoCapture v("ps.mp4");
		/*img1 = imread("shape.png", CV_LOAD_IMAGE_GRAYSCALE);
		shape_detect(img1,colour);
		return 0;*/
		while (1)
		{
			Mat frame;
			v >> frame;
			shape_detect(frame, 3);
			imshow("video", frame);
			int a = waitKey(33);
			if (a == 27)break;

		}
		getchar();
		return 0;
		//waitKey(0);
		//img1 = imread("linedetect.png", cv_load_image_grayscale);
		//img1 = imread("blobdetect.png", cv_load_image_grayscale);
		/*Mat img2(img1.rows, img1.cols, CV_8UC1(0));
		Mat img3 = blob(img1);*/
		//namedWindow("s", WINDOW_AUTOSIZE);
		
		//waitKey(0);
		//Mat image(200, 300, CV_8UC3, Scalar(0, 0, 255));
		//char win[] = "Striped Image"; //String with the name of the window
		//int location;
		//for (int i = 0; i<image.rows; i++)
		//{
		//	for (int j = 0; j<image.cols; j++)
		//	{
		//		image.at<Vec3b>(i, j)[0] = 0;
		//		image.at<Vec3b>(i, j)[1] = 0;
		//		image.at<Vec3b>(i, j)[2] = 0;
		//		if (i<image.rows / 3)
		//			image.at<Vec3b>(i, j)[0] = 255;	//Blue
		//		else if (i >= (2 * image.rows) / 3)
		//			image.at<Vec3b>(i, j)[2] = 255;	//Red
		//		else
		//			image.at<Vec3b>(i, j)[1] = 255;	//Green
		//	}
		//}
		//namedWindow(win, CV_WINDOW_AUTOSIZE);
		//imshow(win, image);
		//waitKey(0);
		//return 0;
		//houghlinecreate(img1);
		/*hough(img1);
		
		for (int i = 0; i < img2.rows; i++)
		{
			int y =(int)( (w - i*cos(u*3.14/180) / sin(u*3.14/180)));
			img2.at<uchar>(i,y) = 255;
			cout << i << y;
		}
		namedWindow("s", WINDOW_AUTOSIZE);
		imshow("s", img2);
		waitKey(0);*/
		/*Mat img1;
		img1 = imread("blodetect.png", CV_LOAD_IMAGE_GRAYSCALE);
		Mat img2=blobdetect(img1);*/
		/*Mat img1;
		img1 = imread("Untitled.png", CV_LOAD_IMAGE_COLOR);
		int hue = 16; int x = 10,sat=10,light=0;
		namedWindow("tol", WINDOW_AUTOSIZE);
		createTrackbar("value", "tol", &hue, 255);
		createTrackbar("value", "tol", &sat, 255);
		createTrackbar("value", "tol", &light, 255);
		while (1)
		{
			Mat img2;
/			cvtColor(img1, img2, CV_BGR2HLS);
			Mat img3 = identifyingHSV(img2, hue,sat,light);
			imshow("tol", img3);
			char a = waitKey(2);
			if (a == 27)break;
		}*/
		/*Mat img1;
		img1=imread("Untitled.png", CV_LOAD_IMAGE_COLOR);
		int hue = 16; int x = 10;
		namedWindow("tol", WINDOW_AUTOSIZE);
		createTrackbar("value", "tol", &hue, 255);
		while (1)
		{
			Mat img2;
			cvtColor(img1, img2, CV_BGR2HSV);
			Mat img3 = identifyingHSV(img2, hue);
			imshow("tol", img3);
			char a = waitKey(2);
			if (a == 27)break;
		}*/
		/*VideoCapture v(0);
		int x = 10;
		namedWindow("new", WINDOW_AUTOSIZE);
		createTrackbar("value", "new", &x, 255);
		while (1)
		{
			Mat frame;
			v >> frame;
			Mat gimg=Grayscale(frame);
			//cvtColor(frame, gimg, CV_BGR2GRAY);
			gimg = prewett(gimg);
			Mat bing = edge(gimg, x);
			imshow("new", gimg);
			char a = waitKey(2);
			if (a == 27)break;
		}*/
		//Mat img;
		/*int x = 10;
		namedWindow("changing", WINDOW_AUTOSIZE);
		createTrackbar("value", "changing", &x, 255);*/
		//img = imread("k.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	 //avgborder(img);
		//median(img);
		//gauss(img);
		//namedWindow("s", WINDOW_AUTOSIZE);
		//imshow("s", img); int in = 0, up = 0;
		//createTrackbar("1", "s", &in, 255);
		//createTrackbar("2", "s", &up, 255);
		/*while (1)
		{
			Mat img1;
			Canny(img, img1, in, up, 3);
			imshow("s", img1);
			//Mat bing = edge(img,x);
			//bing = dilate(bing);
			//bing = erode(bing);
			//imshow("changing", bing);
				char a = waitKey(33);
			if (a == 27)break;

		}*/
		//Mat img2 =prewett(img);
		//img2 = prewett(img2);
	//Mat img2=edge(bing);
		//invert();
		//histo();
	/*namedWindow("s", WINDOW_AUTOSIZE);
	imshow("s", img2);*/
		
		return 0;
	}