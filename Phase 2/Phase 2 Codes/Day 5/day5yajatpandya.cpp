#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<math.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<queue>
using namespace std;
using namespace cv;
int q, r;
Mat gray(Mat z)
{
	Mat img(z.rows, z.cols, CV_8UC1);
	int a, b;
	for (a = 0; a < z.rows; a++)
	{
		for (b = 0; b < z.cols; b++)
		{
			img.at<uchar>(a, b) = (uchar)(0.56*z.at<Vec3b>(a, b)[0] + 0.33*z.at<Vec3b>(a, b)[1] + 0.11*z.at<Vec3b>(a, b)[2]);
		}
	}
	return img;
}
Mat bin(Mat z, int q)
{
	Mat i(z.rows, z.cols, CV_8UC1);
	int a, b;
	for (a = 0; a < z.rows; a++)
	{
		for (b = 0; b < z.cols; b++)
		{
			if (z.at<uchar>(a, b)>q) i.at<uchar>(a, b) = 255;
			else i.at<uchar>(a, b) = 0;
		}
	}
	return i;
}
/**Mat inv(Mat z)
{
Mat i = z;
int a, b; unsigned char q;
for (a = 0; a < (i.rows)/2; a++)
{
for (b = 0; b < i.cols; b++)
{
q = i.at<uchar>(i.rows - a-1, b);
i.at<uchar>(i.rows - a-1, b) = i.at<uchar>(i.rows, b);
i.at<uchar>(i.rows, b) = q;
}
}
return i;
}**/
Mat holo(Mat image)
{
	int f[256], max;
	int a, b;
	for (a = 0; a < 256; a++)
		f[a] = 0;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			f[image.at<uchar>(a, b)]++;
		}
	}
	max = f[0];
	for (a = 0; a < 256; a++)
	{
		if (f[a]>max)
			max = f[a];
	}
	Mat i((max + 1), 255, CV_8UC1, Scalar(255));
	for (b = 0; b < 255; b++)
	{
		for (a = i.rows - 1; a >= i.rows - (f[b]); a--)
			i.at<uchar>(a, b) = 0;
	}
	return i;
}
Mat holo_im(Mat image)
{
	int f[256];
	int a, b;
	for (a = 0; a < 256; a++)
		f[a] = 0;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			f[image.at<uchar>(a, b)]++;
		}
	}
	int p = 0;
	for (a = 0; a < 256; a++)
	{
		p += f[a];
		if (p >= image.rows*image.cols / 2) break;
	}
	p = a;
	Mat i = image = bin(image, p);
	return i;
}
Mat compl(Mat image, int p, int q, int r)
{
	Mat i(image.rows, image.cols, CV_8UC3);
	int a, b;
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			if ((image.at<Vec3b>(a, b)[0] + p - 255)>255) i.at<Vec3b>(a, b)[0] = 255;
			else if ((image.at<Vec3b>(a, b)[0] + p - 255) < 0) i.at<Vec3b>(a, b)[0] = 0;
			else i.at<Vec3b>(a, b)[0] = image.at<Vec3b>(a, b)[0] + p - 255;
			if ((image.at<Vec3b>(a, b)[1] + q - 255)>255) i.at<Vec3b>(a, b)[1] = 255;
			else if ((image.at<Vec3b>(a, b)[1] + q - 255) < 0) i.at<Vec3b>(a, b)[1] = 0;
			else i.at<Vec3b>(a, b)[1] = image.at<Vec3b>(a, b)[1] + q - 255;
			if ((image.at<Vec3b>(a, b)[2] + r - 255)>255) i.at<Vec3b>(a, b)[2] = 255;
			else if ((image.at<Vec3b>(a, b)[2] + r - 255) < 0) i.at<Vec3b>(a, b)[2] = 0;
			else i.at<Vec3b>(a, b)[2] = image.at<Vec3b>(a, b)[2] + r - 255;
			/**if ((image.at<Vec3b>(a, b)[0] + p) < 0) i.at<Vec3b>(a, b)[0] = 0;
			else i.at<Vec3b>(a, b)[0] = image.at<Vec3b>(a, b)[0] + p;
			if ((image.at<Vec3b>(a, b)[1] + q) < 0) i.at<Vec3b>(a, b)[1] = 0;
			else i.at<Vec3b>(a, b)[1] = image.at<Vec3b>(a, b)[1] + q;
			if ((image.at<Vec3b>(a, b)[2] + r) < 0) i.at<Vec3b>(a, b)[2] = 0;
			else i.at<Vec3b>(a, b)[2] = image.at<Vec3b>(a, b)[2] + r;**/
		}
	}
	return i;
}
Mat naive(Mat image, int t)
{
	Mat im = gray(image);
	int i, j, a, b, min, max;
	Mat im2(image.rows, image.cols, CV_8UC1);
	for (a = 0; a < image.rows; a++)
	{
		for (b = 0; b < image.cols; b++)
		{
			if (a == image.rows - 1 || a == 0 || b == image.cols - 1 || b == 0)
			{
				im2.at<uchar>(a, b) = 0; continue;
			}
			max = min = im.at<uchar>(a - 1, b - 1);
			for (i = (a - 1); i <(a + 2); i++)
			{
				for (j = (b - 1); j <(b + 2); j++)
				{
					if (im.at<uchar>(i, j) > max) max = im.at<uchar>(i, j);
					if (im.at<uchar>(i, j) <= min) min = im.at<uchar>(i, j);
				}
			}
			if ((max - min)>t) im2.at<uchar>(a, b) = 255;
			else im2.at<uchar>(a, b) = 0;
		}
	}
	return im2;
}
Mat prewitt(Mat image)
{
	int a, b, x = 0, y = 0;
	Mat i = gray(image), im(image.rows, image.cols, CV_8UC1);
	for (a = 1; a < i.rows - 1; a++)
	{
		for (b = 1; b < i.cols - 1; b++)
		{
			x = i.at<uchar>(a - 1, b + 1) + i.at<uchar>(a, b + 1) + i.at<uchar>(a + 1, b + 1) - i.at<uchar>(a - 1, b - 1) - i.at<uchar>(a, b - 1) - i.at<uchar>(a + 1, b - 1);
			y = i.at<uchar>(a + 1, b + 1) + i.at<uchar>(a + 1, b) + i.at<uchar>(a + 1, b - 1) - i.at<uchar>(a - 1, b - 1) - i.at<uchar>(a - 1, b) - i.at<uchar>(a - 1, b + 1);
			im.at<uchar>(a, b) = sqrt((x*x) + (y*y));
		}
	}
	return im;
}
Mat dilute(Mat image)
{
	int i, j, a, b, wh, bl;
	Mat im2(image.rows, image.cols, CV_8UC1);
	for (a = 1; a < image.rows - 1; a++)
	{
		for (b = 1; b < image.cols - 1; b++)
		{
			/**if (a == image.rows - 1 || a == 0 || b == image.cols - 1 || b == 0)
			{
			im2.at<uchar>(a, b) = 0; continue;
			}**/
			wh = bl = 0;
			for (i = (a - 1); i <(a + 2); i++)
			{
				for (j = (b - 1); j <(b + 2); j++)
				{
					if (image.at<uchar>(i, j) == 255) wh++;
					else bl++;
				}
			}
			if (wh>bl) im2.at<uchar>(a, b) = 255;
			else im2.at<uchar>(a, b) = 0;
		}
	}
	return im2;
}
Mat erosion(Mat image)
{
	int i, j, a, b, wh, bl;
	Mat im2(image.rows, image.cols, CV_8UC1);
	for (a = 1; a < image.rows - 1; a++)
	{
		for (b = 1; b < image.cols - 1; b++)
		{
			/**if (a == image.rows - 1 || a == 0 || b == image.cols - 1 || b == 0)
			{
			im2.at<uchar>(a, b) = 0; continue;
			}**/
			wh = bl = 0;
			for (i = (a - 1); i < (a + 2); i++)
			{
				for (j = (b - 1); j <(b + 2); j++)
				{
					if (image.at<uchar>(i, j) == 255) wh++;
					else bl++;
				}
			}
			if (wh>bl && bl != 0) im2.at<uchar>(a, b) = 0;
			else if (wh<bl && wh != 0) im2.at<uchar>(a, b) = 255;
			else if (wh>bl && bl == 0) im2.at<uchar>(a, b) = image.at<uchar>(a, b);
			else if (wh < bl && wh == 0) im2.at<uchar>(a, b) = image.at<uchar>(a, b);
		}
	}
	return im2;
}
Mat meanfil(Mat img)
{
	Mat im;
	img.copyTo(im);
	int a, b, i, j, s;
	for (a = 1; a < im.rows - 1; a++)
	{
		for (b = 0; b < im.cols - 1; b++)
		{
			s = 0;
			for (i = a - 3; i < a + 4; i++)
			{
				for (j = b - 3; j < b + 4; j++)
				{

					s += img.at<uchar>(i, j);
				}
			}
			im.at<uchar>(a, b) = s / 49;
		}
	}
	return im;
}
Mat medianfil(Mat img)
{
	Mat im;
	img.copyTo(im);
	int a, b, i, j, s[9], k, l, m, min, n;
	for (a = 1; a < im.rows - 1; a++)
	{
		for (b = 0; b < im.cols - 1; b++)
		{
			for (i = 0; i < 9; i++) s[i] = 0; k = 0;
			for (i = a - 1; i < a + 2; i++)
			{
				for (j = b - 1; j < b + 2; j++, k++)
				{

					s[k] = img.at<uchar>(i, j);
				}
			}
			for (l = 0; l < 8; l++)
			{
				min = s[l]; n = l;
				for (m = l + 1; m < 9; m++)
				{
					if (min>s[m]) {
						min = s[m]; n = m;
					}
				}
				k = s[l];
				s[l] = min;
				s[n] = k;
			}
			im.at<uchar>(a, b) = s[4];
		}
	}
	return im;
}
Mat gaussfil(Mat img)
{
	Mat im;
	img.copyTo(im);
	int a, b;
	for (a = 1; a < im.rows - 1; a++)
	{
		for (b = 0; b < im.cols - 1; b++)
		{
			im.at<uchar>(a, b) = (0.06*(int)(im.at<uchar>(a - 1, b - 1) + im.at<uchar>(a - 1, b + 1) + im.at<uchar>(a + 1, b - 1) + im.at<uchar>(a + 1, b + 1)) + 0.098*(int)(im.at<uchar>(a, b - 1) + im.at<uchar>(a, b + 1) + im.at<uchar>(a + 1, b) + im.at<uchar>(a - 1, b)) + 0.162*im.at<uchar>(a, b)) / 0.794;
		}
	}
	return im;
}
Mat bgrtohsv(Mat im2, int t1,int t2,int t3)
{
	int a, b;
	Mat i(im2.rows,im2.cols,CV_8UC1);
	for (a = 0; a < im2.rows; a++)
	{
		for (b = 0; b < im2.cols; b++)
		{
			if (im2.at<Vec3b>(a, b)[0] >= t1 && im2.at<Vec3b>(a, b)[1] >= t2 && im2.at<Vec3b>(a, b)[2] >= t3) i.at<uchar>(a, b) = 255;
			else i.at<uchar>(a, b) = 0;
		}
	
	}
	return i;
}
//int p[2000][2000];
Mat qq(Mat z,Mat im, int x, int y,int m)
{
	//cout << m << " ";
	int i, j;
	for (i = (x - 1); i <(x + 2); i++)
	{
		for (j = (y - 1); j <(y + 2); j++)
		{
			if (z.at<uchar>(i, j) == 0 && im.at<uchar>(i,j) == 255)
			{
			
				//p[i][j] = 0; 
				im.at<uchar>(i, j) = 255/m; 
				im=qq(z, im, i, j, m);
			}
		}
	}
	return im;
}
Mat blob(Mat z)
{
	Mat im(z.rows, z.cols, CV_8UC1);
	int a, b, s = 1;
	for (a = 0; a < z.rows; a++)
	{
		for (b = 0; b < z.cols; b++)
		{
			im.at<uchar>(a, b) = 255;
			//p[a][b] = -1;
		}
	}
	for (a = 1; a < z.rows-1; a++)
	{
		for (b = 1; b < z.cols-1; b++)
		{
			if (z.at<uchar>(a, b) == 0 && im.at<uchar>(a,b) == 255)
			{
				s++;
				im.at<uchar>(a, b) = 255 /s;
				//p[a][b] = 0;
				im=qq(z,im, a, b, s);
			}
		}
	}
	//cout << s;
    return im;
}
Mat hough(Mat img)
{
	int ia[7000][180];
	Mat i(((int)sqrt(img.rows*img.rows + img.cols*img.cols)), 180, CV_8UC1, Scalar(255));
	//Mat im = img;
	//int counter = 0;
	int a, b, r, tta;
	for (a = 0; a < 7000; a++)
	{
		for (b = 0; b < 180; b++)
		{
			ia[a][b] = 0;
		}
	}
	
	for (a = 0; a < img.rows; a++)
	{
		for (b = 0; b < img.cols; b++)
		{
			if (img.at<uchar>(a, b) == 0)
			{
				for (tta = 0; tta < 180; tta++)
				{
					r = (int)(b*cos(tta*CV_PI / 180) + a*sin(tta*CV_PI / 180));
					if (r < 0) r *= -1;
					//ia[r][tta]++;
					//cout << i.at<uchar>(r, tta) << " "<<r<<" "<<tta<<endl;
					if (i.at<uchar>(r, tta)>0) i.at<uchar>(r, tta)--;
					//cout << counter++ << endl;
				}
			}
		}
	}
	return i;
}
	/**Mat opphough(Mat i,Mat im)//input i will be hough image
	{
	Mat img(im.rows,im.cols,CV_8UC1);
	int a, b;
	for (a = 0; a < i.rows; a++)
	{
	for (b = 0; b < i.cols; b++)
	{

	}
	}
	}**/
int main()
{
	Mat image = imread("C:\\Users\\Yajat\\Desktop\\t.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//int x=255,y=255,z=255,w=0;
	//image = gray(image);
	//int p = 0, q = 0,r = 0;
	//Mat img = image;
	namedWindow("Yajat", CV_WINDOW_NORMAL);
	//cvtColor(image, img, CV_BGR2HLS_FULL);
	//namedWindow("Yajat1", CV_WINDOW_AUTOSIZE);
	//imshow("Yajat", blob(bin(gray(image),120)));
	//namedWindow("bin", CV_WINDOW_AUTOSIZE);
	//imshow("bin", bin(image, 120));
	//waitKey(0);
	imshow("Yajat", hough(bin(image,120)));
	waitKey(0);
	/**namedWindow("mean", CV_WINDOW_AUTOSIZE);
	imshow("mean", meanfil(image));
	waitKey(0);
	namedWindow("median", CV_WINDOW_AUTOSIZE);
	imshow("median", medianfil(image));
	waitKey(0);
	namedWindow("gauss", CV_WINDOW_AUTOSIZE);
	imshow("gauss",gaussfil(image));
	waitKey(0);
	namedWindow("canny", CV_WINDOW_AUTOSIZE);**/

	//waitKey(0);
	//createTrackbar("thres", "Yajat", &x, 255);
	//imshow("Yajat", outl(image,thres));
	//createTrackbar("blue", "Yajat", &x,510);
	//createTrackbar("red", "Yajat", &z,510);
	//createTrackbar("green", "Yajat", &y,510);
	//createTrackbar("thres", "Yajat", &w, 255);
	//createTrackbar("h", "Yajat", &p, 255);
	//createTrackbar("s", "Yajat", &q, 255);
	//createTrackbar("l", "Yajat", &r, 255);
	//Mat im(image.rows,image.cols,CV_8UC1);
	//VideoCapture v(0);
	/**while (1)
	{
		/**Mat bimg = compl(image,x,y,z);
		//bimg = red(image,y);
		//bimg = green(image,z);
		//bimg=thres(image,w);//First convert to binary
		imshow("Yajat",bimg);**/
		/**imshow("Yajat", naive(image,x));
		imshow("Yajat1", dilute(naive(image, x)));
		imshow("Yajat2", erosion(dilute(naive(image, x))));/////
		//Canny(image, im, p, q, 3);
		//imshow("canny", im);
		Mat frame, frame2;
		v >> frame;
		Canny(gray(frame), frame2, p, q, 3);
		imshow("Yajat", gaussfil(gray(frame)));
		imshow("Yajat1", (frame2));
		imshow("Yajat", bgrtohsv(img, p, q, r));
		char a = waitKey(33);
		if (a >= 27) break;
	}**/
	return 0;
}