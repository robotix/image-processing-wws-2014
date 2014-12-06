/**Abhinav Agarwal and Ishaan Sang  - BLOB DETECT BFS***/
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
#include<Windows.h>
#include<queue>
using namespace std; using namespace cv;
#define N 200
void BFS(int x,int y);
void blobDetBFS(Mat image);Mat bgr2bin(const Mat image,int t);
typedef struct {
	int x;
	int y;
}point;

int main()
{
	Mat image = imread("BLOB.jpg", CV_LOAD_IMAGE_COLOR);
	if (!image.data){
		cout << "Error reading file\n"; getchar();	exit(0);
	}
	namedWindow("original", CV_WINDOW_AUTOSIZE);
	imshow("original", image);
	Mat image2 = bgr2bin(image, 50);	/**Converting to binary**/
	//blobDet2(image2);

}

bool visit[N][N]; //GLOBAL VARS
int a[N][N], b[N][N],counter=1; //GLOBAL VARS

void blobDetBFS(Mat image)	/**PASS BINARY IMAGE ONLY**/
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

