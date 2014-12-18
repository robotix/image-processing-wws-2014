Point shape(Mat img,int p)
{
	vector<vector<Point>> c;
	findContours(img, c, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	vector<Point> app;
	Point a;
	float d;
	for (int i = 0; i < c.size(); i++)
	{
		double epsilon = 0.02*arcLength(c[i], true);
		approxPolyDP(c[i], app, epsilon, true);
		if (app.size() == p)
		{
			a.x = 0;
			a.y = 0;
			for (int j = 0; j < p; j++)
			{
				a.x += (int)app[j].x;
				a.y += (int)app[j].y;
			}
			d = (app[1].x - app[0].x)*(app[1].x - app[0].x) + (app[1].y - app[0].y)*(app[1].y - app[0].y);
			if (d>1000)
			{
				a.x /= p;
				a.y /= p;
			}
			else a.x = a.y = -1;
			cout << "(" << a.x << "," << a.y << ")\n";
			return a;
		}	
		if ((app.size()>4 && p == 0))
		{
			float m1 = (float)(app[1].y - app[0].y) / (float)(app[1].x - app[0].x);
			float m2 = (float)(app[2].y - app[1].y) /(float) (app[2].x - app[1].x);
			a.x =(int) (m1*m2*(app[2].y - app[0].y) + m1*(app[1].x + app[2].x) - m2*(app[1].x + app[0].x)) / (2 * (m1 - m2));
			a.y = (int)((app[0].x + app[1].x) / 2 - a.x) / m1 + (app[0].y + app[1].y) / 2;
			d = (a.x - app[0].x)*(a.x - app[0].x) + (a.y - app[0].y)*(a.y - app[0].y);
			if (d < 1000)
				a.x = a.y = -1;
			cout << "(" << a.x << "," << a.y << ")\n";
			return a;
		}
	}
	a.x = a.y = -1;
	return a;

}
int main()
{
	int k=730;
	int p;
	Mat image;
	image = imread("b1.png", CV_LOAD_IMAGE_COLOR);
	Mat y = separate(image,50,171,240 ,116,50, 50);
	Mat x(y.rows,y.cols,CV_8UC1,Scalar(0));
	x = dilation(y);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	Point a = shape(x,0);
	if (a.y < k&&a.y>=0)
	{
	cout << "(" << a.x << "," << a.y << ")\n";
	
	}
	y= separate(image, 50, 254, 240, 110, 75, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
	 a = shape(x, 4);
	 if (a.y < k&&a.y>=0)
	 {
		 cout << "(" << a.x << "," << a.y << ")\n";
		
	 }
    y = separate(image, 50, 254, 240, 111, 50, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
    a = shape(x, 3);
	if (a.y < k&&a.y>=0)
	{
		cout << "(" << a.x << "," << a.y << ")\n";
	
	}
	y = separate(image, 30, 42, 240, 125, 50, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
	a = shape(x, 4);
	if (a.y < k&&a.y >= 0)
	{
		cout << "(" << a.x << "," << a.y << ")\n";
	
	}
	y = separate(image, 50, 84, 222, 73, 75, 50);
	x = dilation(y);
	imshow("My window", x);
	waitKey(0);
	a = shape(x, 3);
	if (a.y < k&&a.y >= 0)
	{
		cout << "(" << a.x << "," << a.y << ")\n";
		
	}
	getchar();
	return 0;
}

/* int main()
{
	int k = 730;
		int p,i,j;
		Mat image;
		VideoCapture V("PS.mp4");
		namedWindow("My window", WINDOW_AUTOSIZE);
		namedWindow("My window1", WINDOW_AUTOSIZE);
		while (1)
		{
			V >> image;
			Mat y;
			Mat q(image.rows, image.cols, CV_8UC1, Scalar(0));
			Mat x(image.rows, image.cols, CV_8UC1, Scalar(0));
			Point a;
			while (1)
			{
				V >> image;
				y = separate(image, 50, 254, 240, 111, 50, 50);
				x = dilation(y);
				a = shape(x, 4);
				if (a.y < k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<uchar>(i, j) = 255;
							else q.at<uchar>(i, j) = 0;
						}
					}
					imshow("My window1", image);
					imshow("My window", q);
					waitKey(33);
				}
				if (a.y >120||a.y==-1)
					break;
			}
			while (1)
			{
				V >> image;
				y = separate(image, 50, 171, 240, 115, 75, 50);
				x = dilation(y);
				a = shape(x, 0);
				if (a.y < k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<uchar>(i, j) = 255;
							else q.at<uchar>(i, j) = 0;
						}
					}
					imshow("My window1", image);
					imshow("My window", q);
					waitKey(33);
				}
				if (a.y >120||a.y==-1)
					break;
			}
			while (1)
			{
				V >> image;
				y = separate(image, 30, 254, 240, 111, 30, 30);
				x = dilation(y);
				a = shape(x, 3);
				if (a.y < k&&a.y >= 0)
				{
					for (i = 0; i<image.rows; i++)
					{
						for (j = 0; j < image.cols; j++)
						{
							if (i>image.rows - 20 && j > a.x - 80 && j < a.x + 80)
								q.at<uchar>(i, j) = 255;
							else q.at<uchar>(i, j) = 0;
						}
					}
					imshow("My window1", image);
					imshow("My window", q);
					waitKey(33);
				}
				if (a.y >120||a.y==-1)
					break;
			}
			char w=waitKey(1);
			if (w == 27) break;

		}
		return 0;
}*/