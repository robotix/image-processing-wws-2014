/*Mat binary1(Mat img, int  p,int q,int r)
{
	Mat x(img.rows, img.cols, CV_8UC3);
	int i, j;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (img.at<Vec3b>(i, j)[0] < r)
				x.at<Vec3b>(i, j)[0] = 0;
			else
				x.at<Vec3b>(i, j)[0] = 255;
			if (img.at<Vec3b>(i, j)[1] < q)
				x.at<Vec3b>(i, j)[1] = 0;
			else
				x.at<Vec3b>(i, j)[1] = 255;
			if (img.at<Vec3b>(i, j)[2] < p)
				x.at<Vec3b>(i, j)[2] = 0;
			else
				x.at<Vec3b>(i, j)[2] = 255;
		}
	}
	return x;
}

int main()
{
	int p = 0, q = 0, r = 0;
	Mat img, y;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	createTrackbar("Red", "My window", &p, 255);
	createTrackbar("Green", "My window", &q, 255);
	createTrackbar("Blue", "My window", &r, 255);
	while (1)
	{
		y = binary1(img, p,q,r);
		imshow("My window", y);
		char a = waitKey(33);
		if (a == 27) break;
	}

}*/

/*Mat border(Mat img,int p)
{
	Mat x(img.rows,img.cols,CV_8UC1);
	int i, j, k,l,max,min;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (i == 0 || j == 0 || i == img.rows - 1 || j == img.cols - 1)
				x.at<uchar>(i, j) = 0;
			else
			{
				 max = img.at<uchar>(i, j);
				 min = img.at<uchar>(i, j);
				for (k = i - 1; k <= i + 1; k++)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						if (max<img.at<uchar>(k, l))
							max = img.at<uchar>(k, l);
						if (min>img.at<uchar>(k, l))
							min = img.at<uchar>(k, l);
					}
				}
				if (max - min > p)
					x.at<uchar>(i, j) = 255;
				else
					x.at<uchar>(i, j) = 0;
			}
		}
	}
   return x;
	}*/

/*int main()
{
	
	Mat img;
	int p;
	img =imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x;
	namedWindow("My window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "My window", &p, 255);
	while (1)
	{
		 x = border(image,p);
		imshow("My window", x);
		char a = waitKey(33);
		if (a == 27) break;
	}
	return 0;
}*/

/*Mat border1(Mat img)
{
	Mat z(img.rows, img.cols, CV_8UC1,Scalar(0));
	int i, j, k, l, x, y;
	for (i = 1; i < img.rows-1; i++)
	{
		for (j = 1; j < img.cols-1; j++)
		{
				x = 0;
				y = 0;
				for (k = i - 1; k <= i + 1; k++)
				{
					for (l = j - 1; l <= j + 1; l++)
					{
						y += (k - i)*img.at<uchar>(k, l);
						x += (l - j)*img.at<uchar>(k, l);
					}
				}
				z.at<uchar>(i, j) =(uchar)sqrt((x*x) + (y*y));
				if (z.at<uchar>(i, j) > 255)
					z.at<uchar>(i, j) = 255;
		}
	}
	return z;
}*/

/*int main()
{
	Mat img;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x;
	namedWindow("My window", WINDOW_AUTOSIZE);
		x = border1(image);
		imshow("My window", x);
		waitKey(0);
	return 0;
}*/

/*Mat dilation(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1,Scalar(0));
	int i, j, k, l, b=0,w=0;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			b = 0; w = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (img.at<uchar>(k, l) == 0)
						b++;
					else w++;
				}
			}
			if (b > w)x.at<uchar>(i, j) = 0;
			else x.at<uchar>(i, j) = 255;
		}
	}
	return x;
}*/
/*Mat erosion(Mat img)
{

	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l, b = 0, w = 0;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			b = 0; w = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (img.at<uchar>(k, l) == 0)
						b++;
					else w++;
				}
			}
			if ((b < w||w==0)&&b!=0)x.at<uchar>(i, j) = 0;
			else x.at<uchar>(i, j) = 255;
		}
	}
	return x;
}*/

/*int main()
{
	Mat img;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	namedWindow("My window1", WINDOW_AUTOSIZE);
	namedWindow("My window2", WINDOW_AUTOSIZE);
	image = border(image,25);
	imshow("My window2", image);
	image = dilation(image);
	imshow("My window1", image);
	image = erosion(image);
	imshow("My window", image);
	waitKey(0);
	return 0;
}*/

/*Mat mean(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l,s;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			s = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					s += img.at<uchar>(k, l);
				}
			}
			x.at<uchar>(i, j) = s/9;
		}
	}
	return x;
}*/

/*Mat median(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l,a[9],c,temp;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			c = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					a[c]= img.at<uchar>(k, l);
					c++;
				}
			}
			for (k = 8; k >=0; k--)
			{
				for (l = 0; l < 9 - k-1; l++)
				{
					if (a[l]>a[l + 1])
					{
						temp = a[l];
						a[l] = a[l + 1];
						a[l + 1] = temp;
					}
				}
			}
			x.at<uchar>(i, j) = a[4];
		}
	}
	return x;
}*/

/*Mat guassian(Mat img)
{
	Mat x(img.rows, img.cols, CV_8UC1, Scalar(0));
	int i, j, k, l;
	double temp[3][3] = { 0.06, 0.098, 0.06, 0.098, 0.162, 0.098, 0.06, 0.098, 0.06 };
	double s=0.0;
	for (i = 1; i < img.rows - 1; i++)
	{
		for (j = 1; j < img.cols - 1; j++)
		{
			s = 0;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					s += temp[k - i + 1][l - j + 1] * img.at<uchar>(k, l);
				}
			}
			x.at<uchar>(i, j) = s;
		}
	}
	return x;
}*/

/*int main()
{
	Mat img;
	img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x,y,z;
	namedWindow("My window", WINDOW_AUTOSIZE);
	namedWindow("My window1", WINDOW_AUTOSIZE);
	namedWindow("My window2", WINDOW_AUTOSIZE);
	x = mean(image);
	imshow("My window", x);
	y = median(image);
	imshow("My window1", y);
	z = guassian(image);
	imshow("My window2", z);
	waitKey(0);
	return 0;
}*/

int main()      //canny
{
	int p, q;
	namedWindow("My window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold 1", "My window", &p, 255);
	createTrackbar("Threshold 2", "My window", &q, 255);
	Mat img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
	Mat image = greyscale(img);
	Mat x;
	while (1)
	{
		Canny(image, x, p, q);
		imshow("My window", x);
		char a = waitKey(33);
		if (a == 27) break;
	}
	
	
}