

#include"stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<math.h>
using namespace std;
using namespace cv;

Mat detection(Mat image, int thresh)
{
	Mat binary(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols - 1; j++)
		{
			int max, min;
			max = min = image.at<uchar>(i, j);
			for (int k = i - 1; k < (i + 2); k++)
			{
				for (int l = j - 1; l < (j + 2); l++)
				{
					if (image.at<uchar>(k, l)>max)
						max = image.at<uchar>(k, l);
					if (image.at<uchar>(k, l)<min)
						min = image.at<uchar>(k, l);
				}
			}
			if ((max - min) >= thresh)
				binary.at<uchar>(i, j) = 255;
			if ((max - min) < thresh)
				binary.at<uchar>(i, j) = 0;
		}
	}
	for (int j = 0; j < image.cols; j++)
	{
		binary.at<uchar>(0, j) = 0;
		binary.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		binary.at<uchar>(j, 0) = 0;
		binary.at<uchar>(j, image.cols - 1) = 0;
	}
	return(binary);
}

Mat detection1(Mat image)
{
	Mat detect(image.rows, image.cols, CV_8UC1);

	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols - 1; j++)
		{
			int dx, dy;
			dx = (image.at<uchar>(i - 1, j + 1)) - (image.at<uchar>(i - 1, j - 1)) + (image.at<uchar>(i, j + 1)) - (image.at<uchar>(i, j - 1)) + (image.at<uchar>(i + 1, j + 1)) - (image.at<uchar>(i + 1, j - 1));
			dy = (image.at<uchar>(i + 1, j - 1)) - (image.at<uchar>(i - 1, j - 1)) + (image.at<uchar>(i + 1, j)) - (image.at<uchar>(i - 1, j)) + (image.at<uchar>(i + 1, j + 1)) - (image.at<uchar>(i - 1, j + 1));
			detect.at<uchar>(i, j) = (int)(sqrt(pow(dx, 2) + pow(dy, 2)));
		}
	}

	for (int j = 0; j < image.cols; j++)
	{
		detect.at<uchar>(0, j) = 0;
		detect.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		detect.at<uchar>(j, 0) = 0;
		detect.at<uchar>(j, image.cols - 1) = 0;
	}
	return(detect);
}

Mat dilation(Mat image)
{
	Mat dilated(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols - 1; j++)
		{
			int bcount = 0, wcount = 0;
			for (int k = i - 1; k < i + 1; k++)
			{
				for (int l = j - 1; l < j + 2; l++)
				{
					if (image.at<uchar>(k, l) == 255)
						wcount++;
					if (image.at<uchar>(k, l) == 0)
						bcount++;
				}
			}
			if ((wcount>bcount))
				dilated.at<uchar>(i, j)=255;
			if ((wcount<bcount))
				dilated.at<uchar>(i, j) = 0;
		}
	}
	for (int j = 0; j < image.cols; j++)
	{
		dilated.at<uchar>(0, j) = 0;
		dilated.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		dilated.at<uchar>(j, 0) = 0;
		dilated.at<uchar>(j, image.cols - 1) = 0;
	}
	return(dilated);
}

Mat erosion(Mat image)
{
	Mat eroted(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols - 1; j++)
		{
			int bcount = 0, wcount = 0;
			for (int k = i - 1; k < i + 1; k++)
			{
				for (int l = j - 1; l < j + 2; l++)
				{
					if (image.at<uchar>(k, l) == 255)
						wcount++;
					if (image.at<uchar>(k, l) == 0)
						bcount++;
				}
			}
			if (bcount >= 0 && wcount >= 0 && (wcount>bcount))
				eroted.at<uchar>(i, j) = 0;
			if (bcount >= 0 && wcount >= 0 && (wcount<bcount))
				eroted.at<uchar>(i, j) = 255;
		}
	}
	for (int j = 0; j < image.cols; j++)
	{
		eroted.at<uchar>(0, j) = 0;
		eroted.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		eroted.at<uchar>(j, 0) = 0;
		eroted.at<uchar>(j, image.cols - 1) = 0;
	}
	return(eroted);
}

Mat meanfilter(Mat image)
{
	Mat result(image.rows,image.cols,CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols; j++)
		{
			result.at<uchar>(i, j) = ((image.at<uchar>(i - 1, j - 1) + image.at<uchar>(i - 1, j) + image.at<uchar>(i - 1, j + 1) + image.at<uchar>(i, j - 1) + image.at<uchar>(i, j) + image.at<uchar>(i, j + 1) + image.at<uchar>(i + 1, j - 1) + image.at<uchar>(i + 1, j) + image.at<uchar>(i+1,j+1) ) / 9);
		}
	}
	for (int j = 0; j < image.cols; j++)
	{
		result.at<uchar>(0, j) = 0;
		result.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		result.at<uchar>(j, 0) = 0;
		result.at<uchar>(j, image.cols - 1) = 0;
	}
	return(result);

}

int mediancalc(int a[9])
{
	for (int i = 0; i<8; i++)
	{
		for (int j = i + 1; j<9; j++)
		{
			if (a[i]>a[j])
			{
				int b = a[i];
				a[i] = a[j];
				a[j] = b;
			}
		}
	}
	return(a[4]);
}

Mat medianfilter(Mat image)
{
	Mat result(image.rows,image.cols,CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols - 1; j++)
		{
			int a[9];
			a[0] = image.at<uchar>(i-1,j-1);
			a[1] = image.at<uchar>(i-1,j);
			a[2] = image.at<uchar>(i-1,j+1);
			a[3] = image.at<uchar>(i,j-1);
			a[4] = image.at<uchar>(i,j);
			a[5] = image.at<uchar>(i,j+1);
			a[6] = image.at<uchar>(i+1,j-1);
			a[7] = image.at<uchar>(i+1,j);
			a[8] = image.at<uchar>(i+1,j+1);
			result.at<uchar>(i, j) = mediancalc(a);
		}
	}
	for (int j = 0; j < image.cols; j++)
	{
		result.at<uchar>(0, j) = 0;
		result.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		result.at<uchar>(j, 0) = 0;
		result.at<uchar>(j, image.cols - 1) = 0;
	}
	return(result);
}

Mat gaussianfilter(Mat image)
{
	Mat result(image.rows,image.cols,CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++)
	{
		for (int j = 1; j < image.cols - 1; j++)
		{
			result.at<uchar>(i, j) = (int)((image.at<uchar>(i-1,j-1)*0.06) + (image.at<uchar>(i-1,j)*0.098) + (image.at<uchar>(i-1,j+1)*0.06) + (image.at<uchar>(i,j-1)*0.098) + (image.at<uchar>(i,j)*0.162) + (image.at<uchar>(i,j+1)*0.098) + (image.at<uchar>(i+1,j-1)*0.06) + (image.at<uchar>(i+1,j)*0.098) + (image.at<uchar>(i+1,j+1)*0.06) );
		}
	}
	for (int j = 0; j < image.cols; j++)
	{
		result.at<uchar>(0, j) = 0;
		result.at<uchar>(image.rows - 1, j) = 0;
	}
	for (int j = 0; j < image.rows; j++)
	{
		result.at<uchar>(j, 0) = 0;
		result.at<uchar>(j, image.cols - 1) = 0;
	}
	return(result);
}

int main()
{
	Mat image = imread("c:\\Users\\V.Uday\\Desktop\\fb pics\\devuda.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Mat result;
	int x, y;
	namedWindow("Window1",WINDOW_AUTOSIZE);
	createTrackbar("lower threshhold","Window1",&x,255);
	createTrackbar("upper threshhold","Window1",&y,255);
	while (1)
	{
		Canny(image,result,x,y);
		imshow("Window1",result);
		char a = waitKey(33);
		if (a == 27)break;
	}
	return(0);
}