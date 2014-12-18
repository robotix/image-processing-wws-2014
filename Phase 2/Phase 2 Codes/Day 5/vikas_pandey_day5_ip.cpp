#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<queue>
using namespace cv;
using namespace std;

#define pi 3.1414

void flag_display(){													//display flag
	Mat image(300, 1000, CV_8UC3, Scalar(0, 0, 0));
	for (int x = 0; x < 1000; x++){
		for (int y = 0; y < 300; y++){
			if (y < 100)
			{
				image.at<Vec3b>(y, x)[1] = 165;
				image.at<Vec3b>(y, x)[2] = 255;
			}
			else if (y > 200)
				image.at<Vec3b>(y, x)[1] = 255;
			else{
				image.at<Vec3b>(y, x)[0] = 255;
				image.at<Vec3b>(y, x)[1] = 255;
				image.at<Vec3b>(y, x)[2] = 255;
			}

		}
	}
	namedWindow("flag", WINDOW_AUTOSIZE);
	imshow("flag", image);

}

Mat grayscale(Mat M,int thres,int thres2){																//return grayscale image with a ratio
	Mat gray(M.rows, M.cols, CV_8UC1);
	for (int x = 0; x < M.cols; x++){
		for (int y = 0; y < M.rows; y++){
			gray.at<uchar>(y, x) = (M.at<Vec3b>(y, x)[0] * thres +thres2*M.at<Vec3b>(y, x)[1] + (100-thres-thres2)*M.at<Vec3b>(y, x)[2])/100;

		}
	}
	return gray;

}

Mat grayscale_avg(Mat M){															//return grayscale image of input using average
	Mat gray(M.rows, M.cols, CV_8UC1);
	for (int x = 0; x < M.cols; x++){
		for (int y = 0; y < M.rows; y++){
			gray.at<uchar>(y, x) = (M.at<Vec3b>(y, x)[0] + M.at<Vec3b>(y, x)[1] + M.at<Vec3b>(y, x)[2])/3;

		}
	}
	return gray;

}

Mat black_white(Mat m,int threshold){												//return black and white image acc to threshold
	Mat gray = grayscale_avg(m);
	for (int x = 0; x < gray.cols; x++){
		for (int y = 0; y < gray.rows; y++){
			gray.at<uchar>(y, x) = (gray.at<uchar>(y, x))<threshold?0:255;
		}
	}
	return gray;

}

Mat patches(){																		//display 10x10 patches
	int rows = 10, cols = 10;
	Mat m(1000, 1000, CV_8UC3, Scalar(0, 0, 0));

	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			for (int i = (m.cols/cols)*col; i < (m.cols/cols)*(col+1); i++){
				for (int j = (m.rows/rows)*row; j < (m.rows/rows)*(row+1); j++){
					if ((row + col) % 3 == 0)
						m.at<Vec3b>(j, i)[0] = 255;
					else if ((row + col) % 3 == 2)
						m.at<Vec3b>(j, i)[1] = 255;
					else
						m.at<Vec3b>(j, i)[2] = 255;

				}

			}
		}
	}
	return m;
	
}

Mat reverse(Mat m){																//upside down
	uchar temp;
	for (int x = 0; x < m.cols*3; x++){
		for (int y = 0; y < m.rows/2; y++){
			temp = m.at<uchar>(y, x);
			m.at<uchar>(y, x) = m.at<uchar>(m.rows - y-1, x);
			m.at<uchar>(m.rows - y-1, x) = temp;
		}
	}
	return m;
}

Mat rot_lateral(Mat m){															//mirror image
	uchar temp;
	for (int x = 0; x < m.cols/2; x++){
		for (int y = 0; y < m.rows; y++){
			temp = m.at<Vec3b>(y,x)[0];
			m.at<Vec3b>(y, x)[0] = m.at<Vec3b>(y, m.cols-x-1)[0];
			m.at<Vec3b>(y,m.cols-1-x)[0] = temp;
			temp = m.at<Vec3b>(y, x)[1];
			m.at<Vec3b>(y, x)[1] = m.at<Vec3b>(y, m.cols - x - 1)[1];
			m.at<Vec3b>(y, m.cols - 1 - x)[1] = temp;
			temp = m.at<Vec3b>(y, x)[2];
			m.at<Vec3b>(y, x)[2] = m.at<Vec3b>(y, m.cols - x - 1)[2];
			m.at<Vec3b>(y, m.cols - 1 - x)[2] = temp;
		}
	}
	return m;
}

Mat histogram(Mat m,int *thres){                                         //return histogram image and threshold
	Mat gray = grayscale_avg(m);
	int freq[256];
	unsigned int sum = 0;
	for (int i = 0; i < 256; i++)
		freq[i] = 0;
	for (int x = 0; x < gray.cols; x++){									//get frequency in freq array
		for (int y = 0; y < gray.rows; y++){
			freq[gray.at<uchar>(y, x)]++; 
			}
	}
	int scale=0;
	for (int x = 0; x < 256; x++){											//threshold frequency and scaling factor
		sum += freq[x];
		if (sum<(gray.total()/2))
		{
			*thres = x;
		}
		scale = (freq[x]>scale) ? freq[x] : scale;
		
	}
	Mat hist(400, 260, CV_8UC1,Scalar(255));
	for (int x = 0; x < 256; x ++){											//plotting histogram
		for (int y = hist.rows-((freq[x]*399)/scale)-1; y< hist.rows; y++){
			hist.at<uchar>(y, x) = 0;

		}
	}
	return hist;

}

Mat edge_detection(Mat m, int thres){
	Mat edge(m.rows, m.cols, CV_8UC1);
	for (int x = 0; x < m.cols;x++){
		for (int y = 0; y < m.rows; y++){
			if (x == 0 || y == 0 || x == (m.cols - 1)||y==(m.rows-1))
				edge.at<uchar>(y, x) = 0;
			else{
				int max = 0;
				int min = 100000;
				for (int i = 0; i < 3; i++){
					for (int j = 0; j<3; j++){
						max = m.at<uchar>(y - 1 + j, x - 1 + i)>max ? m.at < uchar>(y - 1 + j, x - 1 + i) : max;
						min = m.at<uchar>(y - 1 + j, x - 1 + i) < min ? m.at < uchar>(y - 1 + j, x - 1 + i) : min;
					}
				}
				if ((max - min)>thres){
					edge.at<uchar>(y, x) = 255;
				}
				else
					edge.at<uchar>(y, x) = 0;
			}
		}
	}

	return edge;
}

Mat edge_detection2(Mat m){
	int delx = 0, dely = 0;
	Mat edge(m.rows, m.cols, CV_8UC1);
	for (int x = 0; x < m.cols; x++){
		for (int y = 0; y < m.rows; y++){
			if (y == 0 || x == 0 || y == (m.rows - 1) || x == (m.cols - 1))
				edge.at<uchar>(y, x) = 0;
			else{
				delx = 0;dely=0;
				for (int i = 0; i < 3; i++){
					delx += m.at<uchar>(y - 1 + i, x + 1) - m.at<uchar>(y - 1 + i, x - 1);
					dely += m.at<uchar>(y - 1 , x - 1+i) - m.at<uchar>(y +1, x - 1+i);
				}
				edge.at<uchar>(y, x) = sqrt(delx*delx + dely*dely)<255 ? sqrt(delx*delx + dely*dely):255;
			}
		}
	}
	return edge;
}

Mat edge_detectionx(Mat m){
	int delx = 0;
	Mat edge(m.rows, m.cols, CV_8UC1);
	for (int x = 0; x < m.cols; x++){
		for (int y = 0; y < m.rows; y++){
			if (y == 0 || x == 0 || y == (m.rows - 1) || x == (m.cols - 1))
				edge.at<uchar>(y, x) = 0;
			else{
				delx = 0;
				for (int i = 0; i < 3; i++){
					delx += m.at<uchar>(y - 1 + i, x + 1) - m.at<uchar>(y - 1 + i, x - 1);
				}
				edge.at<uchar>(y, x) = abs(delx);
			}
		}
	}
	return edge;
}

Mat dilation(Mat m){
	int black = 0,white;
	Mat dil(m.rows, m.cols, CV_8UC1);
	for (int x = 0; x < m.cols; x++){
		for (int y = 0; y < m.rows; y++){
			if (y == 0 || x == 0 || y == (m.rows - 1) || x == (m.cols - 1))
				dil.at<uchar>(y, x) = 0;
			else{
				black = 0; white = 0;
				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 3; j++){
						m.at<uchar>(y - 1 +j, x - 1 + i) == 0 ? (black++) : (white++);
					}
				}
				if (black == 0)
					dil.at<uchar>(y, x) = 255;
				else if (black>white||white==0)
					dil.at<uchar>(y, x) = 0;
				else
					dil.at<uchar>(y, x) = 255;
			}
		}
	}
	return dil;
}

Mat erosion(Mat m){
	int black = 0, white;
	Mat eros(m.rows, m.cols, CV_8UC1);
	for (int x = 0; x < m.cols; x++){
		for (int y = 0; y < m.rows; y++){
			if (y == 0 || x == 0 || y == (m.rows - 1) || x == (m.cols - 1))
				eros.at<uchar>(y, x) = 0;
			else{
				black = 0; white = 0;
				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 3; j++){
						m.at<uchar>(y - 1 + j, x - 1 + i) == 0 ? (black++) : (white++);
					}
				}
				if (black == 0)
					eros.at<uchar>(y, x) = 255;
				else if (black<white||white==0)
					eros.at<uchar>(y, x) = 0;
				else
					eros.at<uchar>(y, x) = 255;
			}
		}
	}
	return eros;
}

Mat gaussian(Mat m){
	Mat gaus(m.rows, m.cols, CV_8UC1, Scalar(0));
	for (int x = 1; x < m.cols - 1; x++){
		for (int y = 1; y < m.rows - 1; y++){
			gaus.at<uchar>(y, x) = 0.06*(m.at<uchar>(y - 1, x - 1) + m.at<uchar>(y - 1, x + 1) + m.at<uchar>(y + 1, x - 1) + m.at<uchar>(y + 1, x + 1)) 
				+ 0.098*(m.at<uchar>(y - 1, x) + m.at<uchar>(y + 1, x) + m.at<uchar>(y, x - 1) + m.at<uchar>(y, x + 1)) + 0.162*(m.at<uchar>(y, x));
		} 
	}
	return gaus;
}

 //blob detection using recurssion. there is some error
/*
int detect_blob(Mat m, int x, int y, int count, Mat counter,Mat err){
	if (x<=1 || y <=1 || x>=( m.cols-3)|| y >= (m.rows-3))
		return 1;
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if ((counter.at<uchar>(y - 1 + j, x - 1 + i) == 0 )&& (m.at<uchar>(y-1+j, x-1+i) == 255)){
				counter.at<uchar>(y-1+j, x-1+i) = count; 
				
				
				for (int x = 0; x < m.cols ; x++){
					for (int y = 0; y < m.rows ; y++){
						if ((counter.at<uchar>(y, x) != 0)){
							err.at<uchar>(y, x) = (m.at<uchar>(y, x)) / (counter.at<uchar>(y, x));
						}
						else
							err.at<uchar>(y, x) = 0;
					}
				}
				imshow("blob", err);
				
			
				detect_blob(m, x - 1 + i, y - 1 + j, count, counter, err);
				
			}
			
		}
	}
	return 1;
}
void blob(Mat m)
{
	Mat err(m.rows, m.cols, CV_8UC1, Scalar(0));
	Mat counter(m.rows, m.cols, CV_8UC1, Scalar(0));
	int count = 0;
	for (int x = 5; x < m.cols-5; x++){
		for (int y = 5; y < m.rows-5; y++){
			if ((m.at<uchar>(y, x) == 255)&&(counter.at<uchar>(y,x)==0)){
				count=count+1;
				counter.at<uchar>(y, x) = count;
				cout << count << endl << endl<<x<<endl<<y<<endl<<endl;
				detect_blob(m, x, y,count,counter,err);
			}
		}
	}

	for (int x = 1; x < m.cols - 1; x++){
		for (int y = 1; y < m.rows - 1; y++){
			if ((counter.at<uchar>(y, x) != 0)){
				m.at<uchar>(y, x) = (m.at<uchar>(y, x)) / (counter.at<uchar>(y, x));
			}
		}
	}
	
	//return counter;
}
*/

//blob detection using queue
				
void blob_detect(Mat m, int count, int x, int y, Mat counter){
	queue<Point> q; 
	Point p,p1;
	p.x = x;
	p.y = y;
	q.push(p);
	do{
		p = q.front();
		q.pop();
		x = p.x;
		y = p.y;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (m.at<uchar>(y + j, x + i) == 255 && counter.at<uchar>(y + j, x + i) == 0)
				{
					p1.x = x + i;
					p1.y = y + j;
					counter.at<uchar>(p1.y, p1.x) = count;
					q.push(p1);
					
				}

			}
		}
		
	} while (q.empty() !=1);
	
}
void bob_queue(Mat m){
	Mat   counter(m.rows, m.cols, CV_8UC1, Scalar(0));
	Point p;
	int count = 0;
	for (int x = 0; x < m.cols; x++){
		for (int y = 0; y < m.rows; y++){
			if (counter.at< uchar>(y, x) == 0 && m.at < uchar>(y, x) == 255){

				blob_detect(m, ++count, x, y, counter);
			}
		}
	}
	for (int x = 0; x < m.cols; x++){
		for (int y = 0; y < m.rows; y++){
			if (counter.at < uchar>(y, x) == 0){

				m.at<uchar>(y, x) = m.at<uchar>(y, x);
			}
			else
				m.at<uchar>(y, x) = m.at<uchar>(y, x) / counter.at<uchar>(y, x);
		}
	}

}

//line detection using hough diag
void plot(Mat counter, int x, int y, int max_r){
	int r;
	for (int i = -90; i < 90; i++){
		r = x*cos(i*pi/180) + y*sin(i*pi/180);
		
			if ((counter.at<uchar>(r+max_r, i+90) < 256))
				counter.at<uchar>(r+max_r, i+90)++;
	}
}
void plot_line(Mat lines, Mat m, int theta, int r){
	int y;
	for (int x = 0; x < m.cols; x++){
		y = (r - x*cos(theta*pi / 180)) / sin(theta*pi / 180);
		if (y<m.rows&&y>0)
			if (m.at<uchar>(y, x) == 255)
				lines.at<uchar>(y, x) = 255;
	}
}
void line_detection(Mat m,int thres){
	Mat lines(m.rows, m.cols, CV_8UC1, Scalar(0));
	int r = sqrt((m.cols)*m.cols + (m.rows)*m.rows);
	Mat counter(r*2, 180, CV_8UC1, Scalar(0));

	for (int x = 0; x < m.cols; x++)
	{
		for (int y = 0; y < m.rows; y++){
			if (m.at<uchar>(y, x) == 255){
				plot(counter, x, y,r);
			}
		}
	}
	imshow("blob", counter);
	
	for (int x = 0; x < 180; x++){
		for (int y = 0; y < 2*r; y++){
			if (counter.at<uchar>(y, x)>thres){
				plot_line(lines, m, x-90, y-r);
			}
		}
	}
	
	imshow("thres", lines);
}


//blob detection main
void main(){
	Mat image;
	int thres = 55; int a = 2;
	image = imread("V:\\line.jpg", CV_LOAD_IMAGE_COLOR);
	image = black_white(image, 100);
	namedWindow("original", WINDOW_AUTOSIZE);
	namedWindow("blob", WINDOW_NORMAL);
	namedWindow("thres", WINDOW_AUTOSIZE);

	imshow("original", image);
	createTrackbar("thres", "thres", &thres, 200);
	while(a != 27){
		line_detection(image, thres);
		a = waitKey(50);
	}
	//imshow("blob", image);
	//imwrite("blobimage.jpg", image);
}

//gaussian filter, mean, median and sobel filter
/* filters and edges
void maain(){
	Mat m = imread("V:\\images.jpg", CV_LOAD_IMAGE_COLOR);
	//tempclass();
	if (m.data)
	{	
		int  thres = 40;
		char wait = 3;
		//cout << "Enter threshold for black and white image:  ";
		//cin >> thres;
		namedWindow("original", WINDOW_NORMAL);
		imshow("original", m);
		Mat gray;
		namedWindow("grayscale", WINDOW_NORMAL);
		gray = grayscale_avg(m);
		imshow("grayscale", gray);
		namedWindow("edge", WINDOW_NORMAL);

		Mat returned;
		returned = edge_detection(gray,thres);
		imshow("edge", returned);

		Mat noise = dilation(returned);
		namedWindow("dilation", WINDOW_AUTOSIZE);
		imshow("dilation", noise);

		noise = erosion(noise);
		namedWindow("erosion", WINDOW_AUTOSIZE);
		imshow("erosion", noise);

		waitKey(0);
		//Mat returned = histogram(m,&thres);
		//namedWindow("disp", WINDOW_AUTOSIZE);
		//imshow("disp", returned);
		//trackbar
		//createTrackbar("EDGE Threshold:  ", "edge", &thres, 200);
		while (wait != 27){
			returned = edge_detection(gray, thres);
			imshow("edge", returned);
			wait = waitKey(20);
			
		}
	}

	else{
		cout << "image not found" << endl << endl;
		int m;
		_getch();
	}

}
*/
/*
//video capture gaussian blur and canny
void main(){

	VideoCapture v(0);
	Mat frame;
	//Mat returned;
	int c = 1,thres=30,thresb=30;
	int a = 0;
	//namedWindow("videocapture", WINDOW_AUTOSIZE);
	int lowthres = 10;
	namedWindow("videocapturegauss", WINDOW_AUTOSIZE);
	createTrackbar("lowThres", "videocapturegauss", &lowthres, 100);
	while (a!=27)
	{	
		v >> frame;
		frame = grayscale_avg(frame);
		frame = gaussian(frame);
		//imshow("videocapture", returned);
		Canny(frame,frame,lowthres,lowthres*3,3);
		imshow("videocapturegauss", frame);
		a=waitKey(40);
	}
}
*/
void hsvdetection(Mat m,Mat hls, int h,int tol){
	for (int x = 0; x < m.cols; x++){
		for (int y = 0; y < m.rows; y++){
			if (hls.at<Vec3b>(y, x)[0]>(h - tol) && hls.at<Vec3b>(y, x)[0] < (h + tol))
			{
				m.at<Vec3b>(y, x)[0] =255;
				m.at<Vec3b>(y, x)[1] =255;
				m.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}
}
/*
#define hs hls.at<Vec3b>(0,0)
void main(){
	Mat frame = imread("V:\\smoking.jpg", CV_LOAD_IMAGE_COLOR);
	Mat  hls(frame.rows, frame.cols, CV_8UC3, Scalar(0));
	int h=95,a=0,tol=10;
//	Mat frame1(frame.cols, frame.rows, CV_8UC1);
	cvtColor(frame, hls,CV_BGR2HLS_FULL);
	namedWindow("hls", WINDOW_AUTOSIZE);
	//createTrackbar("hue value: ", "hsv", &h, 180);
	namedWindow("original", WINDOW_AUTOSIZE);
	imshow("original", frame);
	hsvdetection(frame, hls, 100, 10);
	imshow("hls", frame);
	waitKey(0);
	a = hs[0];
	int b = hs[1];
	int c = hs[2];
	cout << a<<endl<<b<<endl<<c<<endl;
	
}
*/