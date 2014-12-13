#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
 
using namespace std;
using namespace cv;
 
int main()
{
	Mat image(200,300,CV_8UC3,Scalar(255,0,0));
	char win[] = "Striped Image"; //String with the name of the window
	for(int i=0; i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			if(i<image.rows/3)
				{
				image.at<Vec3b>(i,j)[1]=165;	//Orange
				image.at<Vec3b>(i,j)[2]=255;
				image.at<Vec3b>(i,j)[0]=0;
				}
			else if(i>=(2*image.rows)/3)
				{image.at<Vec3b>(i,j)[1]=255;	//Green
				image.at<Vec3b>(i,j)[2]=0;
				image.at<Vec3b>(i,j)[0]=0;
				}
			else
			{
				 image.at<Vec3b>(i,j)[2]=255;	//White
				 image.at<Vec3b>(i,j)[1]=255;
				 image.at<Vec3b>(i,j)[0]=255;
			}
		}
	}
	namedWindow(win,WINDOW_NORMAL);
	imshow(win,image);
	waitKey(0);
	return 0;
}