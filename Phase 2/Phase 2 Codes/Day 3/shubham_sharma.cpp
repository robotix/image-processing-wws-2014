Edge detection:
#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;

 uchar diff(Mat,int,int);


int main()
{
	uchar d;
	int Threshold=40;
	int i, j;
	Mat image;
	image = imread("e.jpg", CV_LOAD_IMAGE_COLOR);
	Mat gimage(image.rows, image.cols, CV_8UC1);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			gimage.at<uchar>(i, j) = (uchar)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}

	
	namedWindow("window1", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "window1", &Threshold, 255);
	while (1)
	{
		Mat bimage(image.rows, image.cols, CV_8UC1, Scalar(0));
		for (i = 1; i < (image.rows - 1); i++)
		{
			for (j = 1; j<(image.cols - 1); j++)
			{
				d = diff(gimage,i, j);
				if (d>Threshold)
					bimage.at<uchar>(i, j) = 255;
			}
		}
		
		imshow("window1", bimage);
		int a = waitKey(33);
		if (a == 27)
			break;
	}
		
	    return 0;
}

uchar diff(Mat gimage,int i, int j)
{
	int k,l;
	uchar d;
	uchar s=gimage.at<uchar>(i,j);
	uchar s1 = gimage.at<uchar>(i, j);
	
			for (k = (i - 1); k <= (i + 1); k++)
			{
				for (l = (j - 1); l <= (j + 1); l++)
				{
					if (s < gimage.at<uchar>(k, l))
						s = gimage.at<uchar>(k, l);
					if (s1 > gimage.at<uchar>(k, l))
						s1 = gimage.at<uchar>(k, l);
				}
			}
			d = s - s1;
			return d;
} 

Edge detection2:
#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include<math.h>
using namespace cv;
using namespace std;


int nfunc(Mat,int,int);

int main()
{
	uchar d;
	int i, j;
	Mat image;
	image = imread("q2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat gimage(image.rows, image.cols, CV_8UC1);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			gimage.at<uchar>(i, j) = (uchar)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}


	Mat nimage(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < (image.rows - 1); i++)
	{
		for (j = 1; j<(image.cols - 1); j++)
		{
			d = nfunc(gimage, i, j);
			nimage.at<uchar>(i, j) = d;
		}
	}
	namedWindow("window1", WINDOW_AUTOSIZE);
	imshow("window1", nimage);
	waitKey(0);
	return 0;
}

int nfunc(Mat gimage, int i, int j)
{
	int x, y,d;
		

	x = (gimage.at<uchar>((i - 1), (j + 1)) + gimage.at<uchar>((i), (j + 1)) + gimage.at<uchar>((i + 1), (j + 1))) - (gimage.at<uchar>((i - 1), (j - 1)) + gimage.at<uchar>((i), (j - 1)) + gimage.at<uchar>((i + 1), (j - 1)));
	y = (gimage.at<uchar>((i + 1), (j - 1)) + gimage.at<uchar>((i + 1), (j)) + gimage.at<uchar>((i + 1), (j + 1))) - (gimage.at<uchar>((i - 1), (j - 1)) + gimage.at<uchar>((i - 1), (j)) + gimage.at<uchar>((i - 1), (j + 1)));
	d = sqrt((x*x) + (y*y));
	return d;
} 

Edge Detection 3:
#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include<math.h>
using namespace cv;
using namespace std;


 int nfunc(Mat, int, int);

int main()
{
	uchar d;
	int i, j;
	Mat image;
	image = imread("e.jpg", CV_LOAD_IMAGE_COLOR);
	
	Mat gimage(image.rows, image.cols, CV_8UC1);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			gimage.at<uchar>(i, j) = (uchar)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}

	Mat nimage(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < (image.rows - 1); i++)
	{
		for (j = 1; j<(image.cols - 1); j++)
		{
			d = nfunc(gimage, i, j);
			nimage.at<uchar>(i, j) = d;
		}
	}
	
	Mat n1image(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < (image.rows - 1); i++)
	{
		for (j = 1; j<(image.cols - 1); j++)
		{
			d = nfunc(nimage, i, j);
			n1image.at<uchar>(i, j) = d;
		}
	}
	namedWindow("window1", WINDOW_AUTOSIZE);
	imshow("window1", nimage);

	
	namedWindow("window2", WINDOW_AUTOSIZE);
	imshow("window2", n1image);

	waitKey(0);
	return 0;
}

int nfunc(Mat gimage, int i, int j)
{
	int x, y, d;


	x = (gimage.at<uchar>((i - 1), (j + 1)) + gimage.at<uchar>((i), (j + 1)) + gimage.at<uchar>((i + 1), (j + 1))) - (gimage.at<uchar>((i - 1), (j - 1)) + gimage.at<uchar>((i), (j - 1)) + gimage.at<uchar>((i + 1), (j - 1)));
	y = (gimage.at<uchar>((i + 1), (j - 1)) + gimage.at<uchar>((i + 1), (j)) + gimage.at<uchar>((i + 1), (j + 1))) - (gimage.at<uchar>((i - 1), (j - 1)) + gimage.at<uchar>((i - 1), (j)) + gimage.at<uchar>((i - 1), (j + 1)));
	d = sqrt((x*x) + (y*y));
	return d;
} 

Dilation:
#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;

 uchar diff(Mat, int, int);
Mat dilation(Mat, int, int);

int main()
{
	uchar d;
	int Threshold = 0,flag=0,flag1=0;
	int i, j,k,l,p=0,q=0;
	Mat image;
	image = imread("e.jpg", CV_LOAD_IMAGE_COLOR);
	Mat gimage(image.rows, image.cols, CV_8UC1);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			gimage.at<uchar>(i, j) = (uchar)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}


	namedWindow("image", WINDOW_AUTOSIZE);
	namedWindow("bimage", WINDOW_AUTOSIZE);
	namedWindow("b1image", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "bimage", &Threshold, 255);
	createTrackbar("Threshold", "b1image", &Threshold, 255);


	while (1)
	{
		Mat bimage(image.rows, image.cols, CV_8UC1, Scalar(0));
		for (i = 1; i < (image.rows - 1); i++)
		{
			for (j = 1; j<(image.cols - 1); j++)
			{
				d = diff(gimage, i, j);
				if (d>Threshold)
					bimage.at<uchar>(i, j) = 255;
			}
		}
		
		Mat b1image(image.rows, image.cols, CV_8UC1, Scalar(0));

		b1image = bimage;
		for (i = 1; i < (image.rows-1); i++)
		{
			for (j = 1; j < (image.cols - 1); j++)
			{
				for (k = (i - 1); k <= (i + 1); k++)
				{
					for (l = (j - 1); l <= (j + 1); l++)
					{
						if (b1image.at<uchar>(k, j) == 0)
						{
							flag++;
						}
						else
							flag1++;
					}

				}
				if (flag>flag1)
                  bimage.at<uchar>(i, j) = 0;
			}
		}
		
		imshow("image", image);
		imshow("bimage", bimage);
		imshow("b1image", b1image);
		int a = waitKey(33);
		if (a == 27)
			break;
	}

	return 0;
}

uchar diff(Mat gimage, int i, int j)
{
	int k, l;
	uchar d;
	uchar s = gimage.at<uchar>(i, j);
	uchar s1 = gimage.at<uchar>(i, j);

	for (k = (i - 1); k <= (i + 1); k++)
	{
		for (l = (j - 1); l <= (j + 1); l++)
		{
			if (s < gimage.at<uchar>(k, l))
				s = gimage.at<uchar>(k, l);
			if (s1 > gimage.at<uchar>(k, l))
				s1 = gimage.at<uchar>(k, l);
		}
	}
	d = s - s1;
	return d;
} 

Average filter:
#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;

 uchar diff(Mat,int,int);


int main()
{
uchar d;
int i, j,k,l;
Mat image;
image = imread("e.jpg", CV_LOAD_IMAGE_COLOR);

Mat gimage(image.rows, image.cols, CV_8UC1);


for (i = 0; i < image.rows; i++)
{
	for (j = 0; j < image.cols; j++)
	{
		gimage.at<uchar>(i, j) = (uchar)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
	}
}

Mat afimage=gimage.clone();

for (i = 1; i < (gimage.rows-1); i++)
{
	for (j = 1; j < (gimage.cols-1); j++)
	{
		int s = 0;
		for (k = i - 1; k <= i + 1; k++)
		{
			for (l = j - 1; l <= j + 1; l++)
			{
				s += gimage.at<uchar>(k, l);
			}
		}
		afimage.at<uchar>(i, j) = s/9;
	}
} 

namedWindow("image", WINDOW_AUTOSIZE);
namedWindow("gimage", WINDOW_AUTOSIZE);
 namedWindow("afimage", WINDOW_AUTOSIZE);
imshow("image", image);
imshow("gimage", gimage);
imshow("afimage", afimage);

waitKey(0);

return 0;
} 

Median filter:
#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;

uchar medianfilter(Mat, int, int);


int main()
{
	uchar d;
	int i, j, k, l;
	Mat image;
	image = imread("e.jpg", CV_LOAD_IMAGE_COLOR);

	Mat gimage(image.rows, image.cols, CV_8UC1);


	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			gimage.at<uchar>(i, j) = (uchar)(0.56*image.at<Vec3b>(i, j)[0] + 0.33*image.at<Vec3b>(i, j)[1] + 0.11*image.at<Vec3b>(i, j)[2]);
		}
	}

	Mat mfimage = gimage.clone();

	for (i = 1; i < (gimage.rows - 1); i++)
	{
		for (j = 1; j < (gimage.cols - 1); j++)
		{
			mfimage.at<uchar>(i, j) = medianfilter(gimage, i, j);
		}
	}

	namedWindow("image", WINDOW_AUTOSIZE);
	namedWindow("gimage", WINDOW_AUTOSIZE);
	namedWindow("mfimage", WINDOW_AUTOSIZE);
	imshow("image", image);
	imshow("gimage", gimage);
	imshow("mfimage", mfimage);

	waitKey(0);

	return 0;
}

uchar medianfilter(Mat gimage, int i, int j)
{
	uchar a[9],t;
	int p = 0,k,l;
	for (k = i - 1; k <= i + 1; k++)
	{
		for (l = j - 1; j <= j + 1; j++)
		{
			a[p] = gimage.at<uchar>(k, l);
			p++;
		}
	}
	p--;
	for (i = 0; i <= 8; i++)
	{
		if (a[i] > a[i + 1])
		{
			t = a[i];
			a[i] = a[i + 1];
			a[i + 1] = t;
		}
	}

	return a[4];
}