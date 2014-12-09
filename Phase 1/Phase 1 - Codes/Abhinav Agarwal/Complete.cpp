
/**Abhinav Agarwal 14EE10001*/

///////////////////HEADER FILES///////////////////
#include "stdafx.h"
#include <iostream>
#include <vector>
//#include<string> //#include<cmath> //#include<Windows.h>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\highgui\highgui_c.h"
#include "opencv2\opencv.hpp"
//#include <tcpxcv.h>
#include <Windows.h>
#include <queue>
using namespace std; using namespace cv;
#define N 200 //#define t 255/2
//////////////////////PROTOTYPES//////////////////////
Mat hist_gray(const Mat); Mat adapt_thres(const Mat); Mat gray(const Mat image);
Mat bgr2bin(const Mat image,int); Mat edgeDetect(const Mat image,int);
Mat noiseReduction(const Mat image, int block, int flag); Mat CannyEdge(const Mat image);
Mat SobelEdge(const Mat src); Mat Redcolordetect(const Mat image, int low, int high);
void Video(); void RedcolordetectT(const Mat image, int low, int high);
Mat RGBcolorshow(); Mat rgb2hsv(const Mat img_rgb); Mat edgeDetectionMask(const Mat image);
Mat blobDet(Mat image); void BFS(int x, int y); void blobDet2(Mat image); Mat HougesT(const Mat image);
void CallBackFunc(int event, int, int, int, void*); void rgbonclick(); void shapeDetect(const Mat image);

int thres;
bool visit[N][N];
int a[N][N], b[N][N], counter = 1;
//#define blob_detect_print
typedef struct {
	int x;
	int y;
}point;

Mat image;
int main()
{
	/*Mat*/ image= imread("G:\\blob4.jpg", CV_LOAD_IMAGE_COLOR);
	if (!image.data){
		cout << "Error reading file\n"; getchar();	exit(0);
	}
	namedWindow("original", CV_WINDOW_AUTOSIZE);
	imshow("original", image);
	int thres = 30;

//	shapeDetect(gray(image));
	//namedWindow("win1", CV_WINDOW_AUTOSIZE);
	/*namedWindow("win2", CV_WINDOW_AUTOSIZE);
	namedWindow("win3", CV_WINDOW_AUTOSIZE);*/
	//Mat image1 = Redcolordetect(image, 100, 150);
	//Mat image2 = bgr2bin(image, 50);
	//HougesT(image2);
	blobDet2(bgr2bin(image, 50)); /*BFS*/ /*pass only small images*/
	//imshow("win1", image2);
	//rgbonclick();
	//	blobDet(image2);
	//	RGBcolorshow();
	//Redcolordetect(image, 100, 150);
	//	Video();
	//	SobelEdge(image);
	/*	CannyEdge(gray(image));*/
	//	Mat temp = noiseReduction(image, 3, 0);
	//	edgeDetect(image,120);
	//	hist_gray(temp);
	//	adapt_thres(image);
	//	gray(image);
	//	bgr2bin(image);
	waitKey(0);
}


void shapeDetect(const Mat image)
{
	Mat O, I(image.rows, image.cols,CV_8UC1, Scalar(0));
	Canny(image,O,50,155,3);
	
	vector<vector<Point>> contour;
	findContours(O, contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	int i;
	vector<Point> approx, a;
	for (i = 0; i < contour.size(); i++)
	{
		approxPolyDP(contour[i], approx, arcLength(contour[i], true)*0.02, true);
		cout << approx.size() << "\n";
		if (approx.size() == 4  )
		{
			for (int j = 0; j < contour[i].size(); j++)
			{
				I.at<uchar>(contour[i][j].y, contour[i][j].x)=255;
			}
		}
	}
	/*GET X,Y*/
	/*
	int low;
	int k=0;
	int a[10]={4,3,8};
	for(j=0;j<contour[
	*/

	namedWindow("circle", WINDOW_AUTOSIZE);
	imshow("circle",I);
	waitKey(0);
}
void rgbonclick()
{
	namedWindow("rgb detect", CV_WINDOW_AUTOSIZE);
	imshow("rgb detect", image);

	setMouseCallback("rgb detect", CallBackFunc, NULL);	
}
void CallBackFunc(int event, int y, int x, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
 	{
		cout << "(" << x << "," << y << ") " << (int)image.at<Vec3b>(x, y)[0] << " " << (int)image.at<Vec3b>(x, y)[1] << " " << (int)image.at<Vec3b>(x, y)[2] << endl;
	}
}
Mat HougesT(const Mat image1)
{
	Mat image = image1.clone();
	Mat image2(image.rows,image.cols,CV_8UC3,Scalar(255,255,255));
	Canny(image, image2, 50, 200, 3);
	//cvtColor(image1, image1, CV_GRAY2BGR);
	vector<Vec2f> lines;
	HoughLines(image2, lines, 1, CV_PI / 180, 200, 50,10);
	namedWindow("detected lines", CV_WINDOW_AUTOSIZE);
//	createTrackbar("thres", );
	for (int i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(image2, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
	imshow("detected lines", image2);
	waitKey(0);
	return image1;
}
void blobDet2(Mat image)
{
	int n = image.rows, m = image.cols; int i, j, k, temp1, temp2, temp3;
	for (i = 0; i < N; i++)	for (j = 0; j < N; j++) visit[i][j] = false;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			b[i][j] = 0;
			if (image.at<uchar>(i, j) == 0) a[i][j] = 0;
			else a[i][j] = 1;
			//cout << a[i][j] << " ";
		}
		//cout << endl;
	}
//	system("pause");
	for (i = 1; i < n-1; i++)
	{
		for (j = 1; j < m-1; j++)
		{
			if (a[i][j] == 0 || visit[i][j] == true) continue;
			else BFS(i, j);
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << b[i][j] ;
		}
		cout << endl;
	}
}
void BFS(int x,int y)
{
	int i, j, k, l, c, temp1, temp2;
	queue <point> q;
	const int qmax = 200;
	point p;/*[qmax];*/
	point S,S1; 
	S.x = x; S.y = y;
	q.push(S);
	b[x][y] = counter;
	//k = 1;
//	cout << x << " " << y << endl; system("pause");
	while (!q.empty())
	{
//	 	cout << "Entered with " << counter << endl;
		S1 = q.front();
		q.pop();
		visit[S1.x][S1.y] = true;
//		int counting = 0;
		for (l = -1; l <= 1; l++)
		{
			for (c = -1; c <= 1; c++)
			{
				if (a[S1.x + l][S1.y + c] == 1 && visit[S1.x + l][S1.y + c] == false)
				{
					
//					cout << "Enter in if "<<counting++<<endl;
					p.x = S1.x + l; p.y = S1.y + c;
					q.push(p);
					visit[S1.x + l][S1.y + c] = true;
					b[S1.x + l][S1.y + c] = counter;
				}
			}
		}
	}
	counter++; 

}
Mat blobDet(Mat image) /*only pass mask to it*/
{
	int a[N][N], b[N][N];
	int n = image.rows, m = image.cols; int i, j, k, temp1, temp2, temp3;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			b[i][j] = 0;
			if (image.at<uchar>(i, j) == 0) a[i][j] = 0;
			else a[i][j] = 1;
			/*cout << a[i][j] << " ";*/
		}
		/*cout << endl;*/
	}
	////////////CREATE AND INITIALIZE ARRRAY///////////////////
	int ctr = 1, temp = 0;
	////////////// LOOP 1 ////////////////
	for (i = 1; i < n; i++)
	{
		for (j = 1; j<m; j++)
		{
			if (a[i][j] == 0) continue;
			else if (a[i - 1][j] + a[i - 1][j - 1] + a[i][j - 1] == 0) { b[i][j] = ctr++; continue; }
			else
			{
				int arr[3] = { 999, 999, 999 }; ///either do this or re-initialize arr each time!
				if (b[i - 1][j] != 0)arr[0] = b[i - 1][j]; if (b[i - 1][j - 1] != 0)arr[1] = b[i - 1][j - 1]; if (b[i][j - 1] != 0)arr[2] = b[i][j - 1];
				temp = (arr[0]<arr[1] ? arr[0] : arr[1]);
				temp = (temp<arr[2] ? temp : arr[2]); ////NOW temp is non zero min
				b[i][j] = temp;

			}
		}
	}
	cout << "After loop 1\n";
	//cout<<"\n\n\n";
#ifdef blob_detect_print
	for (i = 0; i < n; i++)
	{
		for (j = 0; j<m; j++)
			cout << b[i][j] << " ";
		cout << endl;
	}
	//////////////LOOP 2 ////////////////
#endif
	for (i = n - 2; i >= 0; i--)
	{
		for (j = m - 2; j >= 0; j--)
		{
			if (a[i][j] == 0) continue;
			else
			{
				int arr[3] = { 999, 999, 999 }; ///either do this or re-initialize arr each time!
				if (b[i + 1][j] != 0)arr[0] = b[i + 1][j]; if (b[i + 1][j + 1] != 0)arr[1] = b[i + 1][j + 1]; if (b[i][j + 1] != 0)arr[2] = b[i][j + 1];
				temp = (arr[0]<arr[1] ? arr[0] : arr[1]);
				temp = (temp<arr[2] ? temp : arr[2]);
				temp = (temp<b[i][j] ? temp : b[i][j]); ////NOW temp is non zero min
				b[i][j] = temp;
			}

		}
	}
	////////////// LOOP 2 ////////////////
#ifdef blob_detect_print

	cout << "\nAlmost Done\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j<m; j++)
			cout << b[i][j] << " ";
		cout << endl;
	}
#endif
	int l, c, flag = 0; //to make kernel
	////////////////FINAL PASS//////////////
	int VA[40];
	for (i = 0; i<40; i++) VA[i] = 0;

	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			if (b[i][j] == 0) continue;
			for (k = 0, flag = 0; VA[k] != 0; k++)
			{
				if (b[i][j] == VA[k]) flag = 1;
			}
			//cout<<"flag"<<flag;
			if (flag == 0)
			{
				VA[k] = b[i][j];
			}
			for (k = 0; VA[k] != 0; k++)
			{
				if (VA[k] == b[i][j]) { b[i][j] = k + 1; /*cout<<"tt";*/ }
			}
		}
	}
	cout << "\n Done\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j<m; j++)
			cout << b[i][j] << " ";
		cout << endl;
	}



	return image;
}
Mat edgeDetectionMask(const Mat image) ////////input mask only /////////////
{
	Mat image1 = image.clone();
	int i, j, k,l,c,min,max;
	for (i = 2; i < image.rows - 2; i++)
	{
		for (j = 2; j < image.cols - 2; j++)
		{
			max = min = image.at<uchar>(i, j);
			for (int l = i - 1; l < i + 1; l++)
			{
				for (int c = j - 1; c < j + 1; c++)
				{
					if (image.at<uchar>(l, c) > max) max = image.at<uchar>(l, c);
					if (image.at<uchar>(l, c) < min) min = image.at<uchar>(l, c);
				}
				if ((max - min>thres))
					image1.at<uchar>(i, j) = 0;
				else
					image1.at<uchar>(i, j) = 255;
			}
		}
	}
	namedWindow("edgeDetectionMask", CV_WINDOW_AUTOSIZE);
	imshow("edgeDetectionMask", image1);
	waitKey(0);
	return image1;
}
Mat rgb2hsv(const Mat img_rgb)
{
	Mat img_hsv;
	cvtColor(img_rgb, img_hsv, CV_RGB2HSV);
	return img_hsv;
}
Mat RGBcolorshow()
{
	int r=0, g=0, b=0;
	namedWindow("RGB COLOR SELECTOR", CV_WINDOW_AUTOSIZE);
	createTrackbar("Red", "RGB COLOR SELECTOR", &r, 255);
	createTrackbar("Blue", "RGB COLOR SELECTOR", &b, 255);
	createTrackbar("Green", "RGB COLOR SELECTOR", &g, 255);
	Mat image(400, 400, CV_8UC3,Scalar(0,0,0));
	while (1)
	{
		for (int i = 0; i < 400; i++)
		{
			for (int j = 0; j < 400; j++)
			{
				image.at<Vec3b>(i, j)[0] = b; image.at<Vec3b>(i, j)[1] = g; image.at<Vec3b>(i, j)[2] = r;
			}
		}
		imshow("RGB COLOR SELECTOR", image);
		if (waitKey(30) >= 27) return image;
	}
	return image;
}
Mat Redcolordetect(const Mat image, int t2/****/, int t1/***/)
{
	Mat image1(image.rows, image.cols, CV_8UC1);
	int i, j, red, blue, green;
	//namedWindow("RedColorDetect", CV_WINDOW_AUTOSIZE);
	/*createTrackbar("t1", "RedColorDetect", &t1, 255);
	createTrackbar("t2", "RedColorDetect", &t2, 255);
	while (1)
	{*/
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			red = image.at<Vec3b>(i, j)[2];
			blue = image.at<Vec3b>(i, j)[0];
			green = image.at<Vec3b>(i, j)[1];
			if ((red > t1) && (green < t2) && (blue < t2))
				image1.at<uchar>(i, j) = 0;
			else
				image1.at<uchar>(i, j) = 255;
		}
		//imshow("RedColorDetect", image1);
		/*		if (waitKey(30)>=27)exit(0);
			}*/
	}
		return image1;
	
}
void Video()
{
	int i,j;
	namedWindow("Video", CV_WINDOW_AUTOSIZE);
	VideoCapture vid("G:\\a.mp4");
	if (!vid.isOpened()) { cout << "\n\nCannot load video\n\n\n"; getchar(); exit(0); }
	Mat frame;
	//namedWindow("Video", CV_WINDOW_AUTOSIZE);
//	vid.set(CV_CAP_PROP_FPS, 10);
	int thres=100;
	createTrackbar("Threshold","Video",&thres,255);
	while (1)
	{
		vid >> frame; //vid >> frame; //waitKey(100);
		imshow("Video", SobelEdge(frame));
		if (waitKey(30) >= 10) exit(0);
	}
}
Mat SobelEdge(const Mat src)
{
	Mat  src_gray;	Mat grad;
	char* window_name = "Sobel Edge Detection";
	int scale = 1;	int delta = 0;	int ddepth = CV_16S;
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	/// Gradient X
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	/// Gradient Y
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	grad = Scalar::all(255) - grad;
//	imshow(window_name, grad);
	return grad;
}
Mat CannyEdge(const Mat src)
{
	Mat src_gray;	Mat dst, detected_edges;
	int edgeThresh = 1;	int lowThreshold=30;	int const max_lowThreshold = 100;
	int ratio = 3;	int kernel_size = 3;	char* window_name = "Edge Map"; int i, j;
	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, CV_BGR2GRAY);
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	lowThreshold = 60;
		blur(src_gray, detected_edges, Size(3, 3));  /////// SMOOTH /////////
		Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
		dst = Scalar::all(0);
		src.copyTo(dst, detected_edges);
		//char ch = waitKey(30);
		//if (ch == '.')break;
		dst = Scalar::all(255) - dst;
	imshow(window_name, dst);

	return dst;
}
Mat noiseReduction(const Mat image, int block, int flag)/*flag=1=>go-ahead else convert to grayscale first*/
{
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j, k, temp, nwhite, nblack, l, c;
	if (flag == 1) image1 = image.clone();
	else  image1 = adapt_thres(image);
	const Mat image1_copy = image1.clone(); /////////////THIS COPY(IN BIN) WILL REMAIN UNCHANGED//////////////////
	//////////////////////NOW WE HAVE BIN IMAGE IN HAND////////////////////////
	for (i = 0; i < (image1.rows - block); i++)
	{
		for (j = 0; j < (image1.cols - block); j++)
		{
			for (l = i /*- block*/, nblack = 0, nwhite = 0; l < i + block; l++)
			{
				for (c = j/*-block*/; c < j + block; c++)
				{
					if (image1_copy.at<uchar>(l, c) == 0) nblack++;
					else nwhite++;
				}
			}
			if (nblack>nwhite) image1.at<uchar>(i, j) = 0;
			else image1.at<uchar>(i, j) = 255;
		}
	}
	namedWindow("NoiseReduce", CV_WINDOW_AUTOSIZE);
	imshow("NoiseReduce", image1);
	return image1;
}
Mat edgeDetect(const Mat image,int thres)
{
	int max, min;//,thres=29;
	Mat gray(image.rows, image.cols, CV_8UC1);  //the grayscale image matrix is initialized
	cvtColor(image, gray, CV_BGR2GRAY);
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j;
	namedWindow("edgeDetect", CV_WINDOW_AUTOSIZE);
	//createTrackbar("Trackbar", "edgeDetect", &thres, 200);	
	/*while (1)
	{*/
		for (i = 2; i < gray.rows - 2; i++)
		{
			for (j = 2; j < gray.cols - 2; j++)
			{
				max = min = gray.at<uchar>(i, j);
				for (int l = i - 1; l < i + 1; l++)
				{
					for (int c = j - 1; c < j + 1; c++)
					{
						if (gray.at<uchar>(l, c) > max) max = gray.at<uchar>(l, c);
						if (gray.at<uchar>(l, c) < min) min = gray.at<uchar>(l, c);
					}
					if ((max - min>thres))
						image1.at<uchar>(i, j) = 0;
					else
						image1.at<uchar>(i, j) = 255;
				}
			}
		/*}
		char ch = waitKey(30);
		if (ch == '.')exit(0);*/
		imshow("edgeDetect", image1);
	}

	return image1;

}
Mat hist_gray(const Mat image)
{
	int t = 225 / 2.0, avg = 0;
	int hist[256];
	int i, j;
	for (i = 0; i < 256; i++)hist[i] = 0;
	for (i = 0; i < image.rows-1; i++)
	{
		for (j = 0; j < image.cols-1; j++)
		{
			avg = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3.0;
			hist[avg]++;
			//cout << hist[avg] << "\n";
		}
	}
	//////////////////////////////FIND MAX AND NORMALIZE///////////////////////////////////
	int max = -1;
	for (i = 0; i < 255; i++)
	{
		if (hist[i]>max) max = hist[i];
	}
	int normalize_factor;
	if (max < 480) normalize_factor = 1;
	else normalize_factor = max / 400 + 1;
	cout<<max << "\n\n" << normalize_factor << "\n\n";
	//////////////////////////////FIND MAX AND NORMALIZE///////////////////////////////////
	Mat histo(500, 500, CV_8UC1, Scalar(255));
	for (i = 0; i < 256; i++)
	for (int k = 0; k<(hist[i]) / normalize_factor; k++)
		histo.at<uchar>(k, i) = 0;
	//	for (i = 0; i < 256; i++)cout << hist[i] << " ";
	/*namedWindow("histo_gray", CV_WINDOW_AUTOSIZE);
	imshow("histo_gray", histo);*/
	//waitKey(0);
	return histo;
}	  ///check
Mat adapt_thres(const Mat image)
{
	int avg;
	Mat gray(image.rows, image.cols, CV_8UC1);  //the grayscale image matrix is initialized
	cvtColor(image, gray, CV_BGR2GRAY);
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j, max = 0, min = 0;
	for (i = 2; i < gray.rows - 2; i++)
	{
		for (avg = 0, j = 2; j < gray.cols - 2; j++)
		{
			avg = 0;
			for (int l = i - 1; l < i + 1; l++)
			{
				for (int c = j - 1; c < j + 1; c++)
				{
					avg += gray.at<uchar>(l, c);
				}
			}
			avg /= 9;
			if (!(gray.at<uchar>(i, j)> 2.1*avg)){ image1.at<uchar>(i, j) = 0; }
			else { image1.at<uchar>(i, j) = 255; }
			avg = 0;
		}
	}
	namedWindow("adapt_threso", CV_WINDOW_AUTOSIZE);
	imshow("adapt_threso", image1);
	return image1;
}
Mat gray(const Mat image)
{
	float a = 1 / 3.0, b = 1 / 3.0, c = 1 / 3.0;
	//cout << "Working\n";
	//	namedWindow("new2", CV_WINDOW_AUTOSIZE);
	int avg;
	Mat image1(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			avg = (a*image.at<Vec3b>(i, j)[0] + b*image.at<Vec3b>(i, j)[1] + c*image.at<Vec3b>(i, j)[2]);
			image1.at<Vec3b>(i, j)[0] = avg; image1.at<Vec3b>(i, j)[1] = avg; image1.at<Vec3b>(i, j)[2] = avg;
		}
	}
	//namedWindow("GrayScale", CV_WINDOW_AUTOSIZE);
	//imshow("GrayScale", image1);
	//namedWindow("win", CV_WINDOW_AUTOSIZE);
	//imshow("win", image);
	return image1;
}
Mat bgr2bin(const Mat image,int t)
{
	float a = .33, b = .56, c = .1;
	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (!((a*image.at<Vec3b>(i, j)[0] + b*image.at<Vec3b>(i, j)[1] + c*image.at<Vec3b>(i, j)[2])  > t))
			{
				image1.at<uchar>(i, j) = 255;
			}
			else
			{
				image1.at<uchar>(i, j) = 0;
			}
		}
	}
	//namedWindow("bgr2bin", CV_WINDOW_AUTOSIZE);
	//imshow("bgr2bin", image1);
	//namedWindow(""win"", CV_WINDOW_AUTOSIZE);
	//imshow(""win"", image);
	return image1;
}
#ifdef gray

Mat hist_gray(const Mat image)
{
	int hist[256];
	int i, j, avg;
	for (i = 0; i < 256; i++)hist[i] = 0;
	{
		for (j = 0; j < image.cols - 1; j++)
		{
			avg = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3.0;
			hist[avg]++;
			//cout << hist[avg] << "\n";
		}
	}
}
#endif
///////////////////////////////CODING///////////////////////////////
#ifdef code
int fib(int n)
{
	int temp1, temp2;
	if (n < 2)return 1;
	if (n == 2) return 2;
	if (n % 2 == 0)
	{
		temp1 = fib(n / 2 + 1);
		temp2 = fib(n / 2);
		cout << "f(" << n / 2 + 1 << ") = " << temp1 << endl;
		return temp1*temp1 + temp2*temp2;
	}
	else
	{
		temp1 = fib((n - 1) / 2);
		temp2 = fib((n + 1) / 2);
		return 2 * temp1*temp2 + temp2*temp2;
	}

}
int main()
{
	cout << fib(6) << endl;
	getchar();
}
#endif


