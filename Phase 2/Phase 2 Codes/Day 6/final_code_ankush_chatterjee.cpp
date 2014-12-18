#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"


#include <iostream>
#include <stdio.h>
#include <math.h>
#include <queue>

using namespace std;
using namespace cv;

int notcrossed2(Mat image,int top,int bottom,int param=80) //sees if a wall is up front
{
	int i,j;
	int count_white=0,count=0;
	
		for(j=0;j<image.cols;j++)
		{
			for(i=top;i<=bottom;i++)
			{
				if(image.at<uchar>(i,j)==255)
					{count_white++;
						break;
					}	
			}
		}
		if((100*count_white)/image.cols>param)
			return 0;

		return 1;

}
int intelligence_module(Mat image,Point centroid_lane,Point centroid_blob,int percentage)//one param here
{
	int param=40;
	int top=image.rows*(100-percentage)/100.0;
	int left1=(int)(image.cols*0)/9.0,left2=(int)(image.cols*3)/9.0,right2=(int)(image.cols*6)/9.0,right1=(int)(image.cols*9)/9.0;
	if(notcrossed2(image,top,image.rows-1))
	{
		if((centroid_blob.y!=image.rows-1))
		{

			
				if(centroid_blob.x>left2&&centroid_blob.x<right2)
				{
					return 8;

				}
				if(centroid_blob.x>left1&&centroid_blob.x<left2)
					return 4;
				if(centroid_blob.x>right2&&centroid_blob.x<right1)
					return 6;
		}
		else if(centroid_blob.y==image.rows-1) return 8;

	}
	else 
	{
		return 79;
	}

			
}

// int intelligence_module3(Mat image,Point centroid_lane,Point centroid_blob,int percentage)//not working
// {
// 	int param=40;
// 	int top=image.rows*(100-percentage)/100.0;
// 	int left1=(int)(image.cols*0)/9.0,left2=(int)(image.cols*3)/9.0,right2=(int)(image.cols*6)/9.0,right1=(int)(image.cols*9)/9.0;
// 	if(notcrossed2(image,top,image.rows-1))
// 	{
// 		if((centroid_blob.y!=image.rows-1)&&centroid_lane.x!=image.rows-1)
// 		{

// 			if(centroid_blob.x>left2&&centroid_blob.x<right2)
// 			{
// 				return 8;
// 				if((centroid_lane.x>centroid_blob.x-param)&&(centroid_lane.x<centroid_blob.x+1)||((centroid_lane.x>centroid_blob.x)&&(centroid_lane.x<centroid_blob.x+param)))
// 					return 8;
// 				if((centroid_lane.x<centroid_blob.x-param))
// 					return 86;
// 				if((centroid_lane.x>centroid_blob.x+param))
// 					return 84;

// 			}
// 			if(centroid_blob.x>left1&&centroid_blob.x<left2)
// 				return 4;
// 			if(centroid_blob.x>right2&&centroid_blob.x<right1)
// 				return 6;
// 		}
// 		else if((centroid_blob.y!=image.rows-1)&&(centroid_lane.x==image.rows-1))
// 		{
// 				if(centroid_blob.x>left2&&centroid_blob.x<right2)
// 				{
// 					return 8;

// 				}
// 				if(centroid_blob.x>left1&&centroid_blob.x<left2)
// 					return 4;
// 				if(centroid_blob.x>right2&&centroid_blob.x<right1)
// 					return 6;
// 		}
// 		else if(centroid_blob.y==image.rows-1) return 8;

// 	}
// 	else 
// 	{
// 		return 79;
// 	}

			
// }

// int intelligence_module2(Mat image,Point centroid_lane,Point centroid_blob,int percentage)//not working
// {
// 	int param=20;
// 	int top=image.rows*(100-percentage)/100.0;
// 	int left1=(int)(image.cols*0)/9.0,left2=(int)(image.cols*3)/9.0,right2=(int)(image.cols*6)/9.0,right1=(int)(image.cols*9)/9.0;
// 	if(not_crossed(image,top,left2,right2))
// 	{
// 		if(centroid_blob.y>5&&centroid_lane.x!=image.rows-1)
// 		{

// 			if(centroid_blob.x>left2&&centroid_blob.x<right2)
// 			{
// 				if((centroid_lane.x>centroid_blob.x-param)&&(centroid_lane.x<centroid_blob.x+1)||((centroid_lane.x>centroid_blob.x)&&(centroid_lane.x<centroid_blob.x+param)))
// 					return 8;
// 				if((centroid_lane.x<centroid_blob.x-param))
// 					return 86;
// 				if((centroid_lane.x>centroid_blob.x+param))
// 					return 84;

// 			}
// 			if(centroid_blob.x>left1&&centroid_blob.x<left2)
// 				return 4;
// 			if(centroid_blob.x>right2&&centroid_blob.x<right1)
// 				return 6;
// 		}
// 		else if(centroid_lane.x<image.rows-1&&not_crossed(image,top,left2,right2))
// 		{
// 				if(centroid_blob.x>left2&&centroid_blob.x<right2)
// 				{
// 					return 8;

// 				}
// 				if(centroid_blob.x>left1&&centroid_blob.x<left2)
// 					return 4;
// 				if(centroid_blob.x>right2&&centroid_blob.x<right1)
// 					return 6;
// 		}
// 	}
// 		else 
// 		{
// 			return 780;
// 		}

			
// 	}
// int intelligence_module4(Mat image,Point centroid_lane,int percentage,int param=20) //not working
// {
// 	int left=image.cols*0.4,right=image.cols*0.6;
// 	int top=image.rows*(100-percentage)/100.0;
// 	int left_line=0,right_line=image.cols-1;
// 	if(not_crossed(image,top,left,right))
// 	{
// 		if((centroid_lane.x>left)&&(centroid_lane.x<right))
// 				return 8; //move forward;
// 		if((centroid_lane.x<left))
// 				return 4; // move left
// 		if((centroid_lane.x>right))
// 				return 6; //move right
// 	}
// 	else
// 	{
// 		while(image.at<uchar>(centroid_lane.y,left_line++)==0);
// 		while(image.at<uchar>(centroid_lane.y,right_line--)==0);
// 		if(left_line<centroid_lane.x-param&&right_line>centroid_lane.x+param)
// 			return 0;
// 		else if(left_line<centroid_lane.x-param)
// 			return 9;
// 		else if(right_line>centroid_lane.x+param)
// 			return 7;


// 	}
	
// }

Mat red_detector(Mat image,int h_tolerance,int s,int l)
{
	Mat hsv;
	cvtColor(image,hsv,CV_BGR2HLS);

	Mat binary(image.rows,image.cols,CV_8UC1,Scalar(0));
	int i,j;
	for(i=0;i<image.rows;i++)
	{
		for(j=0;j<image.cols;j++)
		{
			if(((((int)hsv.at<Vec3b>(i,j)[0])>180-h_tolerance)||(((int)hsv.at<Vec3b>(i,j)[0])<h_tolerance))&&(((int)hsv.at<Vec3b>(i,j)[1])>l)&&(((int)hsv.at<Vec3b>(i,j)[2])>s) )
				binary.at<uchar>(i,j)=255;
		}
	}
	return binary;
}
Mat line_detector(Mat image,int percentage,double rho=1,double theta=1,int threshold=10,double minLineLength=0,double maxLineGap=5)
{
	int i,j;
	int c=image.cols,r=(int)(image.rows*percentage/100);
	Mat out(image.rows,image.cols,CV_8UC1,Scalar(0));
	
	for(i=image.rows-1;i>image.rows-r-1;i--)
	{
		for(j=0;j<c;j++)
		{
			out.at<uchar>(i,j)=image.at<uchar>(i,j);
		}
	}
	vector<Vec4i> lines;
	Mat final(out.rows,out.cols,CV_8UC1,Scalar(0));
	HoughLinesP(out,lines,rho,theta,threshold,minLineLength,maxLineGap);
	 for( size_t i = 0; i < lines.size(); i++ )
    {
        line( final, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(255), 4, 8 );
    }
	
	
	return final;

}
Point find_centroid(Mat image)
{
	int i,j;
	int x_sum=0,y_sum=0,count=0;
	for(i=0;i<image.rows;i++)
	{
		for(j=0;j<image.cols;j++)
		{
			if(image.at<uchar>(i,j)==255)
			{
				x_sum+=j;
				y_sum+=i;
				count++;
			}
		}
	}
	Point p(image.cols/2,image.rows-1);
	//cout<<x_sum<<" "<<y_sum<<" "<<count<<endl;
	
	if(count)
	{
			p.x=(int)(x_sum/count);
			p.y=(int)(y_sum/count);
	}

	return p;

}
void control_module(int key)  //takes commands from the intelligence  module and converts that to final command to arduino
{
	switch(key)
	{
		case 8 : cout<<"ww"<<endl;
				break;
		case 4 : cout<<"a"<<endl;
				break;
		case 5: cout<<"sssds"<<endl;
				break;
		case 6 : cout<<"dd"<<endl;
				break;
		case 7: cout<<"wwwwwwwwwwwwwwwwwwwwwwwaaaaaaaa"<<endl;
				break;				
		case 9 : cout<<"wwwwwwwwwwwwwwwwwwwwwwdddddddd"<<endl;
				break;
		case 86 :cout<<"wwwd"<<endl;
				break;
		case 84 :cout<<"wwwa"<<endl;
				break;
		case 0: break;		
	}
}
Mat plot_centroid(Mat image,Point lane,Point blob)
{
	circle(image,blob,5,Scalar(0,0,255));
	
	circle(image,lane,5,Scalar(0,255,0));
	return image;

}
void input_video()
{
	int upper=255,lower=45,s=100,l=50,h=10,a,percentage=30,theta=1,threshold=2,minLineLength=1,maxLineGap=10,top;
	Mat frame;
	int key,count_zero=0;
	VideoCapture v(1);
	if(!v.isOpened())
	{
		cout<<"Cant load video"<<endl;
		return;
	}
	namedWindow("video_feed",WINDOW_NORMAL);
	namedWindow("canny",WINDOW_AUTOSIZE);
	namedWindow("centroid",WINDOW_NORMAL);
	createTrackbar("Upper","canny",&upper,255);
	createTrackbar("Lower","canny",&lower,255);
	createTrackbar("percent","canny",&percentage,100);
	createTrackbar("threshold","canny",&threshold,500);
	createTrackbar("minLineLength","canny",&minLineLength,100);
	createTrackbar("maxLineGap","canny",&maxLineGap,20);
	Mat canny,sobel,red;
	Point centroid_lane,centroid_blob;
	while(1)
	{
		
		v>>frame;
		imshow("video_feed",frame);
		Canny(frame,canny,lower,upper,3);
		Mat lines=line_detector(canny,percentage,1,1,threshold,minLineLength,maxLineGap);
		imshow("canny",lines);
		red=red_detector(frame,h,s,l);
		imshow("red",red);
		centroid_lane=find_centroid(lines);
		centroid_blob=find_centroid(red);
		Mat centroid(frame.rows,frame.cols,CV_8UC3,Scalar(0,0,0));
		centroid=plot_centroid(centroid,centroid_lane,centroid_blob);
		imshow("centroid",centroid);
		key=intelligence_module(lines,centroid_lane,centroid_blob,percentage); //returns command about what to do next

		int count_end=0;
		top=lines.rows*(100-percentage)/100;
		int left2=(int)(lines.cols*3)/9.0,right2=(int)(lines.cols*6)/9.0;
		if(key==79) // special case encountered where it finds a wall right in front of it
		{
			count_end=0;
			cout<<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwaaaaaaaaaaaaaaaa"<<endl;
			v>>frame;
			
			//Gaussuan blur here
			imshow("video_feed",frame);
			Canny(frame,canny,lower,upper,3);
			Mat lines=line_detector(canny,percentage,1,1,threshold,minLineLength,maxLineGap);

			imshow("canny",lines);

			red=red_detector(frame,h,s,l);
			imshow("red",red);
			centroid_lane=find_centroid(lines);
			centroid_blob=find_centroid(red);
			Mat centroid(frame.rows,frame.cols,CV_8UC3,Scalar(0,0,0));
			centroid=plot_centroid(centroid,centroid_lane,centroid_blob);
			imshow("centroid",centroid);

			if(centroid_blob.y!=lines.rows-1)
			{
				break;
			}	
			else if(centroid_blob.y==lines.rows-1&&notcrossed2(lines,top,lines.rows-10))
			{
				while(notcrossed2(lines,top,lines.rows-10))
				{
					cout<<"w"<<endl;
				}
				count_end++;
				key=80;

			}
		}

		if(key==80)  //case where  it finds a second wall
		{
			cout<<"dddddddddddddddddddddddddddddd"<<endl;
			v>>frame;
			imshow("video_feed",frame);
			Canny(frame,canny,lower,upper,3);
			Mat lines=line_detector(canny,percentage,1,1,threshold,minLineLength,maxLineGap);

			imshow("canny",lines);

			red=red_detector(frame,h,s,l);
			imshow("red",red);
			centroid_lane=find_centroid(lines);
			centroid_blob=find_centroid(red);
			Mat centroid(frame.rows,frame.cols,CV_8UC3,Scalar(0,0,0));
			centroid=plot_centroid(centroid,centroid_lane,centroid_blob);
			imshow("centroid",centroid);
			if(centroid_blob.y!=lines.rows-1)
			{
				cout<<"wwawd"<<endl;
				key =8;
				break;
			}	
			else if(centroid_blob.y==lines.rows-1&&notcrossed2(lines,top,lines.rows-10))
			{
				while(notcrossed2(lines,top,lines.rows-10))
				{
					cout<<"w"<<endl;
				}
				count_end++;
				
				key=100;
			}


		}
		if(key==100)
		{
			waitKey(0);
			break;
		}
		if(key>0)
		{
			control_module(key); //passes command to control module under normal circumstances
		}	
		else
		{
			count_zero++;
			if(count_zero==2)break; // double checking if 0 is the final command
			else control_module(8);
		}
		a=waitKey(85);
		if(a==27)break;
		
	}
	
}
int main()
{
	input_video();
	return 0;
}