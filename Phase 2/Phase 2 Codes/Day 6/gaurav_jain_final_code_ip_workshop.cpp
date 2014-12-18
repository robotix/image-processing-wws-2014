#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <queue>
#define pi 3.142

using namespace std;
using namespace cv;




void gray_scale(Mat image ,Mat image2)
{
	int i,j,l,b;
	b=image.cols;
	l=image.rows;
	
	for(i=0;i<l;i++)
	{	
		for(j=0;j<b;j++)
		{
			
			image2.at<uchar>(i,j)=0.56*image.at<Vec3b>(i,j)[0]+0.33*image.at<Vec3b>(i,j)[1]+0.11*image.at<Vec3b>(i,j)[2];
		}
	}
}


int main()
{
	Mat image;
	int lower=48,upper=200,u,l;
	VideoCapture v(1);
		namedWindow("Vedio_Capture",CV_WINDOW_AUTOSIZE);
		createTrackbar("Main_lower","Vedio_Capture",&lower,100);
		createTrackbar("Main_upper","Vedio_Capture",&upper,200);
	//	createTrackbar("ed_lower","Vedio_Capture",&l,100);
	//	createTrackbar("ed_upper","Vedio_Capture",&u,200);
	while(1)
	{
		Mat frame;
		v>>frame;
		Mat image2(frame.rows,frame.cols,CV_8UC1,Scalar(0)),cannyimg(frame.rows,frame.cols,CV_8UC1),halfimage(frame.rows,frame.cols,CV_8UC1);
		Mat	nr(frame.rows,frame.cols,CV_8UC1);
	    vector<Vec2f> lines;
	    gray_scale(frame,image2);
		Canny(image2,cannyimg,lower,upper);
		//Canny(cannyimg,nr,l,u);
		
		
		for(int i=0;i<cannyimg.rows/2;i++)
			for(int j=0;j<cannyimg.cols;j++)
					halfimage.at<uchar>(i,j)=0;

		for(int i=cannyimg.rows/2;i<cannyimg.rows ;i++)
			for(int j=0;j<cannyimg.cols;j++)
					halfimage.at<uchar>(i,j)=cannyimg.at<uchar>(i,j);

		HoughLines(halfimage, lines, 2, CV_PI/180, 150, 0, 0 );
		//cout<<lines.size() << "\n";

		


		Mat nlines(frame.rows,frame.cols,CV_8UC3,Scalar(0,0,0));

		double sum_of_theta=0;
		int nolines=0;

		for( size_t i = 0; i < lines.size(); i++ )
		{
		  
			nolines++;
			sum_of_theta+=lines[i][1];
		  float rho = lines[i][0], theta = lines[i][1];
		  Point pt1, pt2;
		  double a = cos(theta), b = sin(theta);
		  double x0 = a*rho, y0 = b*rho;
		  pt1.x = cvRound(x0 + 1000*(-b));
		  pt1.y = cvRound(y0 + 1000*(a));
		  pt2.x = cvRound(x0 - 1000*(-b));
		  pt2.y = cvRound(y0 - 1000*(a));
		  line( nlines, pt1, pt2, Scalar(255,255,255), 3, CV_AA);
		
		}
		if(nolines==0)
			nolines=1;
		double value=sum_of_theta/nolines;
		if(value/CV_PI*180>100)
			cout<< "a" ;
		if(value/CV_PI*180<80)
			cout<< "d";
		else
			cout<< "w";
		imshow("Vedio_Capture",nlines);
		char k=waitKey(33);
		if(k==27)
		break;
		

	}
}