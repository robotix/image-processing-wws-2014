#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <queue>

using namespace std;
using namespace cv; 
int main()
{
	int count = 1;
	queue<Point> que;
	Mat image;
	int i, j,k,l;

	image = imread("10850678_10203017302849237_757178162_n.jpg");
	Mat img(image.rows, image.cols, CV_8SC1);
	
	for (int i = 0; i < image.rows; i++)
	{
		
		for (int j = 0; j < image.cols; j++)
		{
			img.at<uchar>(i, j) = -1;
			//cout << chk[i][j];
		}
	}

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) == 255 && img.at<uchar>(i, j) == -1)
			{
				Point p;
				p.x = i;
				p.y = j;
				que.push(p);

				while (!que.empty())
				{
					p = que.front();
					img.at<uchar>(p.x, p.y) = 1;
					for (int k = -1; k <= 1; k++)
					{
						for (int l = -1; l <= 1; l++)
						{
							if (image.at<uchar>(que.front().x + k, que.front().y + l) == 255 && img.at<uchar>(que.front().x + k)(que.front().y + l) == -1)
							{
								p.x = que.front().x + k;
								p.y = que.front().y + l;
								//cout << "pushed " << p.x << " " << p.y;;
								que.push(p);
								img.at<uchar>(p.x, p.y) == 0;
							}
						}
					}
					p = que.front();
					//cout << p.x << " " << p.y;
					//system("PAUSE");
					img.at<uchar>(p.x, p.y) = count;
					que.pop();
				}
				//cout << "while loop break";
				//system("PAUSE");
				count++;
			}

		}
	}

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (img.at<uchar>(i,j)!= -1 && image.at<uchar>(i, j) != 0)
			{
				image.at<uchar>(i, j) /= img.at<uchar>(i, j);
			}
		}
	}
	imshow("WINDOW", image);
	waitKey(0);
	return 0;
}