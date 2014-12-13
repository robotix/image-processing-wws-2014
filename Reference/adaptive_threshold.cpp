#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat adaptive_threshold(Mat image)
{
	Mat result(image.size(),image.type());
	for(int i = 0 ; i < image.rows ; i++)
	{
		for(int j = 0; j < image.cols ; j++)
		{
			int sum = 0 , avg = 0, t = 9;
			for(int m=i-1; m<=i+1;m++)
			{
				for(int n=j-1;n<=j+1;n++)
				{
					if(m < 0 || n < 0 || m > image.rows - 1 || n > image.cols - 1)
					{
						t--;
						continue;
					}
					sum += image.at<uchar>(m,n);
				}
			}
			avg = sum / t;
			if(image.at<uchar>(i,j)>avg)
				result.at<uchar>(i,j)=255;
			else
				result.at<uchar>(i,j)=0;
		}
	}
	return result;
}

int main()
{
	Mat image, binary;
	string fname;
	cout << "Enter name of file:";
	cin >> fname;
	image = imread(fname,CV_LOAD_IMAGE_GRAYSCALE);
	binary = adaptive_threshold(image);
	namedWindow("Original",WINDOW_AUTOSIZE);
	imshow("Original",image);
	namedWindow("Binary",WINDOW_AUTOSIZE);
	imshow("Binary",binary);
	waitKey(0);
	return 0;
}