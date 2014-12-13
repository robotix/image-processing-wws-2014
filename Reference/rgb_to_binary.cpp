#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//Define Threshold here
#define THRESH 127

using namespace std;
using namespace cv;

int main()
{
	Mat rgbimage;
	string fname;
	cout << "Enter name of file:";
	cin >> fname;
	rgbimage = imread(fname,CV_LOAD_IMAGE_COLOR);
	Mat binary(rgbimage.size(),CV_8UC1); //Make another image with size same as RGB image but with a single channel only
	for(int i = 0 ; i < rgbimage.rows ; i++)
	{
		for(int j = 0 ; j < rgbimage.cols ; j++)
		{
			if(((rgbimage.at<Vec3b>(i,j)[0]+rgbimage.at<Vec3b>(i,j)[1]+rgbimage.at<Vec3b>(i,j)[2])/3)>THRESH)
				binary.at<uchar>(i,j)=255;	//Make pixel white
			else
				binary.at<uchar>(i,j)=0;	//Make pixel black
		}
	}
	namedWindow("Original",WINDOW_AUTOSIZE);
	imshow("Original",rgbimage);
	namedWindow("Binary",WINDOW_AUTOSIZE);
	imshow("Binary",binary);
	waitKey(0);
	return 0;
}