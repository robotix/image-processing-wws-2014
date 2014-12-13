#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//Define ratios for Blue , Green , Red respectively
#define A 0.1140
#define B 0.5870
#define C 0.2989
//These are nearly perfect values of ratios for conversion of RGB to Grayscale. 
//However, you may use any other value of these ratios, just make sure that the resultant lies between 0 and 255

using namespace std;
using namespace cv;

int main()
{
	Mat image;
	string fname;
	cout << "Enter Name of file:";
	cin >> fname;
	image = imread(fname,CV_LOAD_IMAGE_COLOR); 
	Mat grayscale(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(int i=0; i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			grayscale.at<uchar>(i,j)=(A*image.at<Vec3b>(i,j)[0] + B*image.at<Vec3b>(i,j)[1] + C*image.at<Vec3b>(i,j)[2]);
		}
	}
	namedWindow("Normal",CV_WINDOW_AUTOSIZE);
	imshow("Normal",image);
	namedWindow("Grayscale",CV_WINDOW_AUTOSIZE);
	imshow("Grayscale",grayscale);
	waitKey(0);
	return 0;
}
