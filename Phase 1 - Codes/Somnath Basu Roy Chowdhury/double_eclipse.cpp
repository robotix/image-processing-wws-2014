#include<vector>
using namespace std;
using namespace cv;

int main()
{
	Mat image(200,300,CV_8UC3);
	namedWindow("My window", CV_WINDOW_AUTOSIZE);
	int i, j;
	for (i = 0; i < 200; i++)
	{
		for (j = 0; j < 300; j++)
		{
			
			
				if (abs(j-150) < 4*sqrt(10000 - pow(i-100, 2))/3)
				{

					
					if (abs(j - 150) < 4 * sqrt(1000 - pow(i - 100, 2)) / 3)
					{
						image.at<Vec3b>(i, j)[0] = 255;
						image.at<Vec3b>(i, j)[1] = 0;
						image.at<Vec3b>(i, j)[2] = 0;
					}
					else
					{
						image.at<Vec3b>(i, j)[0] = 0;
						image.at<Vec3b>(i, j)[1] = 255;
						image.at<Vec3b>(i, j)[2] = 0;
					}
				}
			else
			{
				image.at<Vec3b>(i, j)[0] = 0;
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[2] = 255;
			}

		}
	}
	imshow("My window", image);
	waitKey(0);
}

