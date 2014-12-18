int canny_video_trackbar(string inp) //Optimised one
{
	int a;
	int lower=0,upper=255;
	Mat frame;
	Mat out;
	VideoCapture v(inp);
	if(!v.isOpened())
	{
		cout<<"Cant load video"<<endl;
		return(-1);
	}
	namedWindow("video",WINDOW_NORMAL);
	createTrackbar("Upper","video",&upper,255);
	createTrackbar("Lower","video",&lower,255);
	while(lower <upper)
	{
		
		v>>frame;
		Canny(frame,out,lower,upper,3);
		imshow("video",out);
		a=waitKey(33);
		if(a==27)break;
		
	}
	return 0;
}
Mat binary_color_filter(Mat hsv,int hue,int tolerance)
{
	Mat bin(hsv.rows,hsv.cols,CV_8UC1,Scalar(0));
	int i,j;
	for(i=0;i<hsv.rows;i++)
	{
		for(j=0;j<hsv.cols;j++)
		{
			if(((int)hsv.at<Vec3b>(i,j)[0]>(hue-tolerance))&&((int)hsv.at<Vec3b>(i,j)[0]<(hue+tolerance)))
				bin.at<uchar>(i,j)=255;
		}
	}
	return bin;
}
void color_filter_trackbar(Mat image)
{
	Mat hsv;
	int hue=0,tolerance =0,a=0;
	Mat out;
	cvtColor(image,hsv,CV_BGR2HLS);
	namedWindow("source",WINDOW_AUTOSIZE);
	imshow("source",image);
	namedWindow("filter",WINDOW_AUTOSIZE);
	createTrackbar("Hue","filter",&hue,180);
	createTrackbar("Tolerance","filter",&tolerance,100);
	while(1)
	{
		out=binary_color_filter(hsv,hue,tolerance);
		imshow("filter",out);
		a=waitKey(33);
		if(a==27)break;

	}	
}
Mat binary_red_filter(Mat hsv,int hue=0,int tolerance=10)
{
	Mat bin(hsv.rows,hsv.cols,CV_8UC1,Scalar(0));
	int i,j;
	for(i=0;i<hsv.rows;i++)
	{
		for(j=0;j<hsv.cols;j++)
		{
			if((((int)hsv.at<Vec3b>(i,j)[0]<(hue+tolerance)))||(((int)hsv.at<Vec3b>(i,j)[0]>(hue+180-tolerance))))
				bin.at<uchar>(i,j)=255;
		}
	}
	return bin;
}

void bfs(Mat image,Point p,int **visited,int blob_num)
{
	queue<Point> q;
	Point p2;
	q.push(p);
	visited[p.x][p.y]=0;
	int i,j;
	while(!q.empty())
	{
		for(i=p.x-1;i<=p.x+1;i++)
		{
			for(j=p.y-1;j<=p.y+1;j++)
			{
				if(visited[i][j]==-1&&image.at<uchar>(i,j)==255)
				{
					p2.x=i;
					p2.y=j;
					q.push(p2);
					visited[i][j]=0;

				}
			}
		}
		visited[p.x][p.y]=blob_num;
		q.pop();
		p=q.front();
	}
}
Mat blob_detection_bfs(Mat image)
{
 	int blob_num=0;
 	int i,j;
 	
 	//********************Initialising Visited array************************
 	int **visited=new int*[(image.rows)*(sizeof(int *))];
	 cout<<"00here"<<image.rows<<endl;
	for(i=0;i<image.rows;i++)
	{
		visited[i]=new int[image.cols*sizeof(int)];
		for(j=0;j<image.cols;j++)
			{
				 visited[i][j]=-1;
			}	 
	}
	cout<<"Visited initialised"<<endl;
	//**********************************************************************
 	for(i=1;i<image.rows-1;i++)
 	{
 		for(j=1;j<image.cols-1;j++)
 		{
 			if(visited[i][j]==-1&&image.at<uchar>(i,j)==255)
 			{
 				Point p(i,j);
 				bfs(image,p,visited,++blob_num);
 			}
 		}
 	}
 	
 	Mat out(image.rows,image.cols,CV_8UC1,Scalar(0));
 	for(i=1;i<image.rows-1;i++)
 	{
 		for(j=1;j<image.cols-1;j++)
 		{
 			if(visited[i][j]!=-1)
 				out.at<uchar>(i,j)=255/visited[i][j];
 		}
 	}
 	return out;

}
int blob_detection_bfs_color(Mat image)
{
 	int blob_num=0;
 	int i,j;
 	
 	//********************Initialising Visited array************************
 	int **visited=new int*[(image.rows)*(sizeof(int *))];
	
	for(i=0;i<image.rows;i++)
	{
		visited[i]=new int[image.cols*sizeof(int)];
		for(j=0;j<image.cols;j++)
			{
				 visited[i][j]=-1;
			}	 
	}
	
	//**********************************************************************
 	for(i=1;i<image.rows-1;i++)
 	{
 		for(j=1;j<image.cols-1;j++)
 		{
 			if(visited[i][j]==-1&&image.at<uchar>(i,j)==255)
 			{
 				Point p(i,j);
 				bfs(image,p,visited,1);
 				blob_num++;
 			}
 		}
 	}
 	
 	Mat out(image.rows,image.cols,CV_8UC1,Scalar(0));
 	for(i=1;i<image.rows-1;i++)
 	{
 		for(j=1;j<image.cols-1;j++)
 		{
 			if(visited[i][j]!=-1)
 				out.at<uchar>(i,j)=255/visited[i][j];
 		}
 	}
 	return blob_num;
}

void color_detector(Mat image)
{
	Mat hsv;
	cvtColor(image,hsv,CV_BGR2HLS);
	cout<<" NUmber of blue blobs is "<<blob_detection_bfs_color(binary_color_filter(hsv,120,10))<<endl;
	cout<<" NUmber of green blobs is "<<blob_detection_bfs_color(binary_color_filter(hsv,60,10))<<endl;
	cout<<" NUmber of red blobs is "<<blob_detection_bfs_color(binary_red_filter(hsv,0,10))<<endl;//special red filter to handle hue circle wrapping
}
int main()
{
	string inp="illu.webm";
	
	Mat image=imread("green.jpg");
	color_filter_trackbar(image);
	namedWindow("source",WINDOW_NORMAL);
	imshow("source",image);
	waitKey(0);
	return 0;
}