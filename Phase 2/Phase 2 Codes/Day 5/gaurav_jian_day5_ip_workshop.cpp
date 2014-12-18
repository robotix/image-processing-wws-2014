#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <queue>
#define pi 3.142

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

void edge_detection(Mat image, Mat image2,int th)
{
	int i,j,max,min;
	Mat gray_image(image.rows,image.cols,CV_8UC1);
	gray_scale(image,gray_image);
	
	
	for(i=1;i<gray_image.rows-1;i++)
	{
		for(j=1;j<gray_image.cols-1;j++)
		{
			min=max=gray_image.at<uchar>(i,j);
		
			for(int m=i-1;m<=i+1;m++)
			{
				for(int n=j-1;n<=j+1;n++)
				{
					if(min>gray_image.at<uchar>(m,n))
						min=gray_image.at<uchar>(m,n);
					if(max<gray_image.at<uchar>(m,n))
						max=gray_image.at<uchar>(m,n);
				}
			}
			if(max-min>th)
				image2.at<uchar>(i,j)=255;
			//cout<<image2.at<uchar>(i,j);
		}
	}

}

void edge_detection2(Mat image, Mat image2)
{
	int i,j,dx,dy,in;
	Mat gray_image(image.rows,image.cols,CV_8UC1);
	gray_scale(image,gray_image);

	for(i=1;i<gray_image.rows-1;i++)
	{
		for(j=1;j<gray_image.cols-1;j++)
		{
			
			dx=gray_image.at<uchar>(i-1,j+1)+gray_image.at<uchar>(i,j+1)+gray_image.at<uchar>(i+1,j+1)-gray_image.at<uchar>(i-1,j-1)-gray_image.at<uchar>(i,j-1)-gray_image.at<uchar>(i+1,j-1);
				
			dy=gray_image.at<uchar>(i+1,j-1)+gray_image.at<uchar>(i+1,j)+gray_image.at<uchar>(i+1,j+1)-gray_image.at<uchar>(i-1,j-1)-gray_image.at<uchar>(i-1,j)-gray_image.at<uchar>(i-1,j+1);

			in=sqrt(dx*dx+dy*dy);
			//cout<<in<< " ";
			if(in>255)
				in=255;
			image2.at<uchar>(i,j)=in;
			
		}
	}

}

void noise_reduction(Mat image,Mat image2)
{
	int i,j,cw,cb;
	Mat imged(image.rows,image.cols,CV_8UC1);
	edge_detection(image,imged,100);

	namedWindow("Edge_detection",CV_WINDOW_AUTOSIZE);
	imshow("Edge_detection",imged);
	waitKey(0);

	//Dilation
	for(i=1;i<image.rows-1;i++)
	{
		for(j=1;j<image.cols-1;j++)
		{
			cw=cb=0;
			{
				for(int m=i-1;m<=i+1;m++)
				{
					for(int n=j-1;n<j+1;n++)
					{
						if(imged.at<uchar>(m,n)==255)
							cw++;
						else
							cb++;
					}
				}
				if(cw>cb)
					image2.at<uchar>(i,j)=255;
				else
					image2.at<uchar>(i,j)=0;
			}
		}
	}
	namedWindow("Dilation",CV_WINDOW_AUTOSIZE);
	imshow("Dilation",image2);
	waitKey(0);
  //erosion
	for(i=1;i<image2.rows-1;i++)
	{
		for(j=1;j<image2.cols-1;j++)
		{
			cw=cb=0;
			{
				for(int m=i-1;m<=i+1;m++)
				{
					for(int n=j-1;n<j+1;n++)
					{
						if(imged.at<uchar>(m,n)==255)
							cw++;
						else
							cb++;
					}
				}

				if(cw<cb && cw>0)
					image2.at<uchar>(i,j)=255;
				else if(cw>cb && cb>0)
					image2.at<uchar>(i,j)=0;
				else image2.at<uchar>(i,j)= imged.at<uchar>(i,j);
			}
		}
	}
	
}

void Gray_Scale_Mean_Noise_Reduction(Mat image,Mat image2)
{
	 int i,j;
	 Mat imged2(image.rows,image.cols,CV_8UC1);
	 gray_scale(image,imged2);
	 for(i=1;i<image.rows-1;i++)
	 {
	 	for(j=1;j<image.cols;j++)
	 	{
	 		int sum=0;
	 		for(int m=i-1;m<=i+1;m++)
	 		{
	 			for(int n=j-1;n<j+1;n++)
	 			{
	 				sum+=imged2.at<uchar>(m,n);
	 			}
	 		}
	 		image2.at<uchar>(i,j)=sum/9;
	 	}
	 }
	 namedWindow("Noise_ reducted_image_mean",CV_WINDOW_AUTOSIZE);
     imshow("Noise_reducted_image_mean",image2);
      waitKey(0);
}

void sort(int a[],int n)
{
	int min;
	for(int i=0;i<n;i++)
	{
		min=a[i];
		for(int j=i+1;j<n;j++)
			if(min>a[i])
				min=a[i];
		a[i]=min;	
	}
}

void Gray_Scale_Median_Noise_Reduction(Mat image,Mat image2)
{
	int i,j,a[9],k;
	 Mat imged2(image.rows,image.cols,CV_8UC1);
	 gray_scale(image,imged2);
	 for(i=1;i<image.rows-1;i++)
	 {
	 	for(j=1;j<image.cols-1;j++)
	 	{
	 		for(int m=i-1,k=0;m<=i+1;m++)
	 		{
	 			for(int n=j-1;n<j+1;n++)
	 				a[k++]=imged2.at<uchar>(m,n);
	 		}
	 		sort(a,9);
	 		image2.at<uchar>(i,j)=a[4];
	 	}
	 }
	 namedWindow("Noise_ reducted_image_median",CV_WINDOW_AUTOSIZE);
    imshow("Noise_reducted_image_median",image2);
      waitKey(0);
}
void Gray_Scale_gaussian_Noise_Reduction(Mat image,Mat image2)
{
	int i,j;
	 Mat imged2(image.rows,image.cols,CV_8UC1);
	 gray_scale(image,imged2);
	 for(i=1;i<image.rows-1;i++)
	 	for(j=1;j<image.cols-1;j++)
	 		image2.at<uchar>(i,j)=(int)(0.06*imged2.at<uchar>(i-1,j-1)+0.098*imged2.at<uchar>(i-1,j)+0.06*imged2.at<uchar>(i-1,j+1)+0.098*imged2.at<uchar>(i,j-1)+0.062*imged2.at<uchar>(i,j)+0.098*imged2.at<uchar>(i,j+1)+0.06*imged2.at<uchar>(i+1,j-1)+0.098*imged2.at<uchar>(i+1,j)+0.06*imged2.at<uchar>(i+1,j+1));
	 	namedWindow("Noise_ reducted_image_gaussian",CV_WINDOW_AUTOSIZE);
    imshow("Noise_reducted_image_gaussian",image2);
      waitKey(0);

}

void BFS(Mat image, int **a,int k,int i,int j)
{	
	char test;
	cout<<"hi...";
 	queue<Point> q;
 	Point s,pt,t;
 	s.x=i;
 	s.y=j;
 	a[i][j]=k;
 	cout<<q.empty();
 	q.push(s);
 	cout<<q.empty();
 	//cin>>test;
	while(!q.empty())
	{
		for( int m=s.x-1;m<=s.x+1;m++)
		{
			for( int n=s.y-1;n<=s.y+1;n++)
			{
				if(a[m][n]==-1 && image.at<uchar>(m,n)==255)
					{	
						pt.x=m;pt.y=n;q.push(pt);
						cout<< pt.x<<" "<<pt.y<<" *";
						a[m][n]=k; 
						//cin>>test;
					}
			}
		}
		cout<<"here";

		//cin>>test;
	

		q.pop();
			t=q.front();
		cout<<t.x<<" "<<t.y<<" *";
		s=q.front();
		cout<< s.x<<" "<<s.y<<" *";
	}

}

void BLOB_DETECTION(Mat image)
{
	int **a,i,j,k=1,test;
	a=(int **)malloc(355*sizeof(int*));
	for(i=0;i<355;i++)
		a[i]=(int *)malloc(502*sizeof(int));
	for(i=0;i<image.rows;i++)
	{
		for(j=0;j<image.cols;j++)
		{
			a[i][j]=-1;
		}
	}
	/*a[1][2]=a[1][3]=a[2][1]=a[3][1]=1;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(a[i][j]==1)*/

	/*for(i=0;i<image.rows;i++)
		for(j=0;j<image.cols;j++)
			cout<<image.at<uchar>(i,j)<<" ";*/

	for(i=0;i<image.rows;i++)
	{
		for(j=0;j<image.cols;j++)
		{	
			cout<< i <<" "<< j << " *";
			if(image.at<uchar>(i,j)==255 && a[i][j]==-1)
			{	
				cout<< "hi...";
				cout<< "Enter test";
				cin>>test;
				BFS(image,a,k,i,j);
				k++;
				cout<<k;
			}

		}
	}
 Mat bdimage(image.rows,image.cols,CV_8UC1);
 for(i=0;i<image.rows;i++)
 {
 	for(j=0;j<image.cols;j++)
 	{
 		if(a[i][j]==-1)
 		bdimage.at<uchar>(i,j)=0;
 		else if(a[i][j]==1)
 			bdimage.at<uchar>(i,j)=50;
 		else if(a[i][j]==2)
 			bdimage.at<uchar>(i,j)=125;
 		else if(a[i][j]==3)
 			bdimage.at<uchar>(i,j)=200;
 	}
 }
 namedWindow("BLOB_DETECTION",CV_WINDOW_AUTOSIZE);
 imshow("BLOB_DETECTION",bdimage);
 waitKey(0);

}

void line_Dtection(Mat image,Mat nimage ,int threshold )
{
	int i,j,m,n,l,maxr,r,k=0,test;
	float theta;
	maxr=2*(int)sqrt(image.rows*image.rows+image.cols*image.cols)+1;
	int a[maxr][180];
	Point p[1000];
	
	for(i=0;i<maxr;i++)
    	for(j=0;j<180;j++)
    			a[i][j]=0;


	

  	for(i=0;i<image.rows;i++)
  	{
  		for(j=0;j<image.cols;j++)
  		{
  			if(image.at<uchar>(i,j)==255)
  			{
  				for(m=0;m<180;m++)
  				{	

  					theta=m*pi/180;
  					//cout<<theta<<" ";
  					r=(int)(i*cos(theta)+j*sin(theta));

  					r=r+(int)sqrt(image.rows*image.rows+image.cols*image.cols);
  					if(r<maxr)
  						a[r][m]++;
  					
  				}
  			}
  		}
  	}

  	
  	//cout<<"hello....";
    for(i=0,k=0;i<maxr;i++)
    {
    	
    	for(j=0;j<180;j++)
    	{
    		
    		if(a[i][j]>threshold)
    		{
    			p[k].x=i;p[k].y=j;
    			k++;

    		}
    			
    	}
    }
  //  cout <<k<<"\n";
  /*  for(i=0;i<k;i++)
    	cout<<p[i].x <<"**"<<p[i].y<<"\n";
  
   // Mat nimage(image.rows,image.cols,CV_8UC1,Scalar(0));

	//cin>>test;*/


    for(i=0;i<k;i++)
    {	
    	//cout<<"\n";
    	theta=p[i].y*pi/180;
    	//cout<<theta<<" ";
    	//cin>>test;
    	for(int m=0,n=0;m<image.rows;m++)
    	{

    		for( j=0;j<image.cols;j++)
    			
    		
    		{
    			r=(int)(m*cos(theta)+j*sin(theta));
    			r=r+(int)sqrt(image.rows*image.rows+image.cols*image.cols);
    			//cout<<p[i].x <<" "<<r<<" *";
    			
    			if(p[i].x==r){n++;
    				//cin>>test;
    				nimage.at<uchar>(m,j)=255;//cout<<n<<" ";
    			}
    		}
    	}
    }

    

}

int main()
{	
	Mat image;
	int l,b,i,j,k,threshold=100,lower=50,upper=150;
	//string fname;
	//cout << "Enter file:";
	//cin >> fname;
	image = imread("/home/gaurav/OpenCV/WWS/pt4.png");
	//imshow("Old_Window",image);
	//waitKey(0);
	b=image.cols;
	l=image.rows;
	Mat image2(image.rows,image.cols,CV_8UC1);
		binary_image(image,image2,150);
		namedWindow("Old_Window",CV_WINDOW_NORMAL);
		imshow("Old_Window",image);
		waitKey(0);
		namedWindow("line_Dtection",CV_WINDOW_NORMAL);
		createTrackbar("lower","line_Dtection",&threshold,500);
		while(1)
		{	
			Mat image2(image.rows,image.cols,CV_8UC1),nimage(image.rows,image.cols,CV_8UC1,Scalar(0));
			binary_image(image,image2,150);
			line_Dtection(image2,nimage,threshold);
			
    		imshow("line_Dtection",nimage);
    		char a=waitKey(33);
    		if(a!=-1)
    			break;
		}
		

	//BLOB_DETECTION(image2);
	/*for(i=0;i<l;i++)
	{
		for(j=0;j<b;j++)w
		{
			image.at<Vec3b>(i,j)[0]=0;
			image.at<Vec3b>(i,j)[1]=0;
		}
	 }*/

   //Mat image2(image.rows,image.cols,CV_8UC1);
	 //Gray_Scale_Mean_Noise_Reduction( image, image2);
	//Gray_Scale_Median_Noise_Reduction( image, image2);
  // Gray_Scale_gaussian_Noise_Reduction( image, image2);


		   //threshold=histogram(image,image2);
		  //cout<<threshold<<"\n";
	     //	gray_scale(image,image2);
	     	

	    // binary_image(image ,image2,threshold);
	   //invert_image(image);
	  //edge_detection2(image,image2);
	 //noise_reduction(image,image2);
	 //namedWindow("Noise_ reducted_image",CV_WINDOW_AUTOSIZE);
    // imshow("Noise_reducted_image",image2);
   //    waitKey(0);
	//	namedWindow("Vedio_Capture",CV_WINDOW_AUTOSIZE);	
	//createTrackbar("lower","Vedio_Capture",&lower,100);
	//createTrackbar("upper","Vedio_Capture",&upper,200);
	/*while(1)
	{	
		Mat image2(image.rows,image.cols,CV_8UC1,Scalar(0)),cannyimg(image.rows,image.cols,CV_8UC1);
		gray_scale(image,image2);
		Canny(image2,cannyimg,lower,upper);
		imshow("Old_Window",cannyimg);
		char a=waitKey(33);
		if(a!= -1)
			break;
	}*/
		// Vedio capture
	/*	VideoCapture v(0);
		while(1)
		{
			Mat frame;
			v>>frame;
			Mat image2(frame.rows,frame.cols,CV_8UC1,Scalar(0)),cannyimg(frame.rows,frame.cols,CV_8UC1);
		    gray_scale(frame,image2);
			Canny(image2,cannyimg,lower,upper);
			imshow("Vedio_Capture",cannyimg);
			char a=waitKey(33);
			if(a!=-1)
				break;

		}*/



	return 0;
}