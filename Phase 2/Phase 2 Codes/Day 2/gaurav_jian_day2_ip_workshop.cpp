#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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
	
	  //namedWindow("Gray_Scale",CV_WINDOW_AUTOSIZE);
	 //imshow("Gray_Scale",image2);
	//waitKey(0);

}	
void binary_image(Mat image ,Mat image2,int threshold)
{
	int i,j,l,b,t;
	l=image.rows;
	b=image.cols;
	
	gray_scale(image,image2);
	  //cout <<"Enter the threshhold value";
	 //cin >> t;
	//t=100;
	for(i=0;i<l;i++)
		for(j=0;j<b;j++)
			image2.at<uchar>(i,j)>threshold?image2.at<uchar>(i,j)=255:image2.at<uchar>(i,j)=0;

	  //namedWindow("binary_image",CV_WINDOW_AUTOSIZE);
  	 //imshow("binary_image",image2);
	//waitKey(0);

}
void invert_image(Mat image)
{
	int i,j,l,b,t1,t2,t3;
	l=image.rows;
	b=image.cols;
	for(i=0;i<l/2;i++)
	{
		for(j=0;j<b;j++)
		{
			t1=image.at<Vec3b>(i,j)[0];
			t2=image.at<Vec3b>(i,j)[1];
			t3=image.at<Vec3b>(i,j)[2];
			image.at<Vec3b>(i,j)[0]=image.at<Vec3b>(l-i-1,j)[0];
			image.at<Vec3b>(i,j)[1]=image.at<Vec3b>(l-i-1,j)[1];
			image.at<Vec3b>(i,j)[2]=image.at<Vec3b>(l-i-1,j)[2];
			image.at<Vec3b>(l-i-1,j)[0]=t1;
			image.at<Vec3b>(l-i-1,j)[1]=t2;
			image.at<Vec3b>(l-i-1,j)[2]=t3;
		}
	}
	namedWindow("invert_image",CV_WINDOW_AUTOSIZE);
	imshow("invert_image",image);
	waitKey(0);
	/*Mat image2(l,b,CV_8UC3);
	for(i=0;i<l;i++)
	{
		for(j=0;j<b;j++)
		{
			image2.at<Vec3b>(l-i-1,j)[0]=image.at<Vec3b>(i,j)[0];
			image2.at<Vec3b>(l-i-1,j)[1]=image.at<Vec3b>(i,j)[1];
			image2.at<Vec3b>(l-i-1,j)[2]=image.at<Vec3b>(i,j)[2];
		}
	}
	namedWindow("invert_image2",CV_WINDOW_AUTOSIZE);
	imshow("invert_image2",image2);
	waitKey(0);*/

}
int histogram(Mat image,Mat	image2)
{
	int i,j,a[255],l,b,max=0,k,th;
	long int sum=0,fsum=0;
	//float k;
	Mat graph(600,600,CV_8UC1,Scalar(255));
	for(i=0;i<255;i++)
		a[i]=0;

	l=image.rows;
	b=image.cols;

	gray_scale(image,image2);

	for(i=0;i<l;i++)
		for(j=0;j<b;j++)
			a[image2.at<uchar>(i,j)]++;
	max=a[0];
	for(i=1;i<255;i++)
		if(a[i]>max)
			max=a[i];

	k=max/500;

	for(j=0;j<255;j++)
	{
		for(i=0;i<600-a[j]/(k*2);i++)
			graph.at<uchar>(i,j)=255;
		for(i=600-a[j]/(k*2);i<600;i++)
			graph.at<uchar>(i,j)=0;
	}

	namedWindow("Graph",CV_WINDOW_AUTOSIZE);
	imshow("Graph",graph);
	waitKey(0);

	for(i=0;i<255;i++)
		sum+=a[i];
	for(i=0;fsum<sum/2;i++)
		fsum+=a[i];
	th=i-1;
	return th;
}


int main()
{	
	Mat image;
	int l,b,i,j,k,threshold;
	//string fname;
	//cout << "Enter file:";
	//cin >> fname;
	image = imread("/home/gaurav/OpenCV/WWS/gj3.jpg");
	imshow("Old_Window",image);
	waitKey(1000);
	b=image.cols;
	l=image.rows;
	/*for(i=0;i<l;i++)
	{
		for(j=0;j<b;j++)w
		{
			image.at<Vec3b>(i,j)[0]=0;
			image.at<Vec3b>(i,j)[1]=0;
		}
	}*/

	Mat image2(image.rows,image.cols,CV_8UC1);

		    threshold=histogram(image,image2);
		  //cout<<threshold<<"\n";
	     //	gray_scale(image,image2);
	    // binary_image(image ,image2,threshold);
	   //invert_image(image);
	  //namedWindow("My_Window",CV_WINDOW_AUTOSIZE);
	 //imshow("New_Window",image2);
	// waitKey(0);
	/*createTrackbar("threshold","Old_Window",&threshold,255);
	while(1)
	{
		binary_image(image,image2,threshold);
		imshow("Old_Window",image2);
		char a=waitKey(33);
		if(a!= -1)
			break;
	}*/
	return 0;
}