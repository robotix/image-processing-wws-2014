//Complete Edge Detection Module - Naive Edge Detection + Prewitt + Sobel + Canny
//Also shows Gradient images in X and Y directions respectively. 
#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define CAM_INDEX 0

using namespace std;
using namespace cv;

Mat Grayscale(Mat img)
{
	Mat grayscale(img.rows,img.cols,CV_8UC1,Scalar(0));
	for(int i=0; i<img.rows;i++)
	{
		for(int j=0;j<img.cols;j++)
		{
			grayscale.at<uchar>(i,j)=(0.114*img.at<Vec3b>(i,j)[0] + 0.587*img.at<Vec3b>(i,j)[1] + 0.2989*img.at<Vec3b>(i,j)[2]);
		}
	}
	return grayscale;
}

Mat NaiveEdge(Mat img,int Threshold)
{
	Mat result(img.size(),img.type());
	for (int i = 1; i < img.rows - 1; ++i)
	{
		for (int j = 1; j < img.cols - 1; ++j)
			{
				int max = 0 , min = 255;
				for (int m = i-1; m <=i+1; ++m)
				{
					for (int n = j-1; n <= j+1; ++n)
					{
						max = img.at<uchar>(m,n) > max ? img.at<uchar>(m,n) : max;
						min = img.at<uchar>(m,n) < min ? img.at<uchar>(m,n) : min;
					}
				}
				if(max-min > Threshold)
					result.at<uchar>(i,j) = 255;
				else
					result.at<uchar>(i,j) = 0;
			}	
	}
	return result;
}

Mat GradX(Mat img)
{
	Mat result(img.size(),img.type());
	for (int i = 1; i < img.rows - 1; ++i)
	{
		for (int j = 1; j < img.cols - 1; ++j)
			{
				result.at<uchar>(i,j) = img.at<uchar>(i-1,j+1) + img.at<uchar>(i,j+1) + img.at<uchar>(i+1,j+1) - img.at<uchar>(i-1,j-1) - img.at<uchar>(i,j-1) - img.at<uchar>(i+1,j-1);
			}	
	}
	return result;
}

Mat GradY(Mat img)
{
	Mat result(img.size(),img.type());
	for (int i = 1; i < img.rows - 1; ++i)
	{
		for (int j = 1; j < img.cols - 1; ++j)
			{
				result.at<uchar>(i,j) = img.at<uchar>(i+1,j+1) + img.at<uchar>(i+1,j) + img.at<uchar>(i+1,j-1) - img.at<uchar>(i-1,j-1) - img.at<uchar>(i-1,j) - img.at<uchar>(i-1,j+1);
			}	
	}
	return result;
}

Mat Prewitt(Mat img)
{
	Mat result(img.size(),img.type());
	for (int i = 1; i < img.rows - 1; ++i)
	{
		for (int j = 1; j < img.cols - 1; ++j)
			{
				char GradX = img.at<uchar>(i-1,j+1) + img.at<uchar>(i,j+1) + img.at<uchar>(i+1,j+1) - img.at<uchar>(i-1,j-1) - img.at<uchar>(i,j-1) - img.at<uchar>(i+1,j-1);
				char GradY = img.at<uchar>(i+1,j+1) + img.at<uchar>(i+1,j) + img.at<uchar>(i+1,j-1) - img.at<uchar>(i-1,j-1) - img.at<uchar>(i-1,j) - img.at<uchar>(i-1,j+1);
				result.at<uchar>(i,j) = (sqrt(GradX*GradX + GradY*GradY) < 255 ? sqrt(GradX*GradX + GradY*GradY) : 255);
			}	
	}
	return result;
}

Mat Sobel(Mat img)
{
	Mat result(img.size(),img.type());
	for (int i = 1; i < img.rows - 1; ++i)
	{
		for (int j = 1; j < img.cols - 1; ++j)
			{
				char GradX = img.at<uchar>(i-1,j+1) + 2 * img.at<uchar>(i,j+1) + img.at<uchar>(i+1,j+1) - img.at<uchar>(i-1,j-1) - 2 * img.at<uchar>(i,j-1) - img.at<uchar>(i+1,j-1);
				char GradY = img.at<uchar>(i+1,j+1) + 2 * img.at<uchar>(i+1,j) + img.at<uchar>(i+1,j-1) - img.at<uchar>(i-1,j-1) - 2 * img.at<uchar>(i-1,j) - img.at<uchar>(i-1,j+1);
				result.at<uchar>(i,j) = (sqrt(GradX*GradX + GradY*GradY) < 255 ? sqrt(GradX*GradX + GradY*GradY) : 255);
			}	
	}
	return result;
}

void MakeCanny(Mat img,int T1, int T2)
{
	Mat result;
	Canny(img,result,T1,T2);
	imshow("Canny",result);
}

int main()
{
	cout << "Select Capture Method:\n1.Image\n2.Video\n:";
	int choice;
	cin >> choice;
	VideoCapture Vid(CAM_INDEX);
	Mat image,CannyEdges;
	if(choice == 1)
	{
		string fname;
		cout << "Enter File Name:";
		cin >> fname;
		image = imread(fname,CV_LOAD_IMAGE_GRAYSCALE);
	}
	int T = 50, T1 = 10, T2 = 80;
	namedWindow("Original",WINDOW_NORMAL);
	namedWindow("Naive Edge",WINDOW_NORMAL);
	namedWindow("Gradient X",WINDOW_NORMAL);
	namedWindow("Gradient Y",WINDOW_NORMAL);
	namedWindow("Prewitt",WINDOW_NORMAL);
	namedWindow("Sobel",WINDOW_NORMAL);
	namedWindow("Canny",WINDOW_NORMAL);
	createTrackbar("Threshold","Naive Edge",&T,255);
	createTrackbar("Threshold 1","Canny",&T1,255);
	createTrackbar("Threshold 2","Canny",&T2,255);
	while(1)
	{
		if(choice==2)
		{
			Vid >> image;
			image = Grayscale(image);
		}
		imshow("Naive Edge",NaiveEdge(image,T));
		imshow("Prewitt",Prewitt(image));
		imshow("Sobel",Sobel(image));
		imshow("Gradient Y",GradY(image));
		imshow("Gradient X",GradX(image));
		imshow("Original",image);	
		MakeCanny(image,T1,T2);
		char a = waitKey(33);
		if(a==27)
			break;
	} 
	return 0;
}