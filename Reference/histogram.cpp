#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//Scale Down Factor
#define SCL_FACTOR 10

using namespace std;
using namespace cv;

Mat makebinary(Mat image, int threshold)
{
	Mat result(image.size(),CV_8UC1);
	for(int i = 0 ; i < image.rows ; i++)
	{
		for(int j = 0 ; j < image.cols ; j++)
		{
			if(image.at<uchar>(i,j)>threshold)
				result.at<uchar>(i,j)=255;	//Make pixel white
			else
				result.at<uchar>(i,j)=0;	//Make pixel black
		}
	}
	return result;
}

int main()
{
	Mat image, binary;
	string fname;
	cout << "Enter Name of file:";
	cin >> fname;
	image = imread(fname,CV_LOAD_IMAGE_GRAYSCALE); //Load image in grayscale 
	Mat histogram((int)((image.rows*image.cols)/SCL_FACTOR),256,CV_8UC1,Scalar(0)); //Declare an object Histogram of size [(Total Number of Pixels * Scaling Factor) * 256]
	int freq[256]={0}; //Initialize Frequency Array to 0
	for(int i=0; i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			freq[image.at<uchar>(i,j)]++;	//Increase Frequency Counter
		}
	}
	//Print an inverted Histogram
	for(int j = 0; j < 256 ; j++)
	{
		for(int i = 0 ; i < (freq[j]/SCL_FACTOR) ; i++)
		{
			histogram.at<uchar>(i,j)=255;
		}
	}
	//Compute the threshold from the histogram
	long long int cum_freq=0;
	int thresh;
	for(int i = 0; i < 256 ; i++)
		{
			cum_freq +=freq[i];
			if(cum_freq>((image.rows*image.cols)/2))
			{
				thresh = i;
				break;
			}
		}	
	binary = makebinary(image,thresh);	//Make binary image from computed threshold
	//Print the original image in Grayscale, the Histogram and the resulting Binary
	namedWindow("Normal",CV_WINDOW_AUTOSIZE);
	imshow("Normal",image);
	namedWindow("Histogram",CV_WINDOW_AUTOSIZE);
	imshow("Histogram",histogram);
	namedWindow("Binary",CV_WINDOW_AUTOSIZE);
	imshow("Binary",binary);
	waitKey(0);
	return 0;
}
