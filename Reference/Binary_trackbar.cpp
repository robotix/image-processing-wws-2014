#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
	Mat image;
	string fname;
	cout << "Enter name of file:";
	cin >> fname;
	image = imread(fname,CV_LOAD_IMAGE_COLOR);
	namedWindow("Original",WINDOW_AUTOSIZE);
	namedWindow("Binary",WINDOW_AUTOSIZE);
	int threshold = 10;
	createTrackbar("Threshold","Binary",&threshold,255);
	while(1)
	{
		Mat gray;
		cvtColor(image,gray,CV_BGR2GRAY);
		Mat binary=makebinary(gray,threshold);
		imshow("Original",image);
		imshow("Binary",binary);
		char a = waitKey(33);
		if(a==27) break;
	}
	return 0;
}