#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<math.h>
#include<opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;
Mat grey(Mat);
Mat dilation(Mat image);
 Mat binary(Mat, int);
 Mat Bincol(Mat, int, int, int);
 Mat erosion(Mat);
 Mat blur(Mat col);
 Mat gaussean(Mat);
 Mat blurimmedian(Mat);
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
	 /* int x = 112;
	  namedWindow("mywindow", CV_WINDOW_AUTOSIZE);
	  createTrackbar("threshold", "mywindow", &x, 200);//first 2 are strings

	  while (1)
	  {
	  Mat temp = grey(image);
	  Mat bin = binary(temp, x);

	  char a = waitKey(500);
	  if (a == 27)break;
	  imshow("mywindow", bin);
	  }*/
	 /*BINARY CONVERSION OF COLOURED IMAGE
	 namedWindow("mywindow", CV_WINDOW_AUTOSIZE);
	 int a = 112, d = 112, c = 112;
	 createTrackbar("r", "mywindow", &a, 255);
	 createTrackbar("b", "mywindow", &d, 255);
	 createTrackbar("g", "mywindow", &c, 255);
	 while (1)
	 {
	 Mat image = imread("E:\\nature.jpg", CV_LOAD_IMAGE_COLOR);
	 Mat bin = Bincol(image, a,d,c);
	 imshow("mywindow", bin);
	 char t = waitKey(33);
	 if (t == 27)break;

	 }
	 */

	 /*USING METHOD 1 TO DO FEATURE EXTRACTION OF GREYSCALE IMAGE and dilation and erosion
	 Mat image = imread("E:\\rahul.jpg", CV_LOAD_IMAGE_COLOR);
	 namedWindow("mywindow", CV_WINDOW_AUTOSIZE);
	 //int x = 0;
	 //createTrackbar("threshold", "mywindow", &x, 255);

	 imshow("window", image);
	// while (1)
	 //{
		 Mat im = grey(image);
		 imshow("window0", im);

		 Mat temp(image.rows, image.cols, CV_8UC1, Scalar(0));
		 for (int i = 1; i < image.rows - 1; i++)
		 {
			 for (int j = 1; j < image.cols - 1; j++)
			 {
				 int min = im.at<uchar>(i - 1, j - 1), max = im.at<uchar>(i - 1, j - 1);
				
				 for (int k = -1; k < 2; k++)
				 {
					 for (int m = -1; m<2; m++)
					 {
						 if (im.at<uchar>(i + k, j + m)>max)
							 max = image.at<uchar>(i + k, j + m);
						 if (im.at<uchar>(i + k, j + m) < min)
							 min = im.at<uchar>(i + k, j + m);
					 }
				 }
				 if (abs(max - min) >=100)temp.at<uchar>(i, j) = 255;


			 }

		 }
		 imshow("mywindow", temp);
		Mat dil= dilation(temp);
		imshow("window1", dil);
		Mat ers = erosion(dil);
		imshow("window2", ers);
		Mat ers1 = erosion(ers);
		imshow("window3", ers1);
		// char t = waitKey(33);
		 //if (t == 27)break;
	 //}*/
Mat image = imread("E:\\nature.jpg", CV_LOAD_IMAGE_COLOR);
namedWindow("window", CV_WINDOW_AUTOSIZE);
imshow("window", image);
Mat temp = grey(image);
imshow("window1", temp);
//Mat temp1=blurimmedian(temp);
//imshow("window2", temp1);
/*Mat greyim=grey(image),fimg;
int x = 20,y=0;
namedWindow("windowa", CV_WINDOW_AUTOSIZE);
createTrackbar("upper", "windowa", &x, 255);
createTrackbar("lower", "windowa", &y, 255);

while (1)
{
	Mat greyim = grey(image);
	 Canny(greyim, fimg, x, y);
	imshow("windowa", fimg);
	int t = waitKey(33);
	if (t == 27)break;
}*/


Mat fimg = gaussean(temp);
imshow("windowa", fimg);

/*BLURING IMAGE USING AVERAGE GIVING EQUAL WEIGHTAGE
Mat blurim = blur(temp);
imshow("window3", blurim);*/
	 waitKey(0);
	 return 0;
 }
 
/*USING METHOD 2 TO DO FEATURE EXTRACTION OF GREYSCALE IMAGE

Mat image = imread("E:\\rahul.jpg", CV_LOAD_IMAGE_COLOR);
Mat greyim = grey(image);
imshow("window", image);
imshow("window1", greyim);
Mat temp1(image.rows, image.cols, CV_8UC1, Scalar(0)), tempx(image.rows, image.cols, CV_8UC1, Scalar(0)), tempy(image.rows, image.cols, CV_8UC1, Scalar(0));
for (int i = 1; i < image.rows - 1; i++)
{
	for (int j = 1; j < image.cols - 1; j++)
	{
		int x = 0, y = 0;
		for (int k = -1; k < 2; k++)
		{
			x = x + greyim.at<uchar>(i + k, j + 1) - greyim.at<uchar>(i + k, j - 1);
			y = y + greyim.at<uchar>(i + 1, j + k) - greyim.at<uchar>(i + -1, j + k);
		}

		temp1.at<uchar>(i, j) = sqrt(x*x + y*y);
		tempx.at<uchar>(i, j) = x;
		tempy.at<uchar>(i, j) = y;
	}
}
imshow("window2", temp1);
imshow("window3", tempx);
imshow("window4", tempy);
*/





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
			

				 temp.at<uchar>(i, j) = (img.at<Vec3b>(i, j)[0] +img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;

			
		 }
		 
	 }return temp;
 }

	 /*Mat Bincol(Mat img, int r, int b, int g)
	 {

	 for (int i = 0; i < img.rows; i++)
	 {
	 for (int j = 0; j < img.cols; j++)
	 {
	 if (img.at<Vec3b>(i, j)[2] < r)
	 img.at<Vec3b>(i, j)[2] = 0;
	 else
	 img.at<Vec3b>(i, j)[2] = 255;

	 if (img.at<Vec3b>(i, j)[1] < g)
	 img.at<Vec3b>(i, j)[1] = 0;
	 else
	 img.at<Vec3b>(i, j)[1] = 255;

	 if (img.at<Vec3b>(i, j)[0] < b)
	 img.at<Vec3b>(i, j)[0] = 0;
	 else
	 img.at<Vec3b>(i, j)[0] = 255;
	 }
	 }

	 return img;
	 }*/
	 /* binary of a greyscale scale image
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

	 }*/

	 Mat blur(Mat image)
	 {
	    Mat temp(image.rows, image.cols, CV_8UC1);
		  for (int i = 1; i < image.rows - 1; i++)
	 {
			  for (int j = 1; j < image.cols - 1; j++)
				 {
	int sum=0;
				  for (int k = -1; k < 2; k++)
					 {
					   for(int m=-1;m<2;m++)
					 sum=sum+image.at<uchar>(i+k,j+m);
					 }	
					temp.at<uchar>(i,j)=sum/9;
			      }
	 }
	 return temp;
	 }
		

	
	 Mat dilation(Mat image)
	 {
		 Mat temp(image.rows, image.cols, CV_8UC1, Scalar(0));

		 for (int i = 1; i < image.rows - 1; i++)
		 {
			 for (int j = 1; j < image.cols - 1; j++)
			 {
				 
				 int bla=0, whi=0;
				 for (int k = -1; k < 2; k++)
				 {
					 for (int m = -1; m < 2; m++)
					 {

						 if (image.at<uchar>(i + k, j + k) == 255)whi++;
						 else bla++;
					 }
				 }
				 if (bla < whi)temp.at<uchar>(i, j) = 255;
				 else  temp.at<uchar>(i, j) = 0;
			 }
		 }
		 return temp;
	 }
 
	 Mat erosion(Mat image)
	 {
		 Mat temp(image.rows, image.cols, CV_8UC1, Scalar(0));

		 for (int i = 1; i < image.rows - 1; i++)
		 {
			 for (int j = 1; j < image.cols - 1; j++)
			 {

				 int bla = 0, whi = 0;
				 for (int k = -1; k < 2; k++)
				 {
					 for (int m = -1; m < 2; m++)
					 {
						 if (image.at<uchar>(i + k, j + k) == 255)whi++;
						 else bla++;
					 }
				 }
				 if (bla != 0 && whi != 0)
				 {
					 if (bla < whi)temp.at<uchar>(i, j) = 0;
					 else  temp.at<uchar>(i, j) = 255;
				 }
			 }
		 }
		 return temp;
	 }
	 Mat blurimmedian(Mat image)
	 {
		 Mat temp(image.rows, image.cols, CV_8UC1);
		 int A[9];
		 for (int i = 1; i < image.rows - 1; i++)
		 {
			 for (int j = 1; j < image.cols - 1; j++)
			 {

				 int e = 0;
				 for (int k = -1; k < 2; k++)
				 {
					 for (int m = -1; m < 2; m++)
					 {
						 A[e++] = image.at<uchar>(i + k, j + m);
						 
					 }
				 }
				 
				 for (int a = 7; a>= 0; --a)
				 {
					 for (int b = 0; b <= a; ++b)

					 {
						 if (A[b] > A[b + 1])
						 {

							 int t = A[b];
							 A[b] = A[b+ 1];
							 A[b + 1] = t;
						 }
					 }
				 }
				 temp.at<uchar>(i, j) = A[4];
				 
			 }
		 }
		  return temp;
	 }

	 Mat gaussean(Mat image)
	 {
		 Mat temp(image.rows, image.cols, CV_8UC1);
		 for (int i = 1; i < image.rows - 1; i++)
		 {
			 for (int j = 1; j < image.cols - 1; j++)
			 {
				 int sum = 0;
				 for (int k = -1; k < 2; k++)
				 {
					 for (int m = -1; m < 2; m++)
					 {

						 sum = sum + (image.at<uchar>(i + k, j + m))  *pow(2.718, -(k*k + m*m) /2)/ (2*3.14);
					 }
				 }
				 temp.at<uchar>(i, j) = sum;
			 }
		 }
		 return temp;
	 }