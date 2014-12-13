#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void insertion_sort (int arr[], int length)
{
	int j, temp;
		
	for (int i = i; i < length; i++){
		j = i;
		
		while (j > 0 && arr[j] < arr[j-1]){
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
			  }
		}
}
Mat convert_to_grayscale(Mat image,float b=0.56,float g=0.33, float r=0.11)
{
		Mat gray(image.rows,image.cols,CV_8UC1,Scalar(0));
		int i,j;
		for(i=0;i<image.rows;i++)
			{
				for(j=0;j<image.cols;j++)
					{
						gray.at<uchar>(i,j)=(uchar)(image.at<Vec3b>(i,j)[0]*b+image.at<Vec3b>(i,j)[1]*g+image.at<Vec3b>(i,j)[2]*r);
					}
			}
		return gray;
		
}
int kernel_check(Mat image,int x,int y,int threshold)
{
	int i=x-1,j,min=255,max=0;
	for(;i<x+2;i++)
	{
		for(j=y-1;j<y+2;j++)
		{
			
				if(image.at<uchar>(i,j)>max)max=image.at<uchar>(i,j);
				if(image.at<uchar>(i,j)<min)min=image.at<uchar>(i,j);
			
			
		}
	}
	if((max-min)>threshold-1)return 1;
	return 0;

}

Mat primitive_edge_detector(Mat image,int threshold=50)
{
	int i,j;
	Mat out(image.rows,image.cols,CV_8UC1,Scalar(255));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
			if(kernel_check(image,i,j,threshold))
				out.at<uchar>(i,j)=0;
		}
	}
	return out;
}
void primitive_edge_detector_trackbar(Mat source)
{
	
	int threshold=0;
	namedWindow("source",WINDOW_AUTOSIZE);
	imshow("source",source);
	namedWindow("edge",WINDOW_AUTOSIZE);
	createTrackbar("Threshold","edge",&threshold,255);
	while(1)
	{
		Mat out=primitive_edge_detector(source,threshold);
		imshow("edge",out);
		char a=waitKey(33);
		if(a==27)break;
	}
	
int delta_x(Mat img, int x, int y)
{
	int sum=0,k;
	for(k=0;k<3;k++)
	{
		sum+=img.at<uchar>(x+k,y+1)-img.at<uchar>(x+k,y-1);
	}
	return sum;
}

int delta_y(Mat img, int x, int y)
{
	int sum=0,k;
	for(k=0;k<3;k++)
	{
		sum+=img.at<uchar>(x+1,y+k)-img.at<uchar>(x-1,y+k);
	}
	return sum;
}
int sobel_delta_x(Mat img, int x, int y)
{
	int sum=0,k;
	for(k=0;k<3;k++)
	{
		sum+=img.at<uchar>(x+k,y+1)-img.at<uchar>(x+k,y-1)+img.at<uchar>(x,y+1)-img.at<uchar>(x,y-1);
	}
	return sum;
}

int sobel_delta_y(Mat img, int x, int y)
{
	int sum=0,k;
	for(k=0;k<3;k++)
	{
		sum+=img.at<uchar>(x+1,y+k)-img.at<uchar>(x-1,y+k)+img.at<uchar>(x+1,y)-img.at<uchar>(x-1,y);
	}
	return sum;
}


Mat prewitt_edge_detector(Mat image)
{
	int i,j,val;
	Mat out(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
				val=sqrt(delta_x(image,i,j)*delta_x(image,i,j)+delta_y(image,i,j)*delta_y(image,i,j));
				if(val<256)
					out.at<uchar>(i,j)=val;
			    else 
			    	out.at<uchar>(i,j)=255;
		}
	}
	return out;

}

Mat prewitt_edge_detector_x(Mat image)
{
	int i,j,val;
	Mat out(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
				val=delta_x(image,i,j);
				if(val<256)
					out.at<uchar>(i,j)=val;
			    else 
			    	out.at<uchar>(i,j)=255;
		}
	}
	return out;

}

Mat prewitt_edge_detector_y(Mat image)
{
	int i,j,val;
	Mat out(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
				val=delta_y(image,i,j);
				if(val<256)
					out.at<uchar>(i,j)=val;
			    else 
			    	out.at<uchar>(i,j)=255;
		}
	}
	return out;

}
Mat dilate(Mat source,int k)
{
	int i,j,x,y,b,w;
	Mat image(source.rows,source.cols,CV_8UC1,Scalar(255));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
			b=0,w=0;
			for(x=i-(k/2);x<=i+(k/2);x++)
			{
				for(y=j-(k/2);y<=j+(k/2);y++)
				{
					if(source.at<uchar>(x,y)==0)b++;
					else w++;
				}
			}
			if(b>w && (b!=0&&w!=0)) image.at<uchar>(i,j)=0;
			else if(b<w && (b!=0&&w!=0) ) image.at<uchar>(i,j)=255;
			else if(b==0)image.at<uchar>(i,j)=255;
			else if(w==0) image.at<uchar>(i,j)=0;
		}
	}
	return image;
}

Mat erode(Mat source,int k)
{
	int i,j,x,y,b,w;
	Mat image(source.rows,source.cols,CV_8UC1,Scalar(0));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
			b=0,w=0;
			for(x=i-(k/2);x<=i+(k/2);x++)
			{
				for(y=j-(k/2);y<=j+(k/2);y++)
				{
					if(source.at<uchar>(x,y)==0)b++;
					else w++;
				}
			}
			if(b<w && (b!=0&&w!=0)) image.at<uchar>(i,j)=0;
			else if(b>w && (b!=0&&w!=0) ) image.at<uchar>(i,j)=255;
			else if(b==0)image.at<uchar>(i,j)=255;
			else if(w==0) image.at<uchar>(i,j)=0;
		}
	}
	return image;
}

Mat noise_reduction(Mat image,int threshold,int k)
{
	Mat out=primitive_edge_detector(image,threshold);
	Mat out1=dilate(out,k);
	Mat out2=erode(out1,k);
	return out2;

}
void noise_reduction_trackbar(Mat source)
{
	int threshold=0;
	int k=3;
	namedWindow("source",WINDOW_AUTOSIZE);
	imshow("source",source);
	namedWindow("edge",WINDOW_AUTOSIZE);
	createTrackbar("Threshold","edge",&threshold,255);
	createTrackbar("Kernel ","edge",&k,15);
	while(1)
	{
		Mat out=noise_reduction(source,threshold,k);
		imshow("edge",out);
		char a=waitKey(33);
		if(a==27)break;
	}
}
Mat average_blur(Mat source)
{
		int i,j,x,y,sum;
		Mat image(source.rows,source.cols,CV_8UC1,Scalar(255));
		for(i=1;i<image.rows-1;i++)
		{
			for(j=1;j<image.cols-1;j++)
			{sum=0;
				for(x=i-1;x<=i+1;x++)
				{
					for(y=j-1;y<=j+1;y++)
					{
						sum+=source.at<uchar>(x,y);
						
					}
				}
				image.at<uchar>(i,j)=sum/9;
			}
		}
		return image;
}
Mat median_blur(Mat source)
{
	int i,j,x,y,c,ele[9];
	Mat image(source.rows,source.cols,CV_8UC1,Scalar(255));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{c=0;
			for(x=i-1;x<=i+1;x++)
			{
				for(y=j-1;y<=j+1;y++)
				{
					ele[c++]=source.at<uchar>(x,y);	
				}
			}
			insertion_sort(ele,9);
			image.at<uchar>(i,j)=ele[4];
		}
	}
	return image;
}
Mat gaussian_blur(Mat source)
{
	double kern[]={0.06,0.098,0.06,0.098,0.162,0.098,0.06,0.098,0.06};
	int i,j,x,y,c;
	double sum;
	Mat image(source.rows,source.cols,CV_8UC1,Scalar(255));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{c=0,sum=0;
			for(x=i-1;x<=i+1;x++)
			{
				for(y=j-1;y<=j+1;y++)
				{
					sum+=kern[c++]*source.at<uchar>(x,y);	
				}
			}
		image.at<uchar>(i,j)=sum;
		}
	}
	return image;
}

Mat sobel_edge_detector(Mat image) 
{
	int i,j,val;
	Mat out(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
				val=sqrt(sobel_delta_x(image,i,j)*sobel_delta_x(image,i,j)+sobel_delta_y(image,i,j)*sobel_delta_y(image,i,j));
				if(val<256)
					out.at<uchar>(i,j)=val;
			    else 
			    	out.at<uchar>(i,j)=255;
		}
	}
	return out;

}
void canny_trackbar(Mat image, Mat out)
{
	int lower=0,upper=255;
	namedWindow("source",WINDOW_AUTOSIZE);
	imshow("source",image);
	namedWindow("canny",WINDOW_AUTOSIZE);
	createTrackbar("Upper","canny",&upper,255);
	createTrackbar("Lower","canny",&lower,255);
	while(1&&lower<upper)
	{
		Canny(image,out,lower,upper,3);
		imshow("canny",out);
		char a=waitKey(33);
		if(a==27)break;
	}
}
int main()
{

	Mat source=imread("lena.png");
	Mat image=convert_to_grayscale(source);
	//noise_reduction_trackbar(image);
	Mat out;
	canny_trackbar(image,out);
	/*namedWindow("source",WINDOW_AUTOSIZE);
	imshow("source",image);
	namedWindow("out",WINDOW_AUTOSIZE);
	imshow("out",out);
	waitKey(0);*/
	

return(0);	
}

}