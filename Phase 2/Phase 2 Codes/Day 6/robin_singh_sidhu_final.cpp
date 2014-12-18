// Robin Singh Sidhu
// 13EC10052
#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include <queue>
#include <conio.h>
#include <stdio.h>
#include <windows.h>


using namespace cv;
using namespace std;

#ifndef TSERIAL_H
#define TSERIAL_H

enum serial_parity  { spNONE, spODD, spEVEN };


/* -------------------------------------------------------------------- */
/* -----------------------------  Tserial  ---------------------------- */
/* -------------------------------------------------------------------- */
class Tserial
{
	// -------------------------------------------------------- //
protected:
	char              port[10];                      // port name "com1",...
	int               rate;                          // baudrate
	serial_parity     parityMode;
	HANDLE            serial_handle;                 // ...

	// ++++++++++++++++++++++++++++++++++++++++++++++
	// .................. EXTERNAL VIEW .............
	// ++++++++++++++++++++++++++++++++++++++++++++++
public:
	Tserial();
	~Tserial();
	int           connect(char *port_arg, int rate_arg,
		serial_parity parity_arg);
	void          sendChar(char c);
	void          sendArray(char *buffer, int len);
	char          getChar(void);
	int           getArray(char *buffer, int len);
	int           getNbrOfBytes(void);
	void          disconnect(void);
};
/* -------------------------------------------------------------------- */

#endif TSERIAL_H


class serial{

private:
	// private attributes
	Tserial *com;
public:


	serial() {

	}

	bool startDevice(char *port, int speed)
	{
		com = new Tserial();
		if (com != 0)
		{
			if (com->connect(port, speed, spNONE))
				printf("Not Connected...\n");
			else
				printf("Connected..\n");
			return TRUE;
		}
		else
			return FALSE;
	}

	void stopDevice()
	{
		com->disconnect();
		// ------------------
		delete com;
		com = 0;
	}

	void send_data(unsigned char data)
	{
		//	unsigned char data = 0;


		com->sendChar(data);
		printf("%c", data);

	}
};

#define pi 3.14159265359
#define	gs(x,y)	img.at<uchar>(x, y) 

int cannyimp();
int tb2();
int scharr(Mat);
Mat gtob(int, Mat);
Mat grayscale(Mat);
int rw();
int flag();
void invert(Mat& img);
int histo();
Mat edge_detect(uchar);
int krcheck(Mat img, uchar thresh, int i, int j);
Mat sobel1(Mat);
Mat dilation(Mat img);
Mat erosion(Mat);
Mat meanfilter(Mat);
int median(int a[]);
Mat medianfilter(Mat img);
void swap(int *x, int *y);
Mat gauss_filter(Mat img);
void bfs_blob(Mat img, int **a, int qcount, int i, int j);
void blob_detect(Mat, bool);
void plot(Mat&, int i, int j);
Mat line_detect(Mat linimg, int);
void marker(Mat& img, int r, int t, Mat);
Mat hough_new(Mat img);
void half(Mat&);
bool horizon(Mat);
void right(Mat);
bool straight(Mat img);
int ps();
// CV_8SC1
Point p[1000000];
queue <Point> q;
int flg = 0;

serial comm; //serial is a class type defined in these files, used for referring to the communication device

void main() {
	char data = 'a'; //To store the character to send
	comm.startDevice("COM3", 9600);

	ps();
	comm.stopDevice(); //The device is closed down

}

int ps()
{
	/* PROBLEM STATEMENT */
	VideoCapture vin(1);
	int t1 = 20, t2 = 80;
	int threshold = 200;
	//namedWindow("hough", WINDOW_AUTOSIZE);
	//createTrackbar("thresh", "hough", &threshold, 255);
	//createTrackbar("t2", "hough", &t2, 255);
	//createTrackbar("t1", "hough", &t1, 255);
	int t = 0;
	while (1)
	{
		t++;
		Mat frame;
		vin >> frame;
		Mat img = frame.clone();
		Mat in = frame.clone();

		//img = grayscale(img);
		// first blur input , do canny, do hough
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		GaussianBlur(img, img, Size(3, 3), 0, 0);
		Canny(img, in, t1, t2);
		Mat out = hough_new(in);
		Mat outp = out.clone();
		half(outp);
		imshow("out", outp);
		//horizon(outp);
		//straight(outp);
		if (straight(outp))
		{
			comm.send_data('dddd');
			waitKey(300);
			comm.send_data('dddd');
			waitKey(300);
			comm.send_data('dddd');
			waitKey(300);
			comm.send_data('wwww');
			waitKey(300);
			comm.send_data('wwww');
			waitKey(300);
			comm.send_data('wwww');
			waitKey(300);
			comm.send_data('dd');
			waitKey(300);
			comm.send_data('ww');
			waitKey(300);
			comm.send_data('ww');
			waitKey(300);
			comm.send_data('aaaa');
			waitKey(300);
			comm.send_data('aaaa');
			waitKey(300);
			comm.send_data('aaaa');
			waitKey(300);
			comm.send_data('aaaa');
			waitKey(300);
			comm.send_data('ww');
			waitKey(300);
			comm.send_data('ww');
			waitKey(300);
		}
		// detect and go straight //
		//
		//{
		//	right(outp);
		//}
		// go st


		if (waitKey(20) == 27)
		{
			break;
		}
	}
	return 0;
}
bool straight(Mat img)
{
	int i, j;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	static int count = 0;
	if (horizon(img))
	{
		for (i = 0; i < img.cols / 2; i++)
		{
			if (img.at<Vec3b>(img.rows - 1, i)[2] >= 240 || img.at<Vec3b>(img.rows - 2, i)[2] >= 240 || img.at<Vec3b>(img.rows - 3, i)[2] >= 240)
			{
				x1 = i;
				y1 = img.rows - 1;
			}
			if (img.at<Vec3b>(img.rows - 1, img.cols - 1 - i)[2] >= 240 || img.at<Vec3b>(img.rows - 2, img.cols - 1 - i)[2] >= 240 || img.at<Vec3b>(img.rows - 3, img.cols - 1 - i)[2] >= 240)
			{
				x2 = img.cols - 1 - i;
				y2 = img.rows - 1;
			}

		}

		for (i = 0; i < img.rows*.2; i++)
		{
			if (img.at<Vec3b>(img.rows - 1 - i, 0)[2] >= 240 || img.at<Vec3b>(img.rows - 1 - i, 1)[2] >= 240 || img.at<Vec3b>(img.rows - 1 - i, 2)[2] >= 240)
			{
				x1 = 0;
				y1 = img.rows - 1 - i;
			}
			if (img.at<Vec3b>(img.rows - 1 - i, img.cols - 3)[2] >= 240 || img.at<Vec3b>(img.rows - 1 - i, img.cols - 2)[2] >= 240 || img.at<Vec3b>(img.rows - 1 - i, img.cols - 1)[2] >= 240)
			{
				x2 = img.cols - 1;
				y2 = img.rows - 1 - i;
			}
		}

		int xbot = img.cols / 2;
		int ybot = img.rows / 2;


		if (((xbot - x1)*(xbot - x1) + (ybot - y1)*(ybot - y1)) > ((xbot - x2)*(xbot - x2) + (ybot - y2)*(ybot - y2)))
		{
			// left > right
			comm.send_data('a');
			waitKey(400);
		}
		else if (((xbot - x1)*(xbot - x1) + (ybot - y1)*(ybot - y1)) < ((xbot - x2)*(xbot - x2) + (ybot - y2)*(ybot - y2)))
		{
			comm.send_data('d');
			waitKey(400);
		}

		comm.send_data('w');
		waitKey(400);


		comm.send_data('w');
		waitKey(400);
		return 0;
	}

	else
		return 1;
}
void right(Mat img)
{
	comm.send_data('a');
	waitKey(100);
	comm.send_data('a');
	waitKey(100);
	comm.send_data('a');
	waitKey(100);
}
bool horizon(Mat img)
{
	int i, j, max;

	max = 0;
	
	for (i = img.rows*.55; i < img.rows*.75; i++)
	{

		
		for (j = img.cols*0.2; j < img.cols*0.7; j++)
		{

			if (img.at<Vec3b>(i, j)[2] >= 240 || img.at<Vec3b>(i - 1, j)[2] >= 240 || img.at<Vec3b>(i + 1, j)[2] >= 240 || img.at<Vec3b>(i + 2, j)[2] >= 240)
				max++;
		}
	}
	if (max > 200)
	{
		return 0;
	}
	else
	{
		comm.send_data('a');
		waitKey(400);
		comm.send_data('d');
		waitKey(400);
		comm.send_data('w');
		waitKey(400);
		return 1;
	}
}
void half(Mat &img)
{
	int i, j;
	Vec3b col;
	col[0] = col[1] = col[2] = 0;
	for (i = 0; i < (img.rows + 1) / 2; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			img.at<Vec3b>(i, j) = col;
		}
	}
}
Mat hough_new(Mat img)
{
	Mat dst;
	Canny(img, dst, 50, 200, 3);
	Mat im(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
	vector<Vec4i> lines1;
	HoughLinesP(dst, lines1, 1, CV_PI / 360, 40, 50, 10); // last three are thresh , min line len, max gap;
	for (size_t i = 0; i < lines1.size(); i++)
	{
		Vec4i l = lines1[i];
		line(im, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}
	////////////////////////////////////////	
	Mat cdst(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 60, 0, 0);
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
	Mat finl = im.clone();
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (cdst.at<Vec3b>(i, j) == im.at<Vec3b>(i, j))
			{
				finl.at<Vec3b>(i, j) = im.at<Vec3b>(i, j);
			}
		}
	}

	//imshow("b", cdst);
	// imshow("a", im);

	return finl;

}
int contour_detect(Mat binimg) // binimg // complete this ??
{
	Mat im = binimg;
	Mat img(binimg.rows, binimg.cols, CV_8UC1);
	Canny(binimg, img, 100, 200);
	int i, j;
	/*	for (i = 0; i < binimg.rows; i++){for (j = 0; j < binimg.cols; j++){if (im.at<uchar>(i, j) >= 200)im.at<uchar>(i, j) = 255;elseim.at<uchar>(i, j) = 0;}}*/

	vector<vector<Point>> c;
	vector<Point> app;
	//vector<Vec4i> hierarchy;
	findContours(img, c, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	approxPolyDP(c[0], app, 5, 1);

}



int line_detect_main()
{
	int threshold = 100;
	Mat linim = imread("A:\\lines.png", 1);
	Mat img = linim;
	imshow("org1", img);
	Canny(linim, linim, 50, 200);
	namedWindow("det", WINDOW_AUTOSIZE);
	createTrackbar("th", "det", &threshold, 250);
	while (1)
	{

		Mat detectim = line_detect(linim, threshold);
		imshow("det", detectim);
		if (waitKey(33) == 27)
			break;
	}
	return 0;
}

Mat line_detect(Mat linimg, int threshold) // linimg is almost binary
{
	int i, j;
	int rl = linimg.rows;
	int cl = linimg.cols;
	Mat acc(cl + rl, 720, CV_8UC1);
	Mat img(rl, cl, CV_8UC1, Scalar(0));
	for (i = 0; i < cl + rl; i++)
	{
		for (j = 0; j < 720; j++)
		{
			acc.at<uchar>(i, j) = 0;
		}
	}
	for (i = 0; i < rl; i++)
	{
		for (j = 0; j < cl; j++)
		{
			if (linimg.at<uchar>(i, j) >= 240) //if white pixel
			{
				// represent in hough space
				plot(acc, i, j);

			}
		}
	}
	int max = 170, maxr = 0, maxt = 0;
	for (i = 0; i < rl + cl; i++)
	{
		for (j = 0; j < 720; j++)
		{
			if (acc.at<uchar>(i, j) > threshold)  // if possible intersection
			{
				// mark the line in img
				marker(img, i, j, linimg);
				//max = acc.at<uchar>(i, j);
				//maxr = i; // r of intersection	
				//maxt = j; // theta
			}
		}
	}

	/*for (i = 0; i < rl ; i++) // display the line with r = maxr and theta = maxt
	{
	for (j = 0; j < cl; j++)
	{
	if (int(j*cos(maxt*pi / 360) + i*sin(maxt*pi / 360)) >= maxr-1 && int(j*cos(maxt*pi / 360) + i*sin(maxt*pi / 360)) <= maxr+1)
	{
	gs(i, j) = 255;
	}
	}
	}
	*/
	//imshow("detect", img);
	//imshow("Hough", acc);


	return img;
}
void marker(Mat& img, int r, int t, Mat linimg)
{
	int i, j;
	for (i = 0; i < img.rows; i++) // display the line with r = maxr and theta = maxt
	{
		for (j = 0; j < img.cols; j++)
		{
			if ((j*cos(t*pi / 360) + i*sin(t*pi / 360)) >= r - 1 && int(j*cos(t*pi / 360) + i*sin(t*pi / 360)) <= r + 1 && linimg.at<uchar>(i, j) >= 240)
			{
				gs(i, j) = 255;
			}
		}
	}
}
void plot(Mat& acc, int i, int j)
{
	int r, t;
	for (t = 0; t < 720; t++) // t is angle in degrees , incrementing half a degree
	{
		// r = xcos + ysin
		r = int(j*cos(t*pi / 360) + i*sin(t*pi / 360));
		if (r >= 0 && acc.at<uchar>(r, t) < 253)
			acc.at<uchar>(r, t) += 2;
	}
}

void blob_detect(Mat img, bool imgtyp) // complete for colored detection???
{
	if (imgtyp == 0)
	{
		int i, j, qcount = 1;
		//Mat img = imread("A:\\basic.png", 0);
		Mat blobbed(img.rows, img.cols, CV_8UC1);
		int **a = (int **)malloc(sizeof(int *)*img.rows);
		for (i = 0; i < img.rows; i++)
		{
			a[i] = (int *)malloc(sizeof(int)*img.cols);
		}

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				a[i][j] = -1;
			}
		}

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				if (gs(i, j) == 255 && a[i][j] == -1) // unexplored white pixel
				{
					bfs_blob(img, a, qcount, i, j);
					qcount++;
				}
			}
		}

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				if (a[i][j] == 1)
					blobbed.at<uchar>(i, j) = 255;
				else if (a[i][j] == 2)
					blobbed.at<uchar>(i, j) = 128;
				else
					blobbed.at<uchar>(i, j) = 0;
			}
		}


		imshow("fucked", img);
		imshow("norm", blobbed);
		waitKey(0);
	}
	else if (imgtyp == 1)
	{

		int i, j, qcount = 1;
		cvtColor(img, img, CV_BGR2HLS);
		Mat blobbed(img.rows, img.cols, CV_8UC3);
		Mat visit(img.rows, img.cols, CV_16SC1);
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				visit.at<schar>(i, j) = -1;
			}
		}

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				if (visit.at<schar>(i, j) == -1) // unexplored white pixel
				{
					//bfs_blob(img, a, qcount, i, j);
					qcount++;
				}
			}
		}
	}


}
void bfs_blob(Mat img, int **a, int qcount, int i, int j)
{
	// q.pop , q.push, q.rear
	Point tmp;
	static int cnt = 0;
	p[cnt].x = j;
	p[cnt].y = i;
	a[i][j] = 0;
	q.push(p[cnt]);
	cnt++;
	// que the adjacent elements of p
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		int k, l;
		for (k = tmp.y - 1; k <= tmp.y + 1; k++)
		{
			for (l = tmp.x - 1; l <= tmp.x + 1; l++)
			{
				if (gs(k, l) == 255 && a[k][l] == -1)
				{
					if (k == i && l == j)
					{
					}
					else
					{
						p[cnt].x = l;
						p[cnt].y = k;
						q.push(p[cnt]);
						a[k][l] = 0;
						cnt++;
					}
				}
			}
		}
		a[tmp.y][tmp.x] = qcount;
	}
}

int hsvdetect()
{
	Mat img = imread("A:\\gm.PNG");
	Mat hsvim(img.rows, img.cols, CV_8UC3);
	Mat hsvi1(img.rows, img.cols, CV_8UC1);
	// hue (0-240) grn- (60-90), rd(230-240 || 0-10), blue (130, 160)
	cvtColor(img, hsvim, CV_BGR2HLS);
	int i, j;
	uchar bthresh = 100, rthresh = 100, gthresh = 250;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			Vec3b color = hsvim.at<Vec3b>(i, j);
			if (color[0] <= 100 && color[0] >= 70)
			{
				hsvi1.at<uchar>(i, j) = 0;
			}
			else
				hsvi1.at<uchar>(i, j) = 255;

		}
	}
	imshow("unpro", img);
	imshow("pro'ed", hsvi1);
	waitKey(0);

	return 0;
}
void video()
{
	// video //
	VideoCapture v("A:\\Naruto - Evanescence - My Last Breath.avi");
	//A:\\RobF\\filmaa\\Reign Of Fire (2002)\\Reign.Of.Fire.(2002).mkv
	// A:\\Naruto - Evanescence - My Last Breath.avi
	namedWindow("edged", WINDOW_AUTOSIZE);
	int x = 30, low = 40, high = 80;
	createTrackbar("Speed", "edged", &x, 100);
	createTrackbar("low", "edged", &low, 80);
	createTrackbar("high", "edged", &high, 150);
	while (1)
	{
		Mat frame;
		v >> frame;
		Mat img(frame.rows, frame.cols, CV_8UC1);
		Mat img1(frame.rows, frame.cols, CV_8UC1);
		cvtColor(frame, img, CV_RGB2GRAY);
		//img1 = sobel1(img);
		Canny(img, img1, low, high);
		//imshow("video", frame);
		imshow("edged", img1);
		char a = waitKey(x);
		if (a == 27)
			break;
	}
}
int cannyimp()
{
	Mat im = imread("A:\\lines.png", 1);
	int low = 50, high = 100;
	Mat inpimg = grayscale(im);
	Mat out(inpimg.rows, inpimg.cols, CV_8UC1);
	namedWindow("canned", WINDOW_AUTOSIZE);
	createTrackbar("low", "canned", &low, 80);
	createTrackbar("high", "canned", &high, 150);

	while (1)
	{
		Canny(inpimg, out, low, high);
		imshow("canned", out);
		char a = waitKey(33);
		if (a == 27)
		{
			break;
		}
	}

	return 0;
}
Mat gauss_filter(Mat img)
{
	Mat imfil(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, l, k;
	int value;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			imfil.at<uchar>(i, j) = 0.06*(gs(i - 1, j - 1) + gs(i - 1, j + 1) + gs(i + 1, j - 1) + gs(i + 1, j + 1)) + 0.098*(gs(i - 1, j) + gs(i + 1, j) + gs(i, j - 1) + gs(i, j + 1)) + 0.162*(gs(i, j));
		}
	}
	return imfil;

}
void swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
Mat medianfilter(Mat img)
{
	int i, j, k, l, r, med;
	int a[9];
	Mat imfil(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			r = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					a[r++] = gs(k, l);
				}
			}
			imfil.at<uchar>(i, j) = median(a);
		}
	}

	return imfil;

}
int median(int a[])
{
	int  i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = i; j < 9 - i - 1; j++)
		{
			if (a[j] >= a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
			}
		}
	}
	return a[4];
}

Mat meanfilter(Mat img)
{
	int i, j, k, l, mean;
	Mat imfil(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			mean = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					mean += gs(k, l);
				}
			}

			imfil.at<uchar>(i, j) = (mean / 9);
		}
	}

	return imfil;

}

Mat dilation(Mat img)
{
	int i, j, black, white, k, l;
	Mat imdil(img.rows, img.cols, CV_8UC1);
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			black = white = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (gs(k, l) == 0)
						black++;
					else white++;
				}
			}
			if (black > white)
				imdil.at<uchar>(i, j) = 0;
			else
				imdil.at<uchar>(i, j) = 255;
		}
	}
	return imdil;
}
Mat erosion(Mat img)
{
	int i, j, black, white, k, l;
	Mat imer(img.rows, img.cols, CV_8UC1);
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			black = white = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (gs(k, l) == 0)
						black++;
					else white++;
				}
			}
			if (black > white)
			{
				if (white == 0)
					imer.at<uchar>(i, j) = 0;
				else
					imer.at<uchar>(i, j) = 255;

			}
			else
			{
				if (black == 0)
					imer.at<uchar>(i, j) = 255;
				else
					imer.at<uchar>(i, j) = 0;
			}

		}
	}

	return imer;
}





int scharr(Mat imgray)
{
	//string str = "A:\\Scenary.jpg";
	//Mat imgray = imread(str, 0);
	Mat fin, gradx, grady, agradx, agrady;

	Scharr(imgray, gradx, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(gradx, agradx);

	//Scharr(imgray, grady, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	//convertScaleAbs(grady, agrady);

	//	addWeighted(agradx, 0.5, agrady, 0.5, 0, fin);
	imshow("Bird", agradx);
	waitKey(0);
	return 0;
}
Mat sobel1(Mat img) // img is grayscale
{
	//	Mat img = grayscale(55, 33, 11);
	Mat im(img.rows, img.cols, CV_8UC1);
	Mat im1(img.rows, img.cols, CV_8UC1);
	float dx, dy, df, dx1, dy1, df1;
	int i, j;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			dx = gs(i - 1, j - 1) + gs(i - 1, j) + gs(i - 1, j + 1) - gs(i + 1, j - 1) - gs(i + 1, j) - gs(i + 1, j + 1);
			dy = gs(i - 1, j - 1) + gs(i, j - 1) + gs(i + 1, j - 1) - gs(i - 1, j + 1) - gs(i, j + 1) - gs(i + 1, j + 1);
			dx1 = -1 * (gs(i - 1, j - 1) + 2 * gs(i - 1, j) + gs(i - 1, j + 1) - gs(i + 1, j - 1) - 2 * gs(i + 1, j) - gs(i + 1, j + 1));
			dy1 = -1 * (gs(i - 1, j - 1) + 2 * gs(i, j - 1) + gs(i + 1, j - 1) - gs(i - 1, j + 1) - 2 * gs(i, j + 1) - gs(i + 1, j + 1));
			df = sqrt(dx*dx + dy*dy);
			df1 = sqrt(dx1*dx1 + dy1*dy1);
			if (df >= 255)
				im.at<uchar>(i, j) = 255;
			else im.at<uchar>(i, j) = df;
			if (df1 >= 255)
				im1.at<uchar>(i, j) = 255;
			else im1.at<uchar>(i, j) = df;
		}
	}
	//namedWindow("Sob1", WINDOW_AUTOSIZE);
	//namedWindow("Sob2", WINDOW_AUTOSIZE);
	//imshow("Sob1", im);
	//imshow("Sob2", im1);
	//waitKey(0);
	return im1;// returning sobel

}

Mat edge_detect(uchar thresh)
{
	Mat img = grayscale(imread("A:\\lines.png", 1));

	Mat im(img.rows, img.cols, CV_8UC1);

	int i, j;

	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			if (krcheck(img, thresh, i, j))
				im.at<uchar>(i, j) = 255;
			else
				im.at<uchar>(i, j) = 0;
		}
	}
	return im;
}
int krcheck(Mat img, uchar thresh, int i, int j)
{
	int k, l;
	uchar max = 0, min = 255;
	for (k = i - 1; k <= i + 1; k++)
	{
		for (l = j - 1; l <= j + 1; l++)
		{
			if (img.at<uchar>(k, l) >= max)
			{
				max = img.at<uchar>(k, l);
			}
			if (img.at<uchar>(k, l) <= min)
			{
				min = img.at<uchar>(k, l);
			}
		}
	}
	if ((max - min) > thresh)
		return 1;
	else return 0;
}

int tb2()
{
	int x = 100, slut = 100, y = 100;
	int i, j;
	string str = "C:\\Users\\Hellblazer\\Documents\\Visual Studio 2013\\Projects\\vision2\\cw.png";
	Mat img = imread(str, 1);
	namedWindow("Bitch", WINDOW_AUTOSIZE);
	createTrackbar("Red", "Bitch", &slut, 255);
	while (1 && x + slut <= 255)
	{
		createTrackbar("Blue", "Bitch", &x, 255 - slut);

		imshow("Bitch", img);
		waitKey(33);
	}


	return 0;
}
int tb1()
{
	int fuck = 50;
	Mat img = grayscale(imread("A:\\lines.png", 1));
	namedWindow("wind", WINDOW_AUTOSIZE);
	createTrackbar("Meter", "wind", &fuck, 255);
	while (1)
	{

		Mat im = gtob(fuck, img);
		imshow("wind", im);
		char a = waitKey(33);
		if (a == 27)
			break;

	}
	return 0;
}
int histo()
{
	int i, j;
	//string str = "A:\\1.png";
	long long int hist[256] = { 0 };
	Mat img = grayscale(imread("A:\\lines.png", 1));
	//int threshold;
	//cout << "enter threshold\n";
	///cin >> threshold;
	//gtob(threshold, img);
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			hist[img.at<uchar>(i, j)]++;
		}
	}
	long long int no_pix = img.rows * img.cols;
	long long int sum = 0, threshold;
	for (i = 0; i < 256 && sum <= (no_pix / 2); i++)
	{
		sum += hist[i];
	}
	threshold = i;
	cout << threshold;
	Mat his(300, 256, CV_8UC1, Scalar(0));
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < hist[i] / 10; j++)
		{
			his.at<uchar>(j, i) = 255;
		}
	}
	invert(his);
	imshow("bitch", his);
	waitKey(0);
	return 0;
}
void invert(Mat& img)
{
	int i, j, k;
	for (i = 0; i <= (img.rows) / 2; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			// img is bgr
			/*
			Vec3b col1 = img.at<Vec3b>(i, j);
			Vec3b col2 = img.at<Vec3b>(img.rows - 1 - i, j);
			Vec3b tmp = col1;
			col1 = col2;
			col2 = tmp;
			img.at<Vec3b>(i, j) = col1;
			img.at<Vec3b>(img.rows - 1 - i, j) = col2;
			*/
			// img is bw
			uchar tmp = img.at<uchar>(i, j);
			img.at<uchar>(i, j) = img.at<uchar>(img.rows - 1 - i, j);
			img.at<uchar>(img.rows - 1 - i, j) = tmp;



		}
	}
}

Mat gtob(int threshold, Mat im)
{
	Mat img(im.rows, im.cols, CV_8UC1);
	int i, j;
	for (i = 0; i < im.rows; i++)
	{
		for (j = 0; j < im.cols; j++)
		{
			if (im.at<uchar>(i, j) > threshold)
			{
				img.at<uchar>(i, j) = 255;
			}
			else
				img.at<uchar>(i, j) = 0;
		}
	}

	return img;

}





Mat grayscale(Mat img)
{
	string str = "A:\\skyscrapers_and_couds-t2.jpg";
	//zY5euSP.jpg
	// 1.png
	//9deeSaM.jpg
	//Ferrari-599-GTB-widescreen-001.jpg
	//CYB0049.jpg
	//38709.jpg
	//skyscrapers_and_couds-t2.jpg
	//Mat img = imread(str, 1);
	//Mat im(img.rows, img.cols, CV_8UC1);
	//Mat im1(img.rows, img.cols, CV_8UC1);
	//Mat im2(img.rows, img.cols, CV_8UC1);
	Mat im12(img.rows, img.cols, CV_8UC1);

	// best grayscale from colored (.56, .33, .11)
	int i, j;
	for (i = 0; i < img.cols; i++)
	{
		for (j = 0; j < img.rows; j++)
		{
			Vec3b color = img.at<Vec3b>(j, i);
			//im.at<uchar>(j, i) = color[0];
			//im1.at<uchar>(j, i) = color[1];
			//im2.at<uchar>(j, i) = color[2];
			im12.at<uchar>(j, i) = color[0] * .55 + .33*color[1] + color[2] * .11;
		}
	}

	//namedWindow("bitch", WINDOW_AUTOSIZE);
	//namedWindow("bitch1", WINDOW_AUTOSIZE);
	//namedWindow("bitch2", WINDOW_AUTOSIZE);
	//namedWindow("bitch12", WINDOW_AUTOSIZE);
	//imshow("bitch", im);
	//imshow("bitch1", im1);
	//imshow("bitch2", im2);
	//imshow("bitch12", im12);
	return im12;
}

int rw()
{
	int x, y;
	string str = "A:\\1.png";
	Mat im = imread(str, CV_LOAD_IMAGE_COLOR);
	// imread(, 1) colored in bgr
	// imread(, 0) grayscale

	//Mat im = imread("A:\\zY5euSP.jpg", CV_LOAD_IMAGE_COLOR);
	//namedWindow("sc", WINDOW_AUTOSIZE);
	namedWindow("sb", WINDOW_AUTOSIZE);
	imshow("sb", im);
	waitKey(0);
	for (y = 0; y < im.rows; y++)
	{


		for (x = 0; x < im.cols; x++)
		{
			Vec3b color = im.at<Vec3b>(y, x); // a vector of dim 3
			color[1] = color[2] = 0;
			im.at<Vec3b>(y, x) = color;
		}

	}
	namedWindow("sb", WINDOW_AUTOSIZE);
	imshow("sb", im);
	waitKey(0);
	//	imshow("sb", image);
	return 0;
}


int flag()
{

	Mat img(300, 300, CV_8UC3, Scalar(0, 0, 0));
	int i, j;

	for (i = 0; i < 300; i++)
	{

		for (j = 0; j < 100; j++)
		{
			img.at<Vec3b>(i, j)[0] = 120; // 0 128 255
			img.at<Vec3b>(i, j)[1] = 128;
			img.at<Vec3b>(i, j)[2] = 255;
		}
		for (j = 100; j < 200; j++)
		{
			img.at<Vec3b>(i, j)[0] = 255; // 255 255 255
			img.at<Vec3b>(i, j)[1] = 255;
			img.at<Vec3b>(i, j)[2] = 255;
		}
		for (j = 200; j < 300; j++)
		{
			img.at<Vec3b>(i, j)[0] = 10; // 0 255 0
			img.at<Vec3b>(i, j)[1] = 255;
			img.at<Vec3b>(i, j)[2] = 110;
		}
	}

	namedWindow("bitch", WINDOW_AUTOSIZE);
	imshow("bitch", img);
	waitKey(0);
	return 0;
}

/*int thresh = 20;
namedWindow("Wind", WINDOW_AUTOSIZE);
//Mat image = edge_detect(thresh);
createTrackbar("Bitch", "Wind", &thresh, 200);
while (1)
{
Mat image = edge_detect(thresh);
imshow("Wind", image);
char a = waitKey(33);
if (a == 27)
break;
}
Mat image = sobel1();
imshow("sobel1", image);
waitKey(0);
scharr(grayscale(1,1,1));
Mat img = edge_detect(50);
Mat imdilated = dilation(img);
Mat imeroded = erosion(imdilated);
//namedWindow("bin", WINDOW_AUTOSIZE);
imshow("bin", img);
imshow("dil1", imdilated);
imshow("erod1", imeroded);
waitKey(0);

//filtered
Mat img = grayscale(1, 1, 1);
Mat filtered = medianfilter(img);
Mat medfilt = medianfilter(img);
Mat gausfilt = gauss_filter(img);
imshow("Unfiltered", img);
imshow("Mean Filtered", filtered);
imshow("Med Filtered", medfilt);
imshow("gauss", gausfilt);
waitKey(0);

while (data != 'l'){
printf("Enter character to be sent"); //User prompt
scanf_s("%c", &data); //User input
/* “COM 2” refers to the com port in which the USB to SERIAL port is attached. It is shown by right clicking on my computer, then going to properties and then device manager
9600 is the baud-rate in bits per second */
/*comm.send_data(data); //The data is sent through the port
}
*/