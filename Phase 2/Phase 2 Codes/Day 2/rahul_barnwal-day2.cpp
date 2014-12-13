 #include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
 Mat grey(Mat);
 Mat binary(Mat, int);

 int main()
 {
	 /*
		 DISPLAYING ONLY RED CHANNELS

		 Mat image;
		 image = imread("E:\\images.jpg", CV_LOAD_IMAGE_COLOR);
		 //namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
		 //imshow("MyWindow", image);
		 for (int i = 0; i < image.rows; i++)
		 {
		 for (int j = 0; j < image.cols; j++)
		 {
		 for (int k = 0; k < 2; k++)
		 {
		 image.at<Vec3b>(i, j)[k] = 0;
		 }
		 }
		 }

		 namedWindow("MyWindow2", CV_WINDOW_AUTOSIZE);
		 imshow("MyWindow2", image);
		 */

	 /*CREATING INDIAN FLAG AND THEN CONVERTING IT INTO GREYSCALE



	 Mat img(48, 144, CV_8UC3, Scalar(255, 255, 255));
	 for (int i = 0; i < 16; i++)
	 {
	 for (int j = 0; j < 144; j++)
	 {

	 img.at<Vec3b>(i, j)[0] = 0;
	 img.at<Vec3b>(i, j)[1] = 165;
	 img.at<Vec3b>(i, j)[2] = 255;
	 }
	 }
	 for (int i = 32; i < 48; i++)
	 {
	 for (int j = 0; j < 144; j++)
	 {

	 img.at<Vec3b>(i, j)[0] = 0;
	 img.at<Vec3b>(i, j)[1] = 255;
	 img.at<Vec3b>(i, j)[2] = 0;
	 }
	 }
	 namedWindow("MyWindow2", CV_WINDOW_AUTOSIZE);
	 imshow("MyWindow2", img);


	 Mat greyim(48, 144, CV_8UC1);
	 for (int i = 0; i < greyim.rows; i++)
	 {
	 for (int j = 0; j < greyim.cols; j++)
	 {


	 greyim.at<uchar>(i, j) = (img.at<Vec3b>(i, j)[0] +
	 img.at<Vec3b>(i, j)[1] +
	 img.at<Vec3b>(i, j)[2]) / 3;
	 imshow("window3", greyim);

	 }
	 }
	 */


	 Mat image = imread("E:\\nature.jpg", CV_LOAD_IMAGE_COLOR);
	 imshow("window", image);
	 
	 /*coversion OF A GREY SCALE IMGE TO BINARY IMAGE
	 Mat temp = grey(image);
	 imshow("window4", temp);
	 for (int i = 0; i < temp.rows; i++)
	 {
	 for (int j = 0; j < temp.cols; j++)
	 {
	 if (temp.at<uchar>(i, j) < 128)
	 temp.at<uchar>(i, j) = 0;
	 else
	 temp.at<uchar>(i, j) = 255;
	 }
	 }

	 imshow("window5", temp);
	 */
	 /*for (int i = 0; i < image.cols; i++)
	 {
	 for (int j = 0; j < image.rows / 2; j++)
	 {
	 for (int k = 0; k < 3; k++)
	 {

	 int a = image.at<Vec3b>(j, i)[k];
	 image.at<Vec3b>(j, i)[k] = image.at<Vec3b>(image.rows - j - 1, i)[k];
	 image.at<Vec3b>(image.rows - j - 1, i)[k] = a;

	 }
	 }
	 }*/
	 /*CALCULATING THRESHOLD AND DRAWING HISTOGRAM
	 int ar[256];
	 for (int i = 0; i < 256; i++)

	 ar[i] = 0;
	 for (int i = 0; i < temp.rows; i++)
	 {
	 for (int j = 0; j < temp.cols; j++)
	 {
	 for (int k = 0; k < 256; k++)
	 {
	 if (temp.at<uchar>(i, j) == k)
	 ar[k]++;
	 }
	 }
	 }
	 int sum = 0,thd;
	 for (thd = 0; sum <= temp.rows*temp.cols /2; thd++)
	 {
	 sum = sum + ar[thd];

	 }
	 thd--;
	 cout << "threshold value of intensity =" << thd;
	 Mat binimg = binary(temp, thd);
	 imshow("Window1", binimg);
	 Mat histg((temp.rows*temp.cols+1)/100, 257, CV_8UC1, Scalar(0));

	 for (int i = 0; i < histg.rows; i++)
	 histg.at<uchar>(i, 0) = 255;
	 for (int i = 0; i < histg.cols; i++)
	 histg.at<uchar>(histg.rows-1,i) = 255;
	 for (int k = 1; k < histg.cols; k++)
	 {
	 for (int a = histg.rows - 2; a >= histg.rows - ar[k - 1]; a--)
	 histg.at<uchar>(a, k) = 255;
	 }
	 namedWindow("Window7", CV_WINDOW_AUTOSIZE);
	 imshow("Window7", histg);*/
	 int x = 112;
	 namedWindow("mywindow", CV_WINDOW_AUTOSIZE);
	 createTrackbar("threshold", "mywindow", &x, 200);//first 2 are strings
	 
	 while (1)
	 {
		 Mat temp = grey(image);
		 Mat bin = binary(temp, x);
		
		 char a = waitKey(500);
		 if (a == 27)break;
		 imshow("mywindow", bin);
	 }
 
	 
waitKey(0);
	return 0;


}
/*
mat also contains scalar to intialise same value to each pixel
mat img(r, c, cv_8uc1, scalar(0));
all pixek will have same value
for 3 channel image
mat img(r,c,cv_)

*/
Mat grey(Mat img)
{
	Mat temp(img.rows, img.cols, CV_8UC1);
	
	for (int i = 0; i < temp.rows; i++)
	{
		for (int j = 0; j < temp.cols; j++)
		{


			temp.at<uchar>(i, j) = (img.at<Vec3b>(i, j)[0] +
				img.at<Vec3b>(i, j)[1] +
				img.at<Vec3b>(i, j)[2]) / 3;

		}
	}
	return temp;
}
Mat binary(Mat greyim, int thd)
{
	for (int i = 0; i < greyim.rows; i++)
	{
		for (int j = 0; j < greyim.cols; j++)
		{
			if (greyim.at<uchar>(i, j) < thd)
				greyim.at<uchar>(i, j) = 0;
			else
				greyim.at<uchar>(i, j) = 255;
		}
	}
	return greyim;

}