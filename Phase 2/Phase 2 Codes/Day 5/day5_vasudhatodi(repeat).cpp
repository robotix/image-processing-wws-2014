Mat lines(Mat img)
{
	int i, j, k,r;
	Mat x(10000, 181, CV_16UC1, Scalar(0));
	
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) > 200)
			{
				for (k = 0; k < 180; k++)
				{
					r = abs(j*cos((k*CV_PI) / 180) + i*sin((k*CV_PI) / 180));
					x.at<unsigned short>(r,k)++;
				}
			}
		}
	}
	int max = 0;
	i = 0; j = 0;
	{
		max = 0;
		for (r = 0; r < 10000; r++)
		{
			for (k = 0; k <= 180; k++)
			{
				int c = 0;
				for (int a = r - 5; a <= r + 5; a++)
				{
					for (int b = k - 2; b <= k + 2; b++)
					{
						if (a>=0&&b>=0&&a<10000&&b<180)
						c += x.at<unsigned short>(a, b);
					}
				}

				       if (c>max)
				    {
						   max = c;
					  i = r; j = k;
				   }
			}
		}
	}
	Mat z(1500, 181, CV_8UC1, Scalar(0));
	for (k = 0; k < 1500; k++)
	{
		for (r = 0; r <= 180; r++)
		{
			z.at<uchar>(k, r) = x.at<unsigned short>(k, r) * 255 / x.at<unsigned short >(i,j);
		}
	}
	namedWindow("My window1", WINDOW_AUTOSIZE);
	imshow("My window1", z);
	Mat y(img.rows, img.cols, CV_8UC1,Scalar(0));

	for (int f = 0; f < img.cols; f++)
	{
		k = (i - f*cos(j*3.14159 / 180)) / sin(j*3.14159 / 180);
		if (k<img.rows && k>-1)
		y.at<uchar>(k,f) = 255;
	}
	return y;
}
/*int main()
{
	Mat img, x;
	img = imread("abc3.png", CV_LOAD_IMAGE_GRAYSCALE);
	x = lines(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	return 0;
}*/