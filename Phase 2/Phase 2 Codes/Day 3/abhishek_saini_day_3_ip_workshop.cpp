#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include<math.h>
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

void edgeDetectionByMatrix(Mat greyImage,Mat edgeImage,int k){
	for(int i=1;i<greyImage.rows-1;i++){
		for(int j=1;j<greyImage.cols-1;j++){
			int max,min;
			max=min=greyImage.at<uchar>(i-1,j-1);
			for(int tempi=i-1;tempi<=i+1;tempi++){
				for(int tempj=j-1;tempj<=j+1;tempj++){
					if(greyImage.at<uchar>(tempi,tempj) > max) max=greyImage.at<uchar>(tempi,tempj);
					if(greyImage.at<uchar>(tempi,tempj) < min) min=greyImage.at<uchar>(tempi,tempj);
				}
			}
			if(max-min > k) edgeImage.at<uchar>(i,j) = 255;
		}
	}
	return ;
}

void edgeDetectionByGradient(Mat greyImage,Mat edgeImage,int x,int y){
	for(int i=1;i<greyImage.rows-1;i++){
		for(int j=1;j<greyImage.cols-1;j++){
			int max,min,dx=0,dy=0,val;
			max=min=greyImage.at<uchar>(i-1,j-1);
			for(int tempi=i-1;tempi<=i+1;tempi++){
				dx=dx+greyImage.at<uchar>(tempi,j+1)-greyImage.at<uchar>(tempi,j-1);
			}
			for(int tempj=j-1;tempj<=j+1;tempj++){
				dy=dy+greyImage.at<uchar>(i+1,tempj)-greyImage.at<uchar>(i-1,tempj);
			}
			if(x==0) dx=0;           /////////if we have to find only x direction gradient
			if(y==0) dy=0;           /////////if we have to find only y direction gradient   
			val=sqrt(dx*dx+dy*dy);
			if(val>255) val=255;
			edgeImage.at<uchar>(i,j)=val;
		}
	}
	return ;
}


void dilateImage(Mat image,Mat dilatedImage){
	for(int i=1;i<image.rows-1;i++){
		for(int j=1;j<image.cols-1;j++){
			int countB=0,countW=0;
			for(int tempi=i-1;tempi<=i+1;tempi++){
				for(int tempj=j-1;tempj<=j+1;tempj++){
					if(image.at<uchar>(tempi,tempj) == 0) countB++;
					else countW++;
				}
			}
			if(countB > countW) dilatedImage.at<uchar>(i,j)=0;
			else dilatedImage.at<uchar>(i,j)=255;
		}
	}
	return ;
}


void eroteImage(Mat dilatedImage,Mat noiselessImage){
	for(int i=1;i<dilatedImage.rows-1;i++){
		for(int j=1;j<dilatedImage.cols-1;j++){
			int countB=0,countW=0;
			for(int tempi=i-1;tempi<=i+1;tempi++){
				for(int tempj=j-1;tempj<=j+1;tempj++){
					if(dilatedImage.at<uchar>(tempi,tempj) == 0) countB++;
					else countW++;
				}
			}
			if(countB < countW ){
				if(countB>0) noiselessImage.at<uchar>(i,j)=0;
				else noiselessImage.at<uchar>(i,j)=255;
			}
			else{
				if(countW>0) noiselessImage.at<uchar>(i,j)=255;
				else noiselessImage.at<uchar>(i,j)=0;
			}
		}
	}
	return ;
}


void noiseReduction(Mat image,Mat noiselessImage){
	Mat dilatedImage(image.rows,image.cols,CV_8UC1,Scalar(0));
	dilateImage(image,dilatedImage);
	/*namedWindow("dilatedWindow",WINDOW_NORMAL);
	imshow("dilatedWindow",dilatedImage);
	waitKey(0);*/
	eroteImage(dilatedImage,noiselessImage);
	return ;
}
			
void meanFilter(Mat image,Mat filteredImage){
	int sum;
	for(int i=1;i<image.rows-1;i++){
		for(int j=1;j<image.cols-1;j++){
			sum=0;
			for(int tempi=i-1;tempi<=i+1;tempi++){
				for(int tempj=j-1;tempj<=j+1;tempj++){
					sum+=image.at<uchar>(tempi,tempj);
				}
			}
			filteredImage.at<uchar>(i,j)=sum/9;
		}
	}
	return ;
}


void merge(int *A,int *B,int *C,int m,int n){
	int i=0,j=0,k=0;
	while(i<m&&j<n){
		if (A[i] < B[j]) C[k++] = A[i++];
		else C[k++] = B[j++];
	}
	while (i<m) C[k++] = A[i++];
	while (j<n) C[k++] = B[j++];
}
 
void sortArray(int *A,int n){
	if(n==1) return;
	int i,j,*B;
	i=n/2;
	B=(int *)malloc(n*sizeof(int));
	sortArray(A,i);
	sortArray(A+i,n-i);
	merge(A,A+i,B,i,n-i);
	for(j=0;j<n;j++) A[j]=B[j];
	free(B);
}



void medianFilter(Mat image,Mat filteredImage){
	int A[9],k;
	for(int i=1;i<image.rows-1;i++){
		for(int j=1;j<image.cols-1;j++){
			k=0;
			for(int tempi=i-1;tempi<=i+1;tempi++){
				for(int tempj=j-1;tempj<=j+1;tempj++){
					A[k]=image.at<uchar>(tempi,tempj);
					k++;
				}
			}
			sortArray(A,9);
			filteredImage.at<uchar>(i,j)=A[4];
		}
	}
	return ;
}


void gaussainFilter(Mat image,Mat filteredImage){
	int sum;
	for(int i=1;i<image.rows-1;i++){
		for(int j=1;j<image.cols-1;j++){
			sum=0;
			for(int tempi=i-1;tempi<=i+1;tempi++){
				for(int tempj=j-1;tempj<=j+1;tempj++){
					if(tempi==i && tempj==j) sum=sum+0.162*image.at<uchar>(tempi,tempj);
					else if(tempi!=i && tempj!=j) sum=sum+0.06*image.at<uchar>(tempi,tempj);
					else sum=sum+0.098*image.at<uchar>(tempi,tempj);
				}
			}
			filteredImage.at<uchar>(i,j)=sum;
		}
	}
	return ;
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
	image=imread("C:\\Users\\Abhishek Saini\\Desktop\\goru.jpg",CV_LOAD_IMAGE_COLOR);
	//namedWindow("MyWindow",WINDOW_NORMAL);
	//imshow("MyWindow",image);
	//waitKey(0);
	

	Mat greyImage(image.rows,image.cols,CV_8UC1);
	copyGray(image,greyImage);
	namedWindow("greyWindow",WINDOW_NORMAL);
	imshow("greyWindow",greyImage);
	waitKey(0);
	
	/*Mat meanFilteredImage(greyImage.rows,greyImage.cols,CV_8UC1,Scalar(255));
	meanFilter(greyImage,meanFilteredImage);
	namedWindow("meanFilteredWindow",WINDOW_NORMAL);
	imshow("meanFilteredWindow",meanFilteredImage);
	waitKey(0);

	Mat medianFilteredImage(greyImage.rows,greyImage.cols,CV_8UC1,Scalar(255));
	medianFilter(greyImage,medianFilteredImage);
	namedWindow("medianFilteredWindow",WINDOW_NORMAL);
	imshow("medianFilteredWindow",medianFilteredImage);
	waitKey(0);

	Mat gaussainFilteredImage(greyImage.rows,greyImage.cols,CV_8UC1,Scalar(255));
	meanFilter(greyImage,gaussainFilteredImage);
	namedWindow("guassainFilteredWindow",WINDOW_NORMAL);
	imshow("guassainFilteredWindow",gaussainFilteredImage);
	waitKey(0);*/

	int upper=50,lower=150;
	namedWindow("cannyWindow",WINDOW_NORMAL);
	createTrackbar("controlLower","cannyWindow",&lower,255);
	createTrackbar("controlUpper","cannyWindow",&upper,255);
	while(1){
		Mat cannyFilteredImage(greyImage.rows,greyImage.cols,CV_8UC1,Scalar(0));
		Canny(greyImage,cannyFilteredImage,upper,lower);
		imshow("cannyWindow",cannyFilteredImage);
		char a=waitKey(33);
		if(a!=-1) break;
	}
	



	/*int x=0,y=0,z=0;
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
	}*/

	/*Mat edgeImage(greyImage.rows,greyImage.cols,CV_8UC1,Scalar(0));
	namedWindow("edgeWindow",WINDOW_NORMAL);
	edgeDetectionByMatrix(greyImage,edgeImage,50);
	imshow("edgeWindow",edgeImage);
	waitKey(0);*/

	/*Mat noiselessImage(greyImage.rows,greyImage.cols,CV_8UC1,Scalar(0));
	noiseReduction(edgeImage,noiselessImage);
	namedWindow("noiselessWindow",WINDOW_NORMAL);
	imshow("noiselessWindow",noiselessImage);
	waitKey(0);*/


	/*createTrackbar("thresholdForEdge","edgeWindow",&k,255);
	while(1){
		Mat edgeImage(greyImage.rows,greyImage.cols,CV_8UC1,Scalar(0));
		edgeDetectionByMatrix(greyImage,edgeImage,k);
		imshow("edgeWindow",edgeImage);
		char a=waitKey(33);
		if(a!=-1) break;
	}*/


	
	/*edgeDetectionByGradient(greyImage,edgeImage,1,1);
	imshow("edgeWindow",edgeImage);
	waitKey(0);*/
	
	/*edgeDetectionByGradient(greyImage,edgeImage,1,0);
	namedWindow("edgeWindowx",WINDOW_NORMAL);
	imshow("edgeWindowx",edgeImage);
	edgeDetectionByGradient(greyImage,edgeImage,0,1);
	namedWindow("edgeWindowy",WINDOW_NORMAL);
	imshow("edgeWindowy",edgeImage);
	waitKey(0);*/

	/*int A[256];
	int i;
	for(i=0;i<256;i++) A[i]=0;
	fillFrequency(greyImage,A);
	showHistogram(A);*/
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