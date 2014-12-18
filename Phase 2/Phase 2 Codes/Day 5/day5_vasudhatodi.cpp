Mat lines(Mat img)
{
	int i, j, k,r;
	Mat x(10000, 181, CV_16UC1, Scalar(0));
	
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) > 100)
			{
				for (k = 0; k < 180; k++)
				{
					r = abs(j*cos((k*CV_PI) / 180) + i*sin((k*CV_PI) / 180));
					//if (x.at<unsigned short>(r, k)>200)
					//{
						//cout << x.at<unsigned short>(r, k)<<endl;
					//}

					x.at<unsigned short>(r,k)++;
				}
			}
		}
	}
	int max = 0, num_of_max = 10;
	i = 0; j = 0;
	for (int m = 0; m < num_of_max; ++m)
	{
		max = 0;
		for (r = 0; r < 10000; r++)
		{
			for (k = 0; k <= 180; k++)
			{

				if (x.at<unsigned short>(r, k)>max)
				{
					max = x.at<unsigned short>(r, k);
					i = r; j = k;
				}
			}
		}
		x.at<unsigned short>(i, j) = 0;
		cout << max << " (" << i << "," << j << ")\n";
	}
	//cout << i << "," << j<<endl;
	//cout << max << endl;
	Mat y(img.rows, img.cols, CV_8UC1,Scalar(0));

	/*for (r = 0; r < 10000; r++)
	{
		for (k = 0; k <= 180; k++)
		{
			if (x.at<unsigned short>(r, k)>max)
			{
				max = x.at<unsigned short>(r, k);
				i = r; j = k;
			}
		}
	}*/

	for (int f = 0; f < img.cols; f++)
	{
		k = (i - f*cos(j*3.14159 / 180)) / sin(j*3.14159 / 180);
		if (k<img.rows && k>-1)
		y.at<uchar>(k,f) = 255;
	}
	return y;
}
int main()
{
	Mat img, x;
	img = imread("abc3.png", CV_LOAD_IMAGE_GRAYSCALE);
	x = lines(img);
	namedWindow("My window", WINDOW_AUTOSIZE);
	imshow("My window", x);
	waitKey(0);
	return 0;
}