#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace cv;


void convertRed(Mat image){
	int i,j;
	for(i=0;i<image.rows;i++){
		for(j=0;j<image.cols;j++){
			image.at<Vec3b>(i,j)[0]=image.at<Vec3b>(i,j)[1]=0;
		}
	}
	return ;
}

void copyGray(Mat image,Mat greyImage){
	int i,j;
	for(i=0;i<greyImage.rows;i++){
		for(j=0;j<greyImage.cols;j++){
			greyImage.at<uchar>(i,j)= image.at<Vec3b>(i,j)[0]*0.56+image.at<Vec3b>(i,j)[1]*0.33+image.at<Vec3b>(i,j)[2]*0.11;
		}
	}
	return ;
}

void copyBinary(Mat image,Mat binaryImage,int k){
	int i,j;
	for(i=0;i<binaryImage.rows;i++){
		for(j=0;j<binaryImage.cols;j++){
			if(image.at<uchar>(i,j)>k) binaryImage.at<uchar>(i,j)=255;
			else binaryImage.at<uchar>(i,j)=0;
		}
	}
	return ;
}

void copyInvert(Mat image,Mat invertImage){
	int i,j;
	for(i=0;i<invertImage.rows;i++){
		for(j=0;j<invertImage.cols;j++){
			invertImage.at<Vec3b>(i,j)[0]=image.at<Vec3b>(image.rows-i-1,j)[0];
			invertImage.at<Vec3b>(i,j)[1]=image.at<Vec3b>(image.rows-i-1,j)[1];
			invertImage.at<Vec3b>(i,j)[2]=image.at<Vec3b>(image.rows-i-1,j)[2];
		}
	}
	return ;
}


void fillFrequency(Mat image,int A[256]){
	int i,j;
	for(i=0;i<image.rows;i++){
		for(j=0;j<image.cols;j++){
			A[image.at<uchar>(i,j)]++;
		}
	}
	return ;
}

void showHistogram(int A[256]){
	Mat histogramImage(600,300,CV_8UC1,Scalar(255));
	int i,j,k;
	for(j=0;j<256;j++){
		i=histogramImage.rows-1;
		k=0;
		while(k<A[j]/100&&(i-k)>0){
			histogramImage.at<uchar>(i-k,j)=0;
			k++;
		}
	}
	namedWindow("histogramWindow",WINDOW_AUTOSIZE);
	imshow("histogramWindow",histogramImage);
	waitKey(0);

	return ;
}

int findThreshold(int A[256],int total){
	int sum;
	int i;
	sum=0;
	i=0;
	while(sum < total/2){
		sum+=A[i];
		i++;
	}
	return i;
}

void printRowsCols(Mat image){
	cout<<"No. of Rows="<<image.rows<<"\nNo. of Columns="<<image.cols<<endl;
	return ;
}

int main()
{
	int k=100;
	/*cout  << "Enter Threshold Value\n";
	cin >> k;*/

	Mat image;
	image=imread("C:\\Users\\Abhishek Saini\\Desktop\\tree.jpg",CV_LOAD_IMAGE_COLOR);
	//namedWindow("MyWindow",WINDOW_NORMAL);
	//imshow("MyWindow",image);
	//waitKey(0);
	
	Mat greyImage(image.rows,image.cols,CV_8UC1);
	//copyGray(image,greyImage);
	namedWindow("greyWindow",WINDOW_NORMAL);
	int x=0,y=0,z=0;
	createTrackbar("controlx","greyWindow",&x,100);
	createTrackbar("controly","greyWindow",&y,100);
	createTrackbar("controlz","greyWindow",&z,100);
	while(1){
		for(int i=0;i<greyImage.rows;i++){
			for(int j=0;j<greyImage.cols;j++){
			greyImage.at<uchar>(i,j)= (image.at<Vec3b>(i,j)[0]*x+image.at<Vec3b>(i,j)[1]*y+image.at<Vec3b>(i,j)[2]*z)/(x+y+z+1);
			}
		}
		imshow("greyWindow",greyImage);
		char a=waitKey(33);
		if(a!=-1) break;
	}

		
	//waitKey(0);

	int A[256];
	int i;
	for(i=0;i<256;i++) A[i]=0;
	fillFrequency(greyImage,A);
	showHistogram(A);
	//k=findThreshold(A,greyImage.rows*greyImage.cols);
	
	

	/*Mat binaryImage(image.rows,image.cols,CV_8UC1);
	namedWindow("binaryWindow",WINDOW_NORMAL);
	createTrackbar("threshold","binaryWindow",&k,255);
	
	while(1){
		copyBinary(greyImage,binaryImage,k);
		imshow("binaryWindow",binaryImage);
		char a=waitKey(33);
		if(a!=-1) break;
	}*/



	/*Mat invertImage(image.rows,image.cols,CV_8UC3);
	copyInvert(image,invertImage);
	namedWindow("invertWindow",WINDOW_NORMAL);
	imshow("invertWindow",invertImage);
	waitKey(0);*/

	return 0;
}