// vision2.cpp : Defines the entry point for the console application.
//     pastebin.com
// sengoku basara?? attack on titans, campione
//abhinav.jain@robotix.in
#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

#define	gs(x,y)	img.at<uchar>(x, y) 

int tb2();
int scharr(Mat);
Mat gtob(int, Mat);
Mat grayscale(int, int, int);
int rw();
int flag();
void invert(Mat& img);
int histo();
Mat edge_detect(uchar);
int krcheck(Mat img, uchar thresh, int i, int j);
Mat sobel1(Mat);
Mat dilation(Mat img);
Mat erosion(Mat);
Mat meanfilter(Mat);
int median(int a[]);
Mat medianfilter(Mat img);
void swap(int *x, int *y);
Mat gauss_filter(Mat img);
int main()
{
	int low = 50, high = 100;
	Mat inpimg = grayscale(1, 1, 1);
	Mat out(inpimg.rows, inpimg.cols, CV_8UC1);
	namedWindow("canned", WINDOW_AUTOSIZE);
	createTrackbar("low", "canned", &low, 80);
	createTrackbar("high", "canned", &high, 150);
	
	while (1)
	{	
		Canny(inpimg, out, low, high);
		imshow("canned", out);
		char a = waitKey(33);
		if (a == 27)
		{
			break;
		}
	}

}
Mat gauss_filter(Mat img)
{
	Mat imfil(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, l, k;
	int value;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			imfil.at<uchar>(i,j) = 0.06*(gs(i - 1, j - 1) + gs(i - 1, j + 1) + gs(i + 1, j - 1) + gs(i + 1, j + 1)) + 0.098*(gs(i-1, j) + gs(i+1, j) + gs(i, j-1) + gs(i, j+1)) + 0.162*(gs(i, j));			
		}
	}
	return imfil;

}
void swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
Mat medianfilter(Mat img)
{
	int i, j, k, l, r, med;
	int a[9];
	Mat imfil(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1 ; j < img.cols - 1; j++)
		{
			r = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					a[r++] = gs(k, l);
				}
			}
			imfil.at<uchar>(i, j) = median(a);
		}
	}

	return imfil;

}
int median(int a[])
{
	int  i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = i; j < 9 - i - 1; j++)
		{
			if (a[j] >= a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
			}
		}
	}
	return a[4];
}

Mat meanfilter(Mat img)
{
	int i, j, k, l, mean;
	Mat imfil(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			mean = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					mean += gs(k, l);
				}
			}
	
			imfil.at<uchar>(i, j) = (mean / 9);
		}
	}
	
	return imfil;

}

Mat dilation(Mat img)
{
	int i, j, black, white, k, l;
	Mat imdil(img.rows, img.cols, CV_8UC1);
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			black = white = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{	
					if (gs(k, l) == 0)
						black++;
					else white++;
				}
			}
			if (black > white)
				imdil.at<uchar>(i, j) = 0;
			else
				imdil.at<uchar>(i, j) = 255;
		}
	}
	return imdil;
}
Mat erosion(Mat img)
{
	int i, j, black, white, k, l;
	Mat imer(img.rows, img.cols, CV_8UC1);
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			black = white = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (gs(k, l) == 0)
						black++;
					else white++;
				}
			}
			if (black > white)
			{
				if (white == 0)
				imer.at<uchar>(i, j) = 0;
				else 
					imer.at<uchar>(i, j) = 255;

			}
			else  
			{
				if (black == 0)
				imer.at<uchar>(i, j) = 255;
				else 
					imer.at<uchar>(i, j) = 0;
			}

		}
	}

	return imer;
}





int scharr(Mat imgray)
{
	//string str = "A:\\Scenary.jpg";
	//Mat imgray = imread(str, 0);
	Mat fin, gradx, grady, agradx, agrady;

	Scharr(imgray, gradx, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(gradx, agradx);

	//Scharr(imgray, grady, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	//convertScaleAbs(grady, agrady);

//	addWeighted(agradx, 0.5, agrady, 0.5, 0, fin);
	imshow("Bird", agradx);
	waitKey(0);
	return 0;
}
Mat sobel1(Mat img)
{
//	Mat img = grayscale(55, 33, 11);
	Mat im(img.rows, img.cols, CV_8UC1);
	Mat im1(img.rows, img.cols, CV_8UC1);
	float dx, dy, df, dx1, dy1, df1;
	int i, j;
	for (i = 1; i < img.rows-1; i++)
	{
		for (j = 1; j < img.cols-1; j++)
		{
			dx = gs(i - 1, j - 1) + gs(i - 1, j) + gs(i - 1, j + 1) - gs(i + 1, j - 1) - gs(i + 1, j) - gs(i + 1, j + 1);
			dy = gs(i - 1, j - 1) + gs(i , j - 1) + gs(i + 1, j - 1) - gs(i - 1, j + 1) - gs(i , j + 1) - gs(i + 1, j + 1);
			dx1 = -1*(gs(i - 1, j - 1) + 2*gs(i - 1, j) + gs(i - 1, j + 1) - gs(i + 1, j - 1) - 2*gs(i + 1, j) - gs(i + 1, j + 1));
			dy1 = -1*(gs(i - 1, j - 1) + 2*gs(i, j - 1) + gs(i + 1, j - 1) - gs(i - 1, j + 1) - 2*gs(i, j + 1) - gs(i + 1, j + 1));
			df = sqrt(dx*dx + dy*dy);
			df1 = sqrt(dx1*dx1 + dy1*dy1);
			if (df >= 255)
				im.at<uchar>(i, j) = 255;
			else im.at<uchar>(i, j) = df;
			if (df1 >= 255)
				im1.at<uchar>(i, j) = 255;
			else im1.at<uchar>(i, j) = df;
		}
	}
	//namedWindow("Sob1", WINDOW_AUTOSIZE);
	//namedWindow("Sob2", WINDOW_AUTOSIZE);
	//imshow("Sob1", im);
	//imshow("Sob2", im1);
	//waitKey(0);
	return im1;// returning sobel

}

Mat edge_detect(uchar thresh)
{
	Mat img = grayscale(55, 33, 11);

	Mat im(img.rows, img.cols, CV_8UC1);
	
	int i, j;

	for (i = 1; i < img.rows-1; i++)
	{
		for (j = 1; j < img.cols-1; j++)
		{
			if (krcheck(img, thresh, i, j ))
				im.at<uchar>(i, j) = 255;
			else
				im.at<uchar>(i, j) = 0;
		}
	}
	return im;
}
int krcheck(Mat img, uchar thresh, int i, int j)
{
	int k, l;
	uchar max = 0, min = 255;
	for (k = i - 1; k <= i + 1; k++)
	{
		for (l = j - 1; l <= j + 1; l++)
		{
			if (img.at<uchar>(k, l) >= max)
			{
				max = img.at<uchar>(k, l);
			}
			if (img.at<uchar>(k, l) <= min)
			{
				min = img.at<uchar>(k, l);
			}
		}
	}
	if ((max - min) > thresh)
		return 1;
	else return 0;
}

int tb2()
{
	int x = 100, slut = 100, y = 100;
	int i, j;
	string str = "C:\\Users\\Hellblazer\\Documents\\Visual Studio 2013\\Projects\\vision2\\cw.png";
	Mat img = imread(str, 1);
	namedWindow("Bitch", WINDOW_AUTOSIZE);
	createTrackbar("Red", "Bitch", &slut, 255);
	while (1 && x + slut <= 255)
	{
		createTrackbar("Blue", "Bitch", &x, 255 - slut);

		imshow("Bitch", img);
		waitKey(33);
	}


	return 0;
}
int tb1()
{
	int fuck = 50;
	Mat img = grayscale(55, 33, 11);
	namedWindow("wind", WINDOW_AUTOSIZE);
	createTrackbar("Meter", "wind", &fuck, 255);
	while (1)
	{

		Mat im = gtob(fuck, img);
		imshow("wind", im);
		char a = waitKey(33);
		if (a == 27)
			break;

	}
	return 0;
}
int histo()
{
	int i, j;
	//string str = "A:\\1.png";
	long long int hist[256] = { 0 };
	Mat img = grayscale(55, 33, 11);
	//int threshold;
	//cout << "enter threshold\n";
	///cin >> threshold;
	//gtob(threshold, img);
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			hist[img.at<uchar>(i, j)]++;
		}
	}
	long long int no_pix = img.rows * img.cols;
	long long int sum = 0, threshold;
	for (i = 0; i < 256 && sum <= (no_pix / 2); i++)
	{
		sum += hist[i];
	}
	threshold = i;
	cout << threshold;
	Mat his(300, 256, CV_8UC1, Scalar(0));
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < hist[i] / 10; j++)
		{
			his.at<uchar>(j, i) = 255;
		}
	}
	invert(his);
	imshow("bitch", his);
	waitKey(0);
	return 0;
}
void invert(Mat& img)
{
	int i, j, k;
	for (i = 0; i <= (img.rows) / 2; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			// img is bgr
			/*
			Vec3b col1 = img.at<Vec3b>(i, j);
			Vec3b col2 = img.at<Vec3b>(img.rows - 1 - i, j);
			Vec3b tmp = col1;
			col1 = col2;
			col2 = tmp;
			img.at<Vec3b>(i, j) = col1;
			img.at<Vec3b>(img.rows - 1 - i, j) = col2;
			*/
			// img is bw
			uchar tmp = img.at<uchar>(i, j);
			img.at<uchar>(i, j) = img.at<uchar>(img.rows - 1 - i, j);
			img.at<uchar>(img.rows - 1 - i, j) = tmp;



		}
	}
}

Mat gtob(int threshold, Mat im)
{
	Mat img(im.rows, im.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < im.rows; i++)
	{
		for (j = 0; j < im.cols; j++)
		{
			if (im.at<uchar>(i, j) > threshold)
			{
				img.at<uchar>(i, j) = 255;
			}
			else
				img.at<uchar>(i, j) = 0;
		}
	}

	return img;

}





Mat grayscale(int red, int blue, int green)
{
	string str = "A:\\skyscrapers_and_couds-t2.jpg";
	//zY5euSP.jpg
	// 1.png
	//9deeSaM.jpg
	//Ferrari-599-GTB-widescreen-001.jpg
	//CYB0049.jpg
	//38709.jpg
	//skyscrapers_and_couds-t2.jpg
	Mat img = imread(str, 1);
	Mat im(img.rows, img.cols, CV_8UC1);
	Mat im1(img.rows, img.cols, CV_8UC1);
	Mat im2(img.rows, img.cols, CV_8UC1);
	Mat im12(img.rows, img.cols, CV_8UC1);

	// best grayscale from colored (.56, .33, .11)
	int i, j;
	for (i = 0; i < img.cols; i++)
	{
		for (j = 0; j < img.rows; j++)
		{

			Vec3b color = img.at<Vec3b>(j, i);
			im.at<uchar>(j, i) = color[0];
			im1.at<uchar>(j, i) = color[1];
			im2.at<uchar>(j, i) = color[2];
			im12.at<uchar>(j, i) = color[0] *.55 + .33*color[1] + color[2] *.11;
		}
	}

	//namedWindow("bitch", WINDOW_AUTOSIZE);
	//namedWindow("bitch1", WINDOW_AUTOSIZE);
	//namedWindow("bitch2", WINDOW_AUTOSIZE);
	//namedWindow("bitch12", WINDOW_AUTOSIZE);
	//imshow("bitch", im);
	//imshow("bitch1", im1);
	//imshow("bitch2", im2);
	//imshow("bitch12", im12);
	return im12;
}

int rw()
{
int x, y;
string str = "A:\\1.png";
Mat im = imread(str, CV_LOAD_IMAGE_COLOR);
// imread(, 1) colored in bgr
// imread(, 0) grayscale

//Mat im = imread("A:\\zY5euSP.jpg", CV_LOAD_IMAGE_COLOR);
//namedWindow("sc", WINDOW_AUTOSIZE);
namedWindow("sb", WINDOW_AUTOSIZE);
imshow("sb", im);
waitKey(0);
for (y = 0; y < im.rows; y++)
{


for (x = 0; x < im.cols; x++)
{
Vec3b color = im.at<Vec3b>(y, x); // a vector of dim 3
color[1] = color[2] = 0;
im.at<Vec3b>(y, x) = color;
}

}
namedWindow("sb", WINDOW_AUTOSIZE);
imshow("sb", im);
waitKey(0);
//	imshow("sb", image);
return 0;
}


int flag()
{

Mat img (300, 300, CV_8UC3, Scalar(0,0,0));
int i, j;

for (i = 0; i < 300; i++)
{

for (j = 0; j < 100; j++)
{
img.at<Vec3b>(i, j)[0] = 120; // 0 128 255
img.at<Vec3b>(i, j)[1] = 128;
img.at<Vec3b>(i, j)[2] = 255;
}
for (j = 100; j < 200; j++)
{
img.at<Vec3b>(i, j)[0] = 255; // 255 255 255
img.at<Vec3b>(i, j)[1] = 255;
img.at<Vec3b>(i, j)[2] = 255;
}
for (j = 200; j < 300; j++)
{
img.at<Vec3b>(i, j)[0] = 10; // 0 255 0
img.at<Vec3b>(i, j)[1] = 255;
img.at<Vec3b>(i, j)[2] = 110;
}
}

namedWindow("bitch", WINDOW_AUTOSIZE);
imshow("bitch", img);
waitKey(0);
return 0;
}

/*int thresh = 20;
namedWindow("Wind", WINDOW_AUTOSIZE);
//Mat image = edge_detect(thresh);
createTrackbar("Bitch", "Wind", &thresh, 200);
while (1)
{
Mat image = edge_detect(thresh);
imshow("Wind", image);
char a = waitKey(33);
if (a == 27)
break;
}
Mat image = sobel1();
imshow("sobel1", image);
waitKey(0);
scharr(grayscale(1,1,1));
Mat img = edge_detect(50);
Mat imdilated = dilation(img);
Mat imeroded = erosion(imdilated);
//namedWindow("bin", WINDOW_AUTOSIZE);
imshow("bin", img);
imshow("dil1", imdilated);
imshow("erod1", imeroded);
waitKey(0);

//filtered
Mat img = grayscale(1, 1, 1);
Mat filtered = medianfilter(img);
Mat medfilt = medianfilter(img);
Mat gausfilt = gauss_filter(img);
imshow("Unfiltered", img);
imshow("Mean Filtered", filtered);
imshow("Med Filtered", medfilt);
imshow("gauss", gausfilt);
waitKey(0);
*/