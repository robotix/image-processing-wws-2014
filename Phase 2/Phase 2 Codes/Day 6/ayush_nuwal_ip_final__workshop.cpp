#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include<iostream>
#include<queue>
#include<algorithm>
#include<math.h>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
#define pie 3.14
/*Mat makebinary(Mat image1, int x)
{
	Mat image2(image1.rows,image1.cols,CV_8UC1);
	int i, j, t;
	t = x;
	for (i = 0; i < image1.rows; i++)
	{
		for (j = 0; j < image1.cols; j++)
		{
			if (image1.at<uchar>(i, j) > t)
			{
				image2.at<uchar>(i, j) = 255;
			}
			else
				image2.at<uchar>(i, j) = 0;
		}
	}
	return (image2);
}*/
/*
Mat histogram(Mat image)
{
	int i, j, k;
	int a[256] = { 0 };
	for (k = 0; k < 256; k++)
	{
		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				if (image.at<uchar>(i, j) == k)
					a[k] = a[k] + 1;
			}
		}
	}
	Mat image2(((image.rows*image.cols) / 100), 256, CV_8UC1, Scalar(0));
	for (j = 0; j < 256; j++)
	{
		for (i = 0; i < a[j] / 100; i++)
		{
			image2.at<uchar>(i, j) = 255;
		}
	}
	return(image2);
}*/
/*
Mat edgewhite(Mat image2)
{
	int i, j, l, m, max, min,t=100;
	Mat image(image2.rows, image2.cols, CV_8UC1, Scalar(255));
	for (l = 1; l < image2.rows-1; l++)
	{
		for (m = 1; m < image2.cols-1; m++)
		{
			max = image2.at<uchar>(l - 1,m - 1);
			min = image2.at<uchar>(l - 1,m - 1);
			for (i = l - 1; i <= l + 1; i++)
			{
				for (j = m - 1; j <= m + 1; j++)
				{
					if (image2.at<uchar>(i,j)> max)
						max = image2.at<uchar>(i,j);
					if (image2.at<uchar>(i,j) < min)
					min = image2.at<uchar>(i,j);
					
				}
			}
			if (max - min > t)
				image.at<uchar>(l, m) = 0;
			else
				image.at<uchar>(l, m) = 255;
		}
	}
	return(image);
}
*/ /*
int median(Mat image1, int i, int j)
{
	int a[9], n, k, l;
	n = 0;
	for (k = -1; k <= 1; k++)
	for (l = -1; l <= 1; l++)
		a[n++] = image1.at<uchar>(i + k, j + l);
	sort(a, a + 9);
	return a[4];
}*/
/*
Mat edgedetectionbygradient(Mat image2)
{
	int i, j,l,m,dx,dy,s;
	Mat newimage(image2.rows, image2.cols, CV_8UC1);
	for (l = 1; l < image2.rows - 1; l++)
	{
		for (m = 1; m < image2.cols-1; m++)
		{
		
					dx = image2.at<uchar>(l - 1, m + 1) - image2.at<uchar>(l - 1, m - 1) + image2.at<uchar>(l, m+1) - image2.at<uchar>(l, m-1) + image2.at<uchar>(l + 1, m + 1) - image2.at<uchar>(l + 1, m - 1);
					dy = image2.at<uchar>(l + 1, m - 1) - image2.at<uchar>(l - 1, m - 1) + image2.at<uchar>(l + 1, m) - image2.at<uchar>(l - 1, m) + image2.at<uchar>(l + 1, m + 1) - image2.at<uchar>(l - 1, m + 1);
			s = (int)sqrt(dx*dx + dy*dy);
					//s = (int)sqrt(dx);
			if (s> 255)
				s = 255;
			newimage.at<uchar>(l, m) = s;
		}
	}
	return(newimage);
}*/
/*
Mat noisedetectiondilation(Mat image2)
{
	int i, j, l, m,same,countB=0,countW=0;
	Mat image = edgewhite(image2);
	Mat imageD(image.rows, image.cols, CV_8UC1);
	for (l = 1; l < image.rows-1; l++)
	{
		for (m = 1; m < image.cols - 1; m++)
		{
			countB = 0;
			countW = 0;
			for (i = l - 1; i <= l + 1; i++)
			{
				for (j = m - 1; j <= m + 1; j++)
				{
					if (image.at<uchar>(i, j) == 0)
						countB++;
					else
						countW++;
				}
			}
			if (countB > countW)
				imageD.at<uchar>(l, m) = 0;
			else
				imageD.at<uchar>(l, m) = 255;
		}

	}
	return(imageD);
}*/
/*
Mat noisedetectionerosion(Mat image2)
{
	int i, j, l, m, same, countB = 0, countW = 0;
	Mat image = edgewhite(image2);
	Mat imageD(image.rows, image.cols, CV_8UC1);
	for (l = 1; l < image.rows - 1; l++)
	{
		for (m = 1; m < image.cols - 1; m++)
		{
			countB = 0;
			countW = 0;
			for (i = l - 1; i <= l + 1; i++)
			{
				for (j = m - 1; j <= m + 1; j++)
				{
					if (image.at<uchar>(i, j) == 0)
						countB++;
					else
						countW++;
				}
			}
			if (countB > countW )
				if (countW==0) imageD.at<uchar>(l, m) = 0;
				else imageD.at<uchar>(l, m) = 255;
			else{
				if (countB == 0) imageD.at<uchar>(l, m) = 255;
				else
					imageD.at<uchar>(l, m) = 0;
			}
		}

	}
	return(imageD);
}*/
/*
Mat meanfilter(Mat image2)
{
	int i, j, l, m,sum,s;
	Mat image(image2.rows, image2.cols, CV_8UC1);
	for (l = 1; l < image2.rows-1; l++)
	{
		for (m = 1; m < image2.cols - 1; m++)
		{
			sum = 0;
			for (i = l - 1; i < l + 1; i++)
			{
				for (j = m - 1; j < m + 1; j++)
				{
					sum = sum + image2.at<uchar>(i, j);
				}
			}
			s = sum / 9;
			image.at<uchar>(l, m) = s;
		}
	}
	return(image);
}*/
/*
Mat weightedmeanfilter(Mat image2)
{
	int l, m, i, j, sum = 0, s;
	Mat image(image2.rows, image2.cols, CV_8UC1);
	for (l = 1; l < image2.rows - 1; l++)
	{
		for (m = 1; m < image2.cols - 1; m++)
		{
			sum = 0.06*(image2.at<uchar>(l - 1, m - 1) + image2.at<uchar>(l - 1, m + 1) + image2.at<uchar>(l + 1, m - 1) + image2.at<uchar>(l + 1, m + 1)) + 0.098*(image2.at<uchar>(l - 1, m) + image2.at<uchar>(l, m - 1) + image2.at<uchar>(l + 1, m) + image2.at<uchar>(l, m + 1)) + 0.162*(image2.at<uchar>(l, m));
			image.at<uchar>(l, m) = sum;
		} sum = 0;
	}
	return(image);
}*/
/*
Mat detectcolor(Mat image1, int h, int tol, int l, int tol1, int s, int tol2)
{
	int i, j, max, min;
	Mat image(image1.rows, image1.cols, CV_8UC1);
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		if (abs(image1.at<Vec3b>(i, j)[0] - h) < tol*h / 100 && abs(image1.at<Vec3b>(i, j)[1] - l) < tol1*l / 100 && abs(image1.at<Vec3b>(i, j)[2] - l) < tol2*s / 100)
			image.at<uchar>(i, j) = 255;
		else
			image.at<uchar>(i, j) = 0;
	}
	return image;
}*/
/*
void detectfig(Mat image1, int **A, int i, int j, int count)
{
	int a, b;
	queue<Point> q;
	Point p, p1;
	p.x = i;
	p.y = j;
	A[i][j] = count;

	do{
		for (a = -1; a <= 1; a++)
		for (b = -1; b <= 1; b++)
		{
			if (p.x + a<image1.rows&&p.x + a>0 && p.y + a<image1.cols&&p.x + a>0)
			if (image1.at<uchar>(p.x + a, p.y + b) == 255 && A[p.x + a][p.y + b] == 0)
			{
				p1.x = p.x + a;
				p1.y = p.y + b;
				A[p.x + a][p.y + b] = count;
				q.push(p1);
			}
		}
		p = q.front();
		q.pop();
	} while (q.empty() != 1);
}*/
/*
void BFS(Mat paintimage, int **a, int l, int m, int count)
{
	int i, j;
	queue<Point> q;
	Point p, p1;
	p.x = l;
	p.y = m;
	do{
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				if (paintimage.at<uchar>(p.x + i, p.y + j) == 255 && a[p.x + i][p.y + j] == -1)
				{
					a[p.x + i][p.y + j] = count;
					p1.x = p.x + i;
					p1.y = p.y + j;
					q.push(p1);
				}
			}
		}
		p = q.front();
		q.pop();
	} while (q.empty()!=1);
}*/
/*
Mat blobimage(Mat image1, int **a)
{
	int i, j, count = 1;
	Mat image(image1.rows, image1.cols, CV_8UC1, Scalar (255));
	for (i = 0; i < image1.rows; i++)
	{
	for (j = 0; j < image1.cols; j++)
	{
		if (a[i][j] == -1)
			image.at<uchar>(i, j) = 0;
		else
			image.at<uchar>(i, j) = 255 / a[i][j];
	}
	count++;
    }
	return image;
}*/
/*
void blobdetection(Mat image1, int **a)
{
	int i, j, count;
	count = 1;
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
		a[i][j] = 0;
	for (i = 0; i < image1.rows; i++)
	for (j = 0; j < image1.cols; j++)
	{
		if (image1.at<uchar>(i, j) == 255 && a[i][j] == 0)
		{
			detectfig(image1, a, i, j, count);
			count++;
		}
	}
}
*/
/*
Mat lineDetection(Mat image, int threshold){
	int **A, n, t, r_max;
	Mat detectedImage(image.rows,image.cols,CV_8UC1,Scalar(0));
	float rad;
	n = sqrt(image.rows*image.rows + image.cols*image.cols);
	r_max = 2 * n + 3;
	A = (int **)malloc(r_max*sizeof(int*));
	for (int i = 0; i<r_max; i++){
		A[i] = (int *)malloc((181)*sizeof(int));
	}
	for (int i = 0; i<r_max; i++){
		for (int j = 0; j<181; j++){
			A[i][j] = 0;
		}
	}
	for (int x = 0; x<image.cols; x++){
		for (int y = 0; y<image.rows; y++){
			if (image.at<uchar>(y, x) == 255){
				for (int k = 0; k<180; k++){
					rad = pie*(k - 90) / 180;
					t = x*cos(rad) + y*sin(rad);
					A[r_max / 2 + t][k]++;
				}
			}
		}
	}

	for (int i = 0; i<180; i++){
		for (int j = 0; j<r_max; j++){
			if (A[j][i]>threshold&&i != 90){
				for (int x = 0; x<image.cols; x++){
					rad = pie*(i - 90) / 180;
					int y = abs((j - r_max / 2 - (x*cos(rad)) / sin(rad)));
					if (x<detectedImage.cols && y<detectedImage.rows && image.at<uchar>(y, x) == 255)
						detectedImage.at<uchar>(y, x) = 255;
				}
			}
		}
	}
	return (detectedImage);
}*/

/*Mat linedetection(Mat paintlines)
{
	Mat machaya(paintlines.rows, paintlines.cols, CV_8UC1);
	int l, m, r_max, i, j, n, t, k;
	int **a;
	a = (int**)malloc(181*sizeof(int*));
	n = sqrt(paintlines.rows*paintlines.rows + paintlines.cols*paintlines.cols);
	for (i = 0; i < paintlines.rows; i++){
		a[i] = (int*)malloc((n + 1)*sizeof(int));
	}
	for (i = 0; i < n + 1; i++)
	{

	}
	for (i = 0; i < paintlines.rows; i++)
	{
		for (j = 0; j < paintlines.cols; j++)
		{
			if (paintlines.at<uchar>(i, j) == 255)
			{
				for (int k = 0; k < 180; k++)
				{
					t = abs(i*sin(pie*k / 180) + j*cos(pie*k / 180))
						a[k][r_max/2+t]++;
				}
			}
		}
	}
	for (i = 0; i < 180; i++)
	{
		for (j = 0; j < r_max; j++)
		{
			for (k = 0; k < paintlines.rows;k++)
		}
	}
}*/
				







	

/*int main()
{
int i, j, k, x = 10,y=11,Threshold,l,m,count=1;*/
	/*Mat paintimage;
	paintimage = imread("C:\\Users\\Dell\\Desktop\\paint.png");
	Mat paintresult(paintimage.rows, paintimage.cols, CV_8UC1,Scalar(255));
	Mat linedetect = imread("C:\\Users\\Dell\\Desktop\\paintlines.png");
	namedWindow("My windowq", WINDOW_AUTOSIZE);
	int **a;
	a = (int**)malloc(paintimage.rows*sizeof(int*));
	for (i = 0; i < paintimage.rows; i++)
		a[i] = (int*)malloc(paintimage.cols*sizeof(int));
	for (i = 1; i < paintimage.rows; i++)
	{
		for (j = 1; j < paintimage.cols; j++)
			a[i][j] = -1;
	}
	for (l = 1; l < paintimage.rows - 1; l++)
	{
		for (m = 1; m < paintimage.cols - 1; m++)
		{
			if (paintimage.at<uchar>(l, m) == 255 && a[l][m] == -1)
			{
					 detectfig(paintimage, a,l,m,count);
						count++;
			}
		}
	}
	blobdetection(paintimage, a);
	paintresult = blobimage(paintimage, a);
	 imshow("My windowq", paintresult);
	 waitKey(0);
}
	Mat image1, imgra;
	int th = 100;
	char a = 51;
	//namedWindow("My window1", WINDOW_NORMAL);
	image1 = imread("C:\\Users\\Dell\\Desktop\\paintlines1.png", CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("My window1", image1);
	//Mat imgray;
	namedWindow("window", WINDOW_NORMAL);
	createTrackbar("threshold", "window", &th, 255);
	HoughLines(image1, sdsd, rho, theta, threshold);
	while (1){
		Mat imgra(image1.rows, image1.cols, CV_8UC1);
	    imgra = lineDetection(image1,th);
		imshow("window", imgra);
		char a = waitKey(33);
		if (a == 27) break;
	}
	return(0);
}


	//Mat image2;
	//image2 = imread("C:\\Users\\Dell\\Desktop\\800.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	//namedWindow("My window", WINDOW_AUTOSIZE);
	
	//Mat imageCanny(image2.rows, image2.cols, CV_8UC1);
	//namedWindow("My windowwmean", WINDOW_AUTOSIZE);
	//Mat image = noisedetectionerosion(image2);
	//Mat image4 = edgewhite(image2);
	//Mat image3 = noisedetectiondilation(image2);
	/*Mat imagewmean = weightedmeanfilter(image2);
	//namedWindow("My window123", WINDOW_AUTOSIZE);
	namedWindow("windowmean", WINDOW_AUTOSIZE);
	Mat imagemean = meanfilter(image2);
	namedWindow("My windowCanny", WINDOW_AUTOSIZE);
	createTrackbar("minThreshold", "My windowCanny", &x, 255);
	createTrackbar("maxThreshold", "My windowCanny", &y, 255);
	while (1)
	{
		//Mat bin = makebinary(image2, x);
		Canny(image2, imageCanny, x,y);
		imshow("My windowCanny", imageCanny);
		char a = waitKey(33);
		if (a == 27) break;
	}*/
		//Mat image3;
	//image = makebinary(image2, x);
	//int a[256] = { 0 };
	/*for (k = 0; k < 256; k++)
	{
		a[k] = 0;
	}*/
	/*
	for (k = 0; k < 256; k++)
	{
		for (i = 0; i < image2.rows; i++)
		{
			for (j = 0; j < image2.cols; j++)
			{
				if(image2.at<uchar>(i, j) == k)
				a[k] = a[k] + 1;
			}
		}
	}
	Mat image(((image2.rows*image2.cols)/100), 256, CV_8UC1,Scalar(0)); */
	/*for (i = 0; i < image1.rows; i++)
	{
		for (j = 0; j < image1.cols; j++)
		{
			image.at<uchar>(i, j) = 255;
		}
	}
*/
	/*for (k = 0; k < 256; k++)
	{
		a[k] = a[k] / 10;
	}
	for (j = 0; j< 256; j++)
		{
			for (i = 0; i < a[j]/100; i++)
			{
				image.at<uchar>(i, j) = 255;
			}
		} */
	/*namedWindow("My windowCanny", WINDOW_AUTOSIZE);
	createTrackbar("minThreshold", "My windowCanny", &x, 255);
	createTrackbar("maxThreshold", "My windowCanny", &y, 255);
	VideoCapture V(0);
	while (1)
	{
		Mat frame;
		V >> frame;
		Mat frame2(frame.rows, frame.cols, CV_8UC1);
		Mat frame3(frame.rows, frame.cols, CV_8UC1);
		for (i = 0; i < frame.rows; i++)
		{
			for (j = 0; j < frame.cols; j++)
			{
				frame2.at<uchar>(i, j) = (frame.at<Vec3b>(i, j)[0])*0.56 + (frame.at<Vec3b>(i, j)[1])*0.33 + (frame.at<Vec3b>(i, j)[2])*0.11;
			}
		}
		Canny(frame2, frame3, x, y);
		imshow("My windowCanny", frame3);
		//imshow("My windowgey", imageresult);
	char a=	waitKey(33);
	if (a == 27) break;
		 
	}*/
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
	VideoCapture v(0);
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





	/*namedWindow("My window", WINDOW_NORMAL);
	createTrackbar("Threshold", "My window", &x, 255);
	while (1)
	{
		for (i = 0; i < image2.rows; i++)
		{
			for (j = 0; j < image2.cols; j++)
			{
				if (image2.at<uchar>(i, j) > x)
				{
					image.at<uchar>(i, j) = 255;
				}
				else
					image.at<uchar>(i, j) = 0;
			}
		}
		Mat bin = makebinary(image2, x);
		imshow("My window", bin);
		char a = waitKey(33);
		if (a == 27) break;
	}
	//namedWindow("My window histogram", WINDOW_AUTOSIZE);
	//image3= histogram(image2);
	imshow("My windowgrey", imageresult);
	//imshow("My windowwmean", imagewmean);
	//imshow("My window123", image4);
	//imshow("My window",image);
	//imshow("My window histogram", image3);
	//imshow("windowmean", imagemean);
	waitKey(0);
	return 0;*/