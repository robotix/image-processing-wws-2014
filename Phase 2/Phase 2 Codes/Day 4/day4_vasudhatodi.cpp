/*int main()  //video
{
	Mat frame;
	VideoCapture V(0);
	int p = 0, q = 0;
	namedWindow("My window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold 1", "My window", &p, 255);
	createTrackbar("Threshold 2", "My window", &q, 255);
	while (1)
	{
		V >> frame;
		Mat img;
		img = greyscale(frame);
		Canny(img, img, q, p);
		imshow("My window", img);
		char a=waitKey(1);
		if (a == 27)break;
	}
	return 0;
}*/
Mat separate(Mat img, int tol,int h,int s,int l)
{
	int i, j;
	Mat x(img.rows, img.cols, CV_8UC3);
	cvtColor(img, x, CV_BGR2HLS);
	Mat y(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (x.at<Vec3b>(i, j)[0]<h + tol&&x.at<Vec3b>(i, j)[0] > h - tol&&x.at<Vec3b>(i, j)[1]<s + tol&&x.at<Vec3b>(i, j)[1] > s - tol&&x.at<Vec3b>(i, j)[2]<l + tol&&x.at<Vec3b>(i, j)[2] > l - tol)
				y.at<uchar>(i, j) = 255;
		}
	}
	return y;
}

/*int main()
{
int p=0,q=0,r=0,s=0;
Mat img,x,y;
img = imread("dme.jpg", CV_LOAD_IMAGE_COLOR);
namedWindow("My window",CV_WINDOW_FULLSCREEN);
createTrackbar("Threshold", "My window", &p,100);
createTrackbar("Hue", "My window", &p, 240);
createTrackbar("Saturation", "My window", &p, 240);
createTrackbar("Light", "My window", &p, 240);
while (1)
{
	x = separate(img, p,q,r,s);
imshow("My window", x);
char a = waitKey(33);
if (a == 27) break;
}

}*/

Mat blob(Mat img)
{
	queue<Point> q;
	int i, j, c = 1, m, n;
	Mat x(img.rows, img.cols, CV_8SC1, Scalar(-1));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			m = i; n = j;
			if (img.at<uchar>(i, j) == 255 && x.at<char>(i, j) == -1)
			{
				Point temp(m,n);
				q.push(temp);
				x.at<char>(i, j) = c;
				while (!q.empty())
				{
					for (int k = m - 1; k <= m + 1; k++)
					{
						for (int l = n - 1; l <= n + 1; l++)
						{
							if (img.at<uchar>(k, l) == 255 && x.at<char>(k, l) == -1)
							{
								Point temp3(k, l);
								q.push(temp3);
								x.at<char>(k, l) = c;
							}
						}
					}
					
					q.pop();
					if (!q.empty())
					{
						Point temp2;
						temp2 = q.front();
						m = temp2.x;
						n = temp2.y;
					}
				}
				c++;
			}
		}
	}
	Mat y(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (x.at<char>(i, j) != -1)
				y.at<uchar>(i, j) = 50*x.at<char>(i, j);
		}
	}
	return y;

}

int main()
{
	Mat img, x;
	img = imread("abc.png", CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("My window", CV_WINDOW_FULLSCREEN);
	x = blob(img);
	imshow("My window", x);
	waitKey(0);
	return 0;
}