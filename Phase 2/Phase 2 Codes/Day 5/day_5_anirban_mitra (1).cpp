#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <queue>
using namespace std;
using namespace cv;

int main(int argc, _TCHAR* argv[])
{
	Mat img = imread("E:\\walpapers\\blob.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2(img.rows, img.cols, CV_8SC1,Scalar(-1));
	Point p; queue<Point>q; int m, n; int count = 1;
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			if (img.at<uchar>(i, j) >200 && img2.at<char>(i, j) == -1)
			{
				
					p.x = j; p.y = i;
					q.push(p);
					img2.at<char>(i, j) = 0;
				while (!q.empty())
				{
					p = q.front();
					m = p.y; n = p.x;
					for (int r = m - 1; r <= m + 1; r++)
					{
						for (int c = n - 1; c <= n + 1; c++)
						{
							if ((img.at<uchar>(r, c) > 200) && (img2.at<char>(r, c) == -1))
							{
								img2.at<char>(r, c) = 0;
								p.x = c; p.y = r;
								q.push(p);
							}
						}
					}
					q.pop();
					img2.at<char>(m, n) = count;
					
				}
				count++;
			}
		}
	}
	Mat img3(img.rows, img.cols, CV_8UC3,Scalar(0,0,0));
		for (int i = 1; i < img.rows - 1; i++)
		{
			for (int j = 1; j < img.cols - 1; j++)
			{
				if (img2.at < char >(i,j)!=-1)
				{
					//img3.at<uchar>(i, j) = (255 / (img2.at < char >(i, j)));
					img3.at<Vec3b>(i, j)[0] = (255 / (img2.at < char >(i, j)));
					img3.at<Vec3b>(i, j)[1] = (255 / (img2.at < char >(i, j)+25));
					img3.at<Vec3b>(i, j)[2] = (255 / (img2.at < char >(i, j)+50));
				}
			}
		}
	namedWindow("blob", WINDOW_NORMAL);
	imshow("blob", img3);
	waitKey(0);
	return 0;
}