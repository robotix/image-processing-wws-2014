#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define lli long long int

using namespace std;
using namespace cv;

int otsu(lli histogram[],lli total)
{
	lli sum = 0;
	for(int i=0; i < 256 ;i++)
		sum = sum + i*histogram[i];
	lli wB = 0;	//Cumulative Frequency (till intensity value = i)
	lli wF = 0; //Total - Cumulative Frequency( till intensity value = i)
	lli sumB = 0; //Cumulative Weighted Frequency
	lli mB, mF, max = 0,between = 0;
	int threshold1 = 0, threshold2 = 0;
	for(int i=0; i < 256 ;i++)
	{
		wB += histogram[i];
		if(wB == 0)
			continue;
		wF = total - wB;
		if(wF == 0)
			break; 	//Break if wB == total
		sumB += i * histogram[i];
		mB = sumB / wB;
		mF = (sum - sumB) / wF;
		between = wB * wF * (mB - mF) * (mB - mF);
		if(between >= max)
		{
			threshold1 = i;
			if(between > max)
				threshold2 = i;
			max = between;
		}
	}
	return ((threshold1 + threshold2) / 2);
}

Mat binary(Mat image,int threshold)
{
	Mat result(image.size(),CV_8UC1);
	for (int i = 0; i < image.rows; ++i)
	{
		for (int j = 0; j < image.cols; ++j)
		{
			if(image.at<uchar>(i,j)>threshold)
				result.at<uchar>(i,j)=255;
			else
				result.at<uchar>(i,j)=0;
		}
	}
	return result;
}

int main(int argc, char const *argv[])
{
	Mat image;
	string fname;
	cout << "Enter File Name:";
	cin >> fname;
	image = imread(fname,CV_LOAD_IMAGE_GRAYSCALE);
	lli freq[256]={0}; //Initialize Frequency Array to 0
	lli N = image.rows*image.cols; //Resolution of Image
	for(int i=0; i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			freq[image.at<uchar>(i,j)]++;	//Increase Frequency Counter
		}
	}
	cout << "Threshold is: " << otsu(freq,N);
	namedWindow("Otsu Binarization",WINDOW_NORMAL);
	namedWindow("Original",WINDOW_NORMAL);
	imshow("Otsu Binarization",binary(image,otsu(freq,N)));
	imshow("Original",image);
	waitKey(0);
	return 0;
}