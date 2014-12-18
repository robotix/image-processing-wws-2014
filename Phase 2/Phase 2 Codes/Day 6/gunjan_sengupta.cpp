#include"stdafx.h"

#include<iostream>
#include<stdio.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>
#include<queue>
using namespace std;
using namespace cv;

Mat border(Mat img1)
{
	
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
			if ((max - min)>50) img2.at<uchar>(i, j) = 255;
		}
	}
	return(img2);
}

Mat border2(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max,x=0,y=0;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows-1) || (j == 0) || (j == img1.cols-1)) continue;
			x = 0; y = 0;
			for (int k = -1; k <= 1; k++)
			{
				x+= img1.at<uchar>(i + k, j + 1) - img1.at<uchar>(i + k, j - 1);
				y += img1.at<uchar>(i + 1, j + k) - img1.at<uchar>(i - 1, j + k);

			}
			img2.at<uchar>(i, j) = sqrt(x*x + y*y);
		}
	}
	return(img2);
}

Mat dilation(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
			img2.at<uchar>(i, j) =max;
		}
	}
	return(img2);
}
Mat erosion(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (img1.at<uchar>(i + k, l + j) > max) max = img1.at<uchar>(i + k, l + j);
					if (img1.at<uchar>(i + k, l + j) < min) min = img1.at<uchar>(i + k, l + j);
				}
			}
		img2.at<uchar>(i, j) =min;
		}
	}
	return(img2);
}
Mat noisemean(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, avg = 0;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			avg = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
	
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					avg += img1.at<uchar>(i + k, j + l);
				}
			}
			img2.at<uchar>(i, j) = avg / 9;
		}
	}
	return(img2);
}
int sort(int a[])
{
	int temp;
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	return 0;
}
Mat noisemedian(Mat img1)
{

	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, n=0,a[9];
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					a[n++] = img1.at<uchar>(i + k, j + l);
				}
			}
			sort(a);
			img2.at<uchar>(i, j) = a[4];
		}
	}
	return(img2);
}
Mat gausian(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int min, max, n = 0,sum;
	float a[9] = { 0.06, 0.098, 0.06, 0.098, 0.162, 0.098, 0.06, 0.098, 0.06 };
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = 0;
			sum = 0;
			if ((i == 0) || (i == img1.rows) || (j == 0) || (j == img1.cols)) continue;
			max = img1.at<uchar>(i - 1, j - 1);
			min = img1.at<uchar>(i - 1, j - 1);
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					sum += a[n++] * (img1.at<uchar>(i + k, j + l));
				}
			}
			img2.at<uchar>(i, j) = sum;
		}
	}
	return(img2);
}
Mat grey(Mat img1)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			img2.at<uchar>(i, j) = img1.at<Vec3b>(i, j)[0] * 0.55 + img1.at<Vec3b>(i, j)[1] * 0.33 + img1.at<Vec3b>(i, j)[2] * 0.11;
		}
	}
	return img2;

}
Mat bnw(Mat img1, int thresh)
{
	Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	int n;
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			n = img1.at<uchar>(i, j);
			if (n>thresh)
			{
				img2.at<uchar>(i, j) = 0;
			}
			else img2.at<uchar>(i, j) = 255;
		}
	}
	return img2;
}
Mat hsv_to_rgb(Mat img1)
{
	Mat img2;
	cvtColor(img1, img2, CV_BGR2HLS);
	//imshow("2", img2);
	return (img2);
}
Mat detectcolor(Mat img1,int h,int color)
{
	Mat img2(img1.rows,img1.cols,CV_8UC1,Scalar(0));
	
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			//cout << (int)img1.at<Vec3b>(i, j)[0]<<" " ;
			if (color == 2){ if ((img1.at<Vec3b>(i, j)[0]<69 + h) && (img1.at<Vec3b>(i, j)[0]>69 - h)) img2.at<uchar>(i, j) = 255; }
			if (color == 3){ if ((img1.at<Vec3b>(i, j)[0]<120 + h) && (img1.at<Vec3b>(i, j)[0]>120 - h)) img2.at<uchar>(i, j) = 255; }
			if (color == 1){ if ((img1.at<Vec3b>(i, j)[0]<179 + h) && (img1.at<Vec3b>(i, j)[0]>179 - h)) img2.at<uchar>(i, j) = 255; }
		}
	}
	//imshow("1", img2);
	
	return(img2);
}

Mat cont(int a, int b, Mat img1, Mat img2, queue<Point> q, int x)
{
	q.push(Point(a, b));
	img2.at<schar>(a, b) = 0;
	int i = a, j = b;
	while (1)
	{

		for (int k = -1; k < 2; k++)
		{
			for (int l = -1; l < 2; l++)
			{
				if ((img1.at<uchar>(i + k, j + l) == 255) && (img2.at<schar>(i + k, j + l) == -1))
				{
					q.push(Point(i + k, j + l));
					img2.at<schar>(i + k, j + l) = 0;

				}
			}
		}
		q.pop();
		img2.at<schar>(i, j) = x;
		Point pointPop = q.front();
		i = pointPop.x;
		j = pointPop.y;
		if (q.empty())  break;
	}
	return img2;
	
}

void printblob(Mat img1, int n)
{
	Mat img2(img1.rows, img1.cols, CV_8UC3, Scalar(0));
	for (int x = 1; x < n; x++)
	{
		for (int i = 0; i < img1.rows; i++)
		{
			for (int j = 0; j < img1.cols; j++)
			{
				if (img1.at<schar>(i, j) == x) img2.at<uchar>(i, j) = 255 / (x);
			}

		}
	}
	namedWindow("blob", WINDOW_AUTOSIZE);
	imshow("blob", img2);
	waitKey(0);
}
Mat blobdetect(Mat img1)
{
	int x = 1;
	Mat img2(img1.rows, img1.cols, CV_8SC1, Scalar(-1));
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if ((img1.at<uchar>(i, j) == 255) && (img2.at<schar>(i,j)==-1))
			{
				queue<Point> q;
				img2=cont(i,j,img1,img2,q,x);
				x++;

			}
		}
	}
	printblob(img2,x);

}

Mat hough(Mat img1)
{
	cout << img1.rows << " ";

	int **a = new int*[3300*sizeof(int *)];
	for (int i = 0; i < 3300; ++i)
		a[i] = new int[180*sizeof(int)];
	for (int p = 0; p< 3300; p++)
	{
		for (int q= 0; q <180; q++)
		{
			a[p][q] = 0;
		}
	}
	//a[4][5]=89;
	int r;
	cout << "Point1\n";
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if (img1.at<uchar>(i, j) == 255)
			{
				for (int t = 0; t <180; t++)
				{
					r = abs((int)(j*(cos((t*3.14) / 180.0)) + i*(sin((t*3.14) / 180.0))));
					a[r][t]++;
					//cout <<"("<< r << ","<<t<<") ";
				}
			}
		}
	}
	cout << "Point2";
	int max = a[0][0], t_max = 0, r_max = 0;
	for (int i = 0; i < 3300; i++)
	{
		for (int j = 0; j < 180; j++)
		{
			if (a[i][j]>max)
			{
				max = a[i][j];
				r_max = i;
				t_max = j;
			}
		}
	}

	cout << max << " " << t_max << " " << r_max << endl;
	//getchar();
	int j, i;
	cout << img1.rows<<" ";
	Mat img(img1.rows, img1.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < img.rows; i++)
	{
		j = (int)abs((r_max - i*sin(t_max*3.14/180)) / (cos(t_max*3.14/180)));
		img.at<uchar>(i,j) = 255;
		
	}cout << "abc";
	cout << img.size() << img1.size() << endl;
	imshow("hough_image", img);
	waitKey(0);
	return(img);
}

Point centroids(int n, vector<Point> a)
{
	int x, y;
	Point centroid;
	if (n == 3)
	{
		x = (a[0].x + a[1].x + a[2].x) / 3;
		y = (a[0].y + a[1].y + a[2].y) / 3;
		centroid.x = x;
		centroid.y = y;
		cout << endl << "centroid of triangle is - {" << centroid.x << "," << centroid.y << "}"<<endl;
	}
	else if (n == 4)
	{
		cout << a[0].x << endl << a[2].x << endl;
		centroid.x = (a[0].x + a[2].x) / 2;
		centroid.y = (a[0].y + a[2].y) / 2;
		cout << endl << "centroid of square is - {" << centroid.x << "," << centroid.y << "}"<<endl;
	}
	else
	{
		int x1 = a[0].x, x2 = a[1].x, x3 = a[2].x;
		int y1 = a[0].y, y2 = a[1].y, y3 = a[2].y;

		float mr =(float)(y1 - y2) / (float)(x1 - x2);
		float mt =(float)(y2 - y3) / (float)(x2 - x3);

		centroid.x = (mr*mt*(y3 - y1) + mr*(x2 + x3) - mt*(x1 + x2)) / (2 * (mr - mt));
		centroid.y = (-1 / mr)*(centroid.x - (x1 + x2) / 2) + (y1 + y2) / 2;
		cout << endl << "centroid of circle is - {" << centroid.x << "," << centroid.y << "}" << endl;
	}
	return(centroid);
}

void movebot(Mat frame, int c)
{
	namedWindow("base", WINDOW_AUTOSIZE);
	Mat a(frame.rows, frame.cols, CV_8UC1, Scalar(0));
	for (int i =-2; i <3; i++)
	{
		for (int j =0; j <100; j++)
			a.at<uchar>(j, c) = 255;
	}
	imshow("base", a);
}
Mat shape_detect(Mat img1,int color)
{
	vector<vector<Point>> c;
	int tol = 2;
	namedWindow("3", WINDOW_AUTOSIZE);
	//createTrackbar("tollerence","3",&tol,100);
	Mat img2;
		Mat img3= hsv_to_rgb(img1);
		img3 = detectcolor(img3, tol, color);
		img3 = erosion(img3);
		img3 = dilation(img3);
		imshow("3", img3);
		img2 = img3;
	
	findContours(img2, c, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	vector<Point> app;
	int x = 0, t = 0, s = 0, cr = 0;
	
	Point cnt,centroid1,centroid2,centroid3;
	cnt.x = 0;
	cnt.y = 0;
	for (int i = 0; i < c.size(); i++)
	{
		int c1,c2;
		double epsilon = 0.05*arcLength(c[i], true);
		approxPolyDP(c[i], app, epsilon, true);
		x = app.size();
		if (x == 3) {
			c1 = ((app[0].x - app[1].x)*(app[0].x - app[1].x)) + ((app[0].y - app[1].y)*(app[0].y - app[1].y));
			c2 = ((app[0].x - app[2].x)*(app[0].x - app[2].x)) + ((app[0].y - app[2].y)*(app[0].y - app[2].y));
			if ((c1>20)&&(c2>20))
			{
				t++;
				centroid1=centroids(3, app);

			}
		}
		if (x == 4) {
			c1 = ((app[0].x - app[1].x)*(app[0].x - app[1].x)) + ((app[0].y - app[1].y)*(app[0].y - app[1].y));
			c2 = ((app[0].x - app[2].x)*(app[0].x - app[2].x)) + ((app[0].y - app[2].y)*(app[0].y - app[2].y));
			if ((c1 > 10)&&(c2>20))
			{
				s++;
				centroid2=centroids(4, app);
			}
		}

		if (x >4) {
			
			cr++;
			centroid3=centroids(7,app);
			cnt = centroid3;
		}
    }
	cout << cnt;
	//movebot(img3, cnt.x);
	return(img2);
	//waitKey(0);
	getchar();
	
}

int main()
{

	Mat img1;
	//img1 = imread("aaa.png", CV_LOAD_IMAGE_COLOR);
	VideoCapture v("a.mp4");
	while (1)
	{
		int n = 3;
		int x;
		Mat frame;
		v >> frame;
		imshow("video", frame);
		frame=shape_detect(frame,n);
		//shape_detect(frame, 2);
		//shape_detect(frame, 1);
		int a= waitKey(33);
		if (a==27) break;
	}
//	Mat img2 = blobdetect(img1);*/
//	Mat img1;
//	img1 = imread("magli.png", CV_LOAD_IMAGE_GRAYSCALE);
//	//Mat img2 =hough(img1);
//	imshow("original", img1);
//	waitKey(0);
//	namedWindow("gray", WINDOW_AUTOSIZE);
//	imshow("gray", hough(img1));
//	//waitKey(0);
//	//waitKey(0);
//	//hough(img1);
//	//namedWindow("toll", WINDOW_AUTOSIZE);
//	//imshow("edgedetect", img1);
//	/*int thresh = 10;
//	int lower = 0, upper = 0;
//	createTrackbar("lower", "video", &lower, 256);
//	createTrackbar("upper", "video",&upper,256);
//	VideoCapture V(0);*/
//	//createTrackbar("trackbar", "video",&thresh, 256);
//	//int h = 0;
//	//createTrackbar("hsv", "toll", &h, 100);
//	/*while (1)
//	{
//		Mat img2;*/
//	    ///Canny(img1, img2, lower, upper, 3);
//		//img2 = dilation(img2);
//		//img2 = erosion(img2);
//		//imshow("edgedetect", img2);
//		/*Mat frame;
//		V >> frame;
//		frame = grey(frame);
//		Canny(frame, frame, lower, upper, 3);*/
//		//frame = gausian(frame);
//		//frame = bnw(frame,thresh);
//		//frame = border2(frame);
//		//frame = dilation(frame);
//		//frame = erosion(frame);
//		/*img2 = hsv_to_rgb(img1);
//		Mat img3 = detectcolor(img2,h);
//		imshow("toll", img3);
//		char a = waitKey(33);
//		if (a == 27) break;
//	}*/
//
//	/*Mat img2(img1.rows, img1.cols, CV_8UC1, Scalar(0));
//	img2 = noisemean(img1);
//	namedWindow("mean",WINDOW_AUTOSIZE);
//	imshow("mean", img2);
//	Mat img3(img1.rows, img1.cols, CV_8UC1, Scalar(0));
//	img3 = noisemedian(img1);
//	namedWindow("median", WINDOW_AUTOSIZE);
//	imshow("median", img3);
//	img3 = gausian(img1);
//	namedWindow("gausian", WINDOW_AUTOSIZE);
//	imshow("gausian", img3);*/
//	/*img2 = border(img1);
//	namedWindow("dilated", WINDOW_AUTOSIZE);
//	imshow("dilated", img2);
//	img2 = dilation(img2);
//	namedWindow("eroded", WINDOW_AUTOSIZE); 
//	imshow("eroded", img2);
//	img2 = erosion(img2);
//	//img2 = border2(img1);
//	//img2 = border2(img2);
//	//imshow("edgedetect", img2);
//	waitKey(0);*/
//	return(0);
}