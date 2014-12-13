#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>
#include<algorithm>
#include<dos.h>
using namespace cv;
using namespace std;
Mat cir_cle(Mat);
Mat three_parts(Mat);
Mat check_box(Mat);
Mat grey(Mat);
Mat binary(Mat,int);
Mat invert(Mat);
int thres(Mat,char);
Mat show_modi(Mat, int, int, int);
Mat grey_modi(Mat,int,int,int);
void trackbar_rgb(char[], int&, int&, int&);
void trackbar_hsv(char[], int&, int&, int&);
void hsvtorgb(int, int, int, int&, int&, int&);
Mat dil_ero(Mat,char);
Mat grey2binary(Mat, int);
Mat border_new(Mat, int);
Mat border_new2(Mat);
Mat border_onlyx(Mat);

Mat mean_filter(Mat,int);
Mat median_filter(Mat,int);
Mat gaussian_filter(Mat,int);
int main()
{
	
	/*
	//CODE FOR RGB VARIATION
	int r = 1; int g = 1; int b = 1;
	trackbar_rgb("Windows", r, g, b);
	
	while (1)
	{
		image = imread("C:\\Users\\nishantiam\\Pictures\\sunset.jpg", 1);
		image = show_modi(image,r,g,b);
		
		imshow("Windows", image);
		int a;
		a = waitKey(33);
		if (a == 27)
			break;
	}
	*/
	/*
	/////CODE TO WRITE THE IMAGE
	vector<int> write;
	write.push_back(CV_IMWRITE_JPEG_QUALITY);
	write.push_back(99);
	imwrite("C:\\Users\\nishantiam\\Pictures\\new.jpg", image, write);
	namedWindow("Drawing", CV_WINDOW_NORMAL);
	imshow("Drawing", image);
	waitKey();*/
	
	
	
/*int thres = 4;
	namedWindow("Drawing", CV_WINDOW_NORMAL);
	createTrackbar("thres", "Drawing", &thres, 255);
	while (1)
	{
		
		Mat image = imread("C:\\Users\\nishantiam\\Pictures\\sunset.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		//image = grey(image);
		//cout << image.rows << " " << image.cols;
		image = border_new(image,thres);
		namedWindow("Drawing", CV_WINDOW_NORMAL);
		imshow("Drawing", image);
		//cout << image.rows << " " << image.cols;
		
		int a = waitKey(33);
		if (a == 27)
			break;
	}*/



	/*
	///////////For noise reduction
	namedWindow("orig", CV_WINDOW_NORMAL);
	namedWindow("dil", CV_WINDOW_NORMAL);
	namedWindow("ero", CV_WINDOW_NORMAL);
	int thres = 150;
	createTrackbar("b_thr", "orig", &thres, 255);
	while (1)
	{	
		Mat image = imread("C:\\Users\\nishantiam\\Pictures\\sunset.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		
		image = grey2binary(image, thres);
		imshow("orig", image);

		image = dil_ero(image,'d');
		imshow("dil", image);
		image = dil_ero(image, 'e');

		imshow("ero", image);
		int a = waitKey(33);
		if (a == 27)
			break;
	}
	*/
	
	/*
	//Code for hsv to rgb conversion
	int h, s, v;
	h = s = v = 0;
	int r, g, b;
	r = g = b = 0;
	trackbar_hsv("win", h, s, v);
	while (1)
	{
		Mat image = imread("C:\\Users\\nishantiam\\Pictures\\sunset.jpg", CV_LOAD_IMAGE_ANYCOLOR);
		hsvtorgb(h, s, v, &r, &g, &b);
		image=show_modi(image, r, g, b);
		imshow("win", image);
	}*/
	
	/////CODE FOR FILTERING BY MEAN AND MEDIAN FILTRATION
	namedWindow("orig", CV_WINDOW_NORMAL);
	namedWindow("chang1", CV_WINDOW_NORMAL);
	namedWindow("chang2", CV_WINDOW_NORMAL);
	namedWindow("chang3", CV_WINDOW_NORMAL);
	int val = 5; int val2 = 5; int val3 = 1;
	createTrackbar("mean_modi", "chang1", &val, 20);
	createTrackbar("median_modi", "chang2", &val2, 20);

	createTrackbar("gaussian_modi", "chang3", &val3, 20);
	while (1)
	{
		Mat image = imread("C:\\Users\\nishantiam\\Pictures\\noise.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		imshow("orig", image);
		image = mean_filter(image,val);
		imshow("chang1", image);
		image = imread("C:\\Users\\nishantiam\\Pictures\\noise.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		image = median_filter(image,val2);
		imshow("chang2", image);
		imread("C:\\Users\\nishantiam\\Pictures\\noise.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		image = gaussian_filter(image,val3);
		imshow("chang3", image);
		int a = waitKey(33);
		if (a == 27)
			break;
	}
/*
//implementing canny
Mat image = imread("C:\\Users\\nishantiam\\Pictures\\noise.jpg", CV_LOAD_IMAGE_GRAYSCALE);
Mat img(image.size(), image.type());
namedWindow("orig", CV_WINDOW_NORMAL);
namedWindow("chang", CV_WINDOW_NORMAL);
int val1 = 50; int val2 = 100;
createTrackbar("lower", "chang", &val1, 255);
createTrackbar("upper", "chang", &val2, 255);
imshow("orig", image);
while (1)
{
	Canny(image, img, val1, val2);
	imshow("chang", img);
	int a = waitKey(33);
	if (a == 27)
		break;

}
*/
}

void trackbar_hsv(char wname[], int &h, int &s, int &v)
{
	namedWindow(wname, CV_WINDOW_NORMAL);
	createTrackbar("HUE", wname, &h, 359);
	createTrackbar("SATURATION", wname, &s, 99);
	createTrackbar("VALUE", wname, &v, 99);

}
void trackbar_rgb(char wname[] ,int &r,int &g,int &b)
{
	namedWindow(wname, CV_WINDOW_NORMAL);
	createTrackbar("RED", wname, &r, 100);
	createTrackbar("GREEN", wname, &g, 100);
	createTrackbar("BLUE", wname, &b, 100);

}
Mat cir_cle(Mat image)
{
	int x = 1000;
	int y = 1000;
	int r = 100;
	int rr = 110;
	for (int i = r; i <= rr; i++)
	{
		for (double l = 1000 - i; l <= 1000 + i; l = l + 0.0001)
		{
			double k = pow((pow(i, 2) - pow(l - 1000, 2)), 0.5);

			{

				image.at<Vec3b>(1000 + k, l)[0] = 0;
				image.at<Vec3b>(1000 + k, l)[1] = 0;
				image.at<Vec3b>(1000 + k, l)[2] = 0;
				image.at<Vec3b>(1000 - k, l)[0] = 0;
				image.at<Vec3b>(1000 - k, l)[1] = 0;
				image.at<Vec3b>(1000 - k, l)[2] = 0;

			}
		}
	}
	return image;
}

Mat three_parts(Mat image)
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (i < image.rows / 3)
			{
				image.at<Vec3b>(i, j)[0] = 0;
				image.at<Vec3b>(i, j)[1] = 165;
				image.at<Vec3b>(i, j)[2] = 255;
			}
			else if (i >= image.rows / 3 && i<image.rows * 2 / 3)
			{
				image.at<Vec3b>(i, j)[0] = 255;
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				{
					image.at<Vec3b>(i, j)[1] = 255;
					image.at<Vec3b>(i, j)[2] = 0;
					image.at<Vec3b>(i, j)[0] = 0;
				}
			}
		}
	}
	return image;
}
Mat check_box(Mat image)
{
	for (int i = 0; i < image.rows; i += image.rows / 5)
	{
		for (int j = 0; j < image.cols; j += image.cols / 5)
		{
			for (int k = i; k < i + (image.rows / 10); k++)
			{
				for (int l = j; l < j + (image.cols / 10); l++)
				{
					image.at<Vec3b>(k, l)[1] = 0;
					image.at<Vec3b>(k, l)[2] = 0;
					image.at<Vec3b>(k, l)[0] = 0;


				}
			}
		}
	}
	for (int i = image.rows / 10; i < image.rows; i += image.rows / 5)
	{
		for (int j = image.cols / 10; j < image.cols; j += image.cols / 5)
		{
			for (int k = i; k < i + (image.rows / 10); k++)
			{
				for (int l = j; l < j + (image.cols / 10); l++)
				{
					image.at<Vec3b>(k, l)[1] = 0;
					image.at<Vec3b>(k, l)[2] = 0;
					image.at<Vec3b>(k, l)[0] = 0;


				}
			}
		}
	}
	return image;
}
Mat grey(Mat img)
{
	Mat image(img.size(), img.type());
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int k = image.at<Vec3b>(i, j)[0] * 0.11 + image.at<Vec3b>(i, j)[1] * 0.33 + image.at<Vec3b>(i, j)[2] * 0.56;
			image.at<Vec3b>(i, j)[1] = k;
			image.at<Vec3b>(i, j)[2] = k;
			image.at<Vec3b>(i, j)[0] = k;

		}
	}
	return image;
}
Mat binary(Mat image,int x=-1)
{
	
	if (x == -1)
	{
		cout << "enter the threshold";
		cin >> x;
	}
	
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int k = image.at<Vec3b>(i, j)[0] * 0.11 + image.at<Vec3b>(i, j)[1] * 0.33 + image.at<Vec3b>(i, j)[2] * 0.56;
			
			if (k >= x)
			{
				image.at<Vec3b>(i, j)[1] = 255;
				image.at<Vec3b>(i, j)[2] = 255;
				image.at<Vec3b>(i, j)[0] = 255;
			}
			else
			{
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[2] = 0;
				image.at<Vec3b>(i, j)[0] = 0;
			}
		}
	}
	return image;
}
Mat invert(Mat image)
{
	//cout << image.rows << " " << image.cols;
	Mat img(image.size(),image.type());
	int k = 0; int l;
	for (int i = image.rows-1; i >= 0; i--)
	{
		l = 0;
		for (int j = image.cols-1; j >= 0; j--)
		{
			img.at<Vec3b>(k, l)[0] = image.at<Vec3b>(i, j)[0];
			img.at<Vec3b>(k, l)[1] = image.at<Vec3b>(i, j)[1];
			img.at<Vec3b>(k, l)[2] = image.at<Vec3b>(i, j)[2];
			l++;
		}
		//imshow("Drawing", image);
		//waitKey();
		k++;
	}
	return img;
}
int thres(Mat image, char imgshow='n')
{
	image = grey(image);
	long int arr[256] = { 0 };
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			arr[image.at<uchar>(i, j)]++;
		}
	}
	Mat img(1000, 256, 0);
	for (int i = 0; i < 256; i++)
	{
		int j = arr[i] / 100;
		for (int k = 0; k <= j; k++)
		{
			img.at<uchar>(999 - k, i) = 0;
		}

	}
	if (imgshow == 'y')
	{	imshow("image", img);
	}
	int i = 0;
	long int count = 0;
	while (count < (image.rows*image.cols) / 2)
	{
		count += arr[i++];
	}
	return i - 1;


}
Mat grey_modi(Mat image,int r,int g,int b)
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int k = image.at<Vec3b>(i, j)[0] * b + image.at<Vec3b>(i, j)[1] * g + image.at<Vec3b>(i, j)[2] * r;
			k /= 100;
			image.at<Vec3b>(i, j)[1] = k;
			image.at<Vec3b>(i, j)[2] = k;
			image.at<Vec3b>(i, j)[0] = k;

		}
	}
	return image;
}
Mat show_modi(Mat image, int r, int g, int b)
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			image.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1]*g/100;
			image.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[1]*r/100;
			image.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[1]*b/100;

		}
	}
	return image;
}

Mat border_new(Mat img,int thres)
{
	
	Mat im_new(img.size(), img.type());
	int max, min;
	for (int i = 1; i <img.rows -1; i+=1)
	{
		for (int j = 1; j < img.cols - 1; j+=1)
		{
			max = 0; min = 255;
			for (int k = i - 1; k <= i + 1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++)
				{
					if (img.at<uchar>(k, l)>max)
						max = img.at<uchar>(k, l);
					else if (img.at<uchar>(k, l) < min)
						min = img.at<uchar>(k, l);
					
				}
			}
			if (max - min>thres)
				im_new.at<uchar>(i, j) = 255;
			else
				im_new.at<uchar>(i, j) = 0;
			
		}
	}
	return im_new;
}
Mat border_new2(Mat img)
{
	
	int pm_x; int pm_y;
	
	
	Mat im_new(img.rows,img.cols,img.type());
	for (int i = 1; i <img.rows - 1; i += 1)
	{
		for (int j = 1; j < img.cols  - 1; j += 1)
		{
			
					
			pm_x = img.at<uchar>(i + 1, j + 1) + img.at<uchar>(i, j + 1) + img.at<uchar>(i - 1, j + 1) - (img.at<uchar>(i + 1, j -1) + img.at<uchar>(i, j -1) + img.at<uchar>(i - 1, j -1));
			pm_y = img.at<uchar>(i + 1, j + 1) + img.at<uchar>(i+1, j ) + img.at<uchar>(i + 1, j - 1) - (img.at<uchar>(i - 1, j - 1) + img.at<uchar>(i-1, j ) + img.at<uchar>(i - 1, j + 1));

			//cout << pm_x << "\n " << pm_y;
			int grd = pow((pow(pm_y, 2) + pow(pm_x, 2)),0.5);
			im_new.at<uchar>(i, j) = grd;
		}
	}

	return im_new;
}
Mat border_onlyx(Mat img)
{

	int pm_x; int pm_y;


	Mat im_new(img.rows, img.cols, img.type());
	for (int i = 1; i <img.rows - 1; i += 1)
	{
		for (int j = 1; j < img.cols - 1; j += 1)
		{


			pm_x = img.at<uchar>(i + 1, j + 1) + img.at<uchar>(i, j + 1) + img.at<uchar>(i - 1, j + 1) - (img.at<uchar>(i + 1, j - 1) + img.at<uchar>(i, j - 1) + img.at<uchar>(i - 1, j - 1));
			//pm_y = img.at<uchar>(i + 1, j + 1) + img.at<uchar>(i + 1, j) + img.at<uchar>(i + 1, j - 1) - (img.at<uchar>(i - 1, j - 1) + img.at<uchar>(i - 1, j) + img.at<uchar>(i - 1, j + 1));

			//cout << pm_x << "\n " << pm_y;
			//int grd = pow((pow(pm_y, 2) + pow(pm_x, 2)), 0.5);
			im_new.at<uchar>(i, j) = pm_x;
		}
	}

	return im_new;
}

Mat dil_ero(Mat img,char wt)
{
	Mat im_new(img.size(), img.type());
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			int black = 0; int white = 0;
			for (int k = i - 1; k <= i + 1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++)
				{
					if (img.at<uchar>(k, l)==255)
						white++;
					else if (img.at<uchar>(k, l) ==0)
						black++;

				}
			}
			if (wt == 'd')
			{
				if (white > black)
					im_new.at<uchar>(i, j) = 255;
				else
					im_new.at<uchar>(i, j) = 0;

			}
			else
			{
				if (white > 0 && black > 0)
				{
					if (white > black)
						im_new.at<uchar>(i, j) = 0;
					else
						im_new.at<uchar>(i, j) = 255;
				}
				else if (black == 0)
				{
					im_new.at<uchar>(i, j) = 255;
				}
				else
					im_new.at<uchar>(i, j) = 0;
			}
		}
	}
	return im_new;
}

Mat grey2binary(Mat image, int x )
{

	if (x == -1)
	{
		cout << "enter the threshold";
		cin >> x;
	}

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			
			if (image.at<uchar>(i,j)>x)
			{
				image.at<uchar>(i, j)=255;
				
			}
			else
			{
				image.at<uchar>(i, j) = 0;
			}
		}
	}
	return image;
}

/*void hsvtorgb(int h, int s, int v, int& r, int& g, int& b)
{
	if (s == 0)
	{
		r = g = b = v * 255;
	}
	else
	{
		float hh = h/360; float ss = s/100; float vv = v/100;
		float cas = hh * 6;
		int cs = (int)cas;
		//int p = vv*(1 - ss) * 255;
		//int q = vv*(1 - ss*(cas - cs))*255;
		//int t = vv*(1 - ss*(1 - cas + cs)) * 255;
		//v=vv*255;
		switch (cs):
		{
		case 0:
			r=v;
			g=t;
			b=p;
			break;
		case 1:
			r=q;
			g=v;
			b=p;
			break;
		case 2:
			r =p;
			g =v;
			b =t;
			break;
		case 3:
			r =p;
			g =q;
			b =v;
			break;
		case 4:
			r =t;
			g =p;
			b =v;
			break;
		case 5:
			r =v;
			g =p;
			b =q;
			break;
		
		}
		
	}
}
*/
Mat median_filter(Mat img,int c)
{
	int t = pow(2 * c + 1, 2);
	vector<int> arr;
	arr.resize(t);
	Mat im_new(img.size(), img.type());
	for (int i = c; i < img.rows - c; i++)
	{
		for (int j = c; j < img.cols - c; j++)
		{
			int count = 0;
			for (int k = i - c; k <= i + c; k++)
			{
				for (int l = j - c; l <= j + c; l++)
				{
					arr[count++] = img.at<uchar>(k, l);
				}
			}
			
			sort(arr.begin(),arr.end());
			int d = t / 2;
			im_new.at<uchar>(i, j) = arr[d];
		}
	}

	return im_new;
}

Mat mean_filter(Mat img,int c)
{
	Mat im_new(img.size(), img.type());
	for (int i = c; i < img.rows - c; i++)
	{
		for (int j = c; j < img.cols -c; j++)
		{
			long int count = 0;
			for (int k = i - c; k <= i +c; k++)
			{
				for (int l = j - c; l <= j + c; l++)
				{
					count = count + img.at<uchar>(k, l);
				}
			}
			im_new.at<uchar>(i, j) = count / pow(2*c+1,2);
		}
	}

	return im_new;
}
Mat gaussian_filter(Mat img,int c)
{

	Mat im_new(img.size(), img.type());
	for (int i = c; i < img.rows - c; i++)
	{
		for (int j = c; j < img.cols - c; j++)
		{
			long int count = 0;
			for (int k = -c; k <= +c; k++)
			{
				for (int l = -c; l <= +c; l++)
				{
					count = count + ((pow(2.718, -(pow(k, 2) + pow(l, 2)) / 2))/6.283)*img.at<uchar>(i+k,j+l);
				}
			}

			im_new.at<uchar>(i, j) = count;
		}
	}

	return im_new;
}