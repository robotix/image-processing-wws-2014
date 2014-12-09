#include"stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
/*int main()
{
	Mat image = imread("C:\\Users\\PRIYANK YADAV\\visual photos\\11.JPG", CV_LOAD_IMAGE_GRAYSCALE);

	Mat image1(image.rows, image.cols, CV_8UC1, Scalar(255));
	char win[] = "my window";
	int k, l, max, min, t = 15, i, j;
	namedWindow(win, CV_WINDOW_AUTOSIZE);
	imshow(win, image);
	waitKey(0);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			max = 0; min = 255;
			for (k = i - 1; k <= i + 1; k++)
			{
				for (l = j - 1; l <= j + 1; l++)
				{
					if (k >= 0 && k < image.rows  && l >= 0 && l < image.cols)
					{
						if ((k != i && l == j) || (k == i && l != j))

						{
							if (image.at<uchar>(k, l) > max)
								max = image.at<uchar>(k, l);

							if (image.at<uchar>(k, l) < min)
								min = image.at<uchar>(k, l);

						}
					}

				}
			}
			if ((max - min) > t)
				image1.at<uchar>(i, j) = 0;
		}
	}
	namedWindow(win, CV_WINDOW_AUTOSIZE);
	imshow(win, image1);
	waitKey(0);
	return 0;
}*/
