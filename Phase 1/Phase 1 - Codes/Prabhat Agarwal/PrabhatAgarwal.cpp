#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cmath>


using namespace std;
using namespace cv;


typedef struct _blob
{
	int id;
	int maxx;
	int maxy;
	int minx;
	int miny;
	int cnt;
	int cx;
	int cy;
}Blob;

void load_image(char name[])
{
	Mat image;
	image = imread(name, CV_LOAD_IMAGE_COLOR);
	namedWindow("START", CV_WINDOW_AUTOSIZE);
	imshow("START", image);
	waitKey();

}

void imageCreator()
{
	int i, j;
	Mat image(200, 300, CV_8UC3, Scalar(0, 0, 0 ));
	char winName[] = "Striped Image";
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (i < image.rows / 3)
				image.at<Vec3b>(i, j)[2] = 255;
			else if (i > image.rows / 3 && i < 2 * image.rows / 3)
				image.at<Vec3b>(i, j)[1] = 255;
			else
				image.at<Vec3b>(i, j)[0] = 255;
		}

	}
	namedWindow(winName, CV_WINDOW_AUTOSIZE);
	imshow(winName, image);
	waitKey();
}

Mat rgbToBinary(Mat image,int threshold)
{
	int i, j, sum = 0;;
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			sum = image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2];
			if (sum < threshold)
			{
				image2.at<uchar>(i, j) = 255;
			}
			else
				image2.at<uchar>(i, j) = 0;
		}

	}
	/*char winName[] = "RGB TO BINARY";
	namedWindow(winName, CV_WINDOW_AUTOSIZE);
	imshow(winName, image2);
	//waitKey();*/
	return image2;
	
}

Mat RGB_to_Graysacle(Mat image)
{
	Mat dst(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j, sum = 0;;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			sum = image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2];
			dst.at<uchar>(i,j) = sum / 3;
		}

	}
	/*char winName[] = "RGB To Graysacle";
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, image);
	waitKey();*/
	return dst;

}

void histogramThreshold()
{
	int i, j, sum = 0;;
	char imgName[] = "G:\sample2.jpg";
	Mat image = imread(imgName, CV_LOAD_IMAGE_GRAYSCALE);
	int freq[256] = { 0 };
	int threshold = (image.rows * image.cols )/ 2;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			freq[image.at<uchar>(i, j)] ++;
		}
	}
	for (i = 0; i < 256; i++)
	{
		sum += freq[i];
		if (sum > threshold)
			break;
	}
	/*int factor = (threshold * 2) / 500;
	Mat histogram(500, 256, CV_8UC1 ,Scalar(0));
	char winName[] = "Histogram";
	for (i = 0; i < image.cols; i++)
	{
		histogram.at<uchar>(freq[i]/factor, i) = 255;
	}
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, histogram);
	waitKey();*/





	threshold = i;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) > threshold)
				image.at<uchar>(i, j) = 255;
			else
				image.at<uchar>(i, j) = 0;
		}
	}
	char winName[] = "Histogram";
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, image);
	waitKey();
}
double getMean(Mat image, int i, int j)
{
	//printf("I amhere\n");
	int k, l, sum = 0, t=9;
	for (k = i - 1; k <= i + 1; k++)
	{
		for (l = j - 1; l <= j + 1; l++)
		{
			if (k < 0 || l < 0 || k >= image.rows  || l >= image.cols)
			{
				t--;
				continue;
			}
			sum += image.at<uchar>(k, l);
		}
	}
	//printf("\nLoop ended\n");
	return ((double)sum / t);

}
void adaptiveThreshold()
{
	Mat image = imread("G:\\sample3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			double mean = getMean(image, i, j);
			if (image.at<uchar>(i, j) > mean)
				image2.at<uchar>(i, j) = 255;
			else
				image2.at<uchar>(i, j) = 0;

		}
	}
	namedWindow("Adaptive", CV_WINDOW_NORMAL);
	imshow("Adaptive", image2);
	waitKey();
}

void globalMean()
{
	Mat image = imread("G:\\sample.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int i, j,sum = 0;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			sum += image.at<uchar>(i, j);

		}
	}
	double mean = sum / (image.rows*image.cols);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) > mean)
				image.at<uchar>(i, j) = 255;
			else
				image.at<uchar>(i, j) = 0;

		}
	}
	namedWindow("Global", CV_WINDOW_NORMAL);
	imshow("Global", image);
	waitKey();
}

void trakbar()
{
	Mat image = imread("G:\\sample2.jpg", CV_LOAD_IMAGE_COLOR);
	int threshold = 362;
	namedWindow("TrackBar", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "TrackBar", &threshold, 255 * 3);
	while (true)
	{
		Mat img = rgbToBinary(image, threshold);
		imshow("TrackBar", img);
		int key = waitKey(50);
		if (key == 27)
			break;

	}
}
int getDiff(Mat image, int i, int j)
{
	//printf("I am here\n");
	int k, l, max = -1, min = 300;
	for (k = i - 1; k <= i + 1; k++)
	{
		for (l = j - 1; l <= j + 1; l++)
		{
			if (k < 0 || l < 0 || k >= image.rows || l >= image.cols)
			{
				continue;
			}
			if (image.at<uchar>(k, l) > max)
				max = image.at<uchar>(k, l);
			if (image.at<uchar>(k, l) < min)
				min = image.at<uchar>(k, l);

		}
	}
	//printf("%d %d \n", max, min);
	//printf("\nLoop ended\n");
	return (max - min);

}

Mat EdgeDetection(Mat image2,int threshold)
{
	//namedWindow(window, CV_WINDOW_AUTOSIZE);
	//imshow(window, image2);
	//Mat image2 = rgbToBinary(image, 362);
	Mat image3(image2.rows, image2.cols, CV_8UC1, Scalar(0));
	int i, j;
	for (i = 0; i < image2.rows; i++)
	{
		for (j = 0; j < image2.cols; j++)
		{
			int diff = getDiff(image2, i, j);
			//printf("%d \n", diff);
			if (diff > threshold)
				image3.at<uchar>(i, j) = 255;
			else
				image3.at<uchar>(i, j) = 0;

		}
	}
	return image3;

}
void EdgeDetect(Mat image,char window[])
{
	int threshold = 80;
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", window, &threshold, 255);
	while (true)
	{
		Mat img = EdgeDetection(image, threshold);
		//putText(img, "hey you!!", cvPoint(100,100), FONT_HERSHEY_DUPLEX, 2, cvScalar(200, 200, 300), 1, 8, false);
		imshow(window, img);
		int key = waitKey(33);
		if (key == 27)
			break;
	}
}
Mat changeBrightness(Mat image,int brightness)
{
	int i, j;
	Mat img(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));
	double factor = brightness / 100;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			img.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0] * factor;
			img.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1] * factor;
			img.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2] * factor;
		}

	}
	return img;
}
void brightBar()
{
	int brightness = 100;
	Mat image = imread("G:\\sample.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Window", CV_WINDOW_AUTOSIZE);
	createTrackbar("Brightness", "Window", &brightness, 100);
	while (true)
	{
		Mat img = changeBrightness(image, brightness);
		imshow("Window", img);
		int key = waitKey(50);
		if (key == 27)
			break;
	}
}

int getBorW(Mat image, int i, int j)
{
	//printf("I am here\n");
	int k, l, black = 0,white =0;
	for (k = i - 1; k <= i + 1; k++)
	{
		for (l = j - 1; l <= j + 1; l++)
		{
			if (k < 0 || l < 0 || k >= image.rows || l >= image.cols||(k==i&&l==j))
			{
				continue;
			}
			if (image.at<uchar>(k, l) == 0)
				black++;
			if (image.at<uchar>(k, l) == 255)
				white++;
		}
	}
	//printf("%d %d \n", max, min);
	//printf("\nLoop ended\n");
	if (black == 8 || white == 8)
		return -1;
	if (black > white)
		return 0;
	else
		return 255;
}


Mat dilation(Mat src)
{
	int i, j;
	//Mat src2 = rgbToBinary(src, 362);
	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < src.rows; i++)
	{
		for (j = 0; j < src.cols; j++)
		{
			if (getBorW(src, i, j) != -1)
				dst.at<uchar>(i, j) = getBorW(src, i, j);
			else
				dst.at<uchar>(i, j) = src.at<uchar>(i, j);

		}
	}
	return dst;
}

Mat erosion(Mat src)
{
	int i, j;
	//Mat src2 = rgbToBinary(src, 362);
	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < src.rows; i++)
	{
		for (j = 0; j < src.cols; j++)
		{
			if (getBorW(src, i, j) == 0)
				dst.at<uchar>(i, j) = 255;
			else if (getBorW(src, i, j) == -1)
				dst.at<uchar>(i, j) = src.at<uchar>(i, j);
		}
	}
	return dst;
}

void video()
{
	VideoCapture vid("G:\\sample.mp4");
	int threshold = 362, position = 0;
	namedWindow("Video", CV_WINDOW_AUTOSIZE);
	int MAX = vid.get(CV_CAP_PROP_FRAME_COUNT)*1000;
	MAX = MAX / vid.get(CV_CAP_PROP_FPS);
	createTrackbar("threshold", "Video", &threshold,255*3);
	createTrackbar("Position", "Video", &position, MAX);
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	while (1)
	{
		Mat temp;
		vid.set(CV_CAP_PROP_POS_MSEC, position);

		if(vid.read(temp)==NULL)
			break;
		//if (temp.empty() == true)
			//break;
		imshow("Original", temp);
		Mat dst = RGB_to_Graysacle(temp);
		Mat img = rgbToBinary(temp, threshold);
		imshow("Video", img);
		int key = waitKey(30);
		if (key == 27)
			break;
		position = position + 1000 / vid.get(CV_CAP_PROP_FPS);
		setTrackbarPos("Position", "Video", position);
	}
}

/*int main()
{
	video();
	return 0;
}
*/


void CannyEdge(Mat image)
{
	int threshold = 20;
	namedWindow("CannyEdgeDetection", CV_WINDOW_NORMAL);
	createTrackbar("MinimumThreshold", "CannyEdgeDetection", &threshold, 255);
	while (true)
	{
		Mat img;
		img.create(image.size(), image.type());
		Canny(image, img, threshold, threshold * 3, 3, false);
		imshow("CannyEdgeDetection", img);
		int key = waitKey(50);
		if (key == 27)
			break;
	}
}


Mat rgbcolorDetection(Mat image, int color[], int t[])
{
	//Mat image;
	int i, j;
	Mat dst(image.rows, image.cols, CV_8UC1, Scalar(0));
	//cvtColor(src, image, CV_BGR2HSV);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (abs(image.at<Vec3b>(i, j)[0] - color[0]) < t[0]
				&& abs(image.at<Vec3b>(i, j)[1] - color[1]) < t[1]
				&& abs(image.at<Vec3b>(i, j)[2] - color[2]) < t[2])
				dst.at<uchar>(i, j) = 255;
		}
	}
	return dst;
}


Mat hsvcolorDetection(Mat src, int color[],int t[])
{
	Mat image;
	int i, j;
	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));
	cvtColor(src, image, CV_BGR2HSV);
	imshow("Color Detection", image);
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (abs(image.at<Vec3b>(i, j)[0] - color[0]) < t[0]
				&& abs(image.at<Vec3b>(i, j)[1] - color[1]) < t[1]
				&& abs(image.at<Vec3b>(i, j)[2] - color[2]) < t[2])
				dst.at<uchar>(i, j) = 255;
		}
	}
	return dst;
}
Mat image;
int thres[3];
void onMousergb(int event, int x, int y, int, void*)
{
	if (event != CV_EVENT_LBUTTONDOWN)
		return;
	int color[] = { image.at<Vec3b>(y,x)[0], image.at<Vec3b>(y, x)[1], image.at<Vec3b>(y, x)[2] };
	int thres[] = { 100, 100, 100 };
	Mat dst = rgbcolorDetection(image, color, thres);
	imshow("Color Detection", dst);
}
void onMousehsv(int event, int x, int y, int, void*)
{
	if (event != CV_EVENT_LBUTTONDOWN)
		return;
	Mat ima;
	cvtColor(image, ima, CV_BGR2HSV);
	int color[] = { ima.at<Vec3b>(y, x)[0], ima.at<Vec3b>(y, x)[1], ima.at<Vec3b>(y, x)[2] };
	int thres[] = { 10,50,200 };
	Mat dst = hsvcolorDetection(image, color, thres);
	imshow("Color Detection", dst);
	dst = dilation(dst);
	CannyEdge(dst);
}

void colorDetecthsv()
{
	image = imread("G:\\sample6.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Original", CV_WINDOW_NORMAL);
	namedWindow("Color Detection", CV_WINDOW_NORMAL);
	createTrackbar("Hue", "Original", &thres[0], 360);
	createTrackbar("\nSaturation", "Original", &thres[1], 100);
	createTrackbar("\nValue", "Original", &thres[2], 100);
	setMouseCallback("Original", onMousehsv, 0);
	imshow("Original", image);
	int color[] = { 0,0,0 };
	int thres[] = { 10, 10, 10 };
	Mat dst = hsvcolorDetection(image,color ,thres );
	imshow("Color Detection", dst);
	//waitKey();
}

void colorDetectrgb()
{
	image = imread("G:\\sample6.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Original", CV_WINDOW_NORMAL);
	namedWindow("Color Detection", CV_WINDOW_NORMAL);
	createTrackbar("Blue", "Original", &thres[0], 255);
	createTrackbar("Green", "Original", &thres[1], 255);
	createTrackbar("Red", "Original", &thres[2], 255);
	setMouseCallback("Original", onMousergb, 0);
	imshow("Original", image);
	int color[] = { 0, 0, 0 };
	int thres[] = { 100, 100, 100 };
	Mat dst = rgbcolorDetection(image, color, thres);
	imshow("Color Detection", dst);
	//waitKey();
}


void blobDetect(Mat image)
{
	int i, j;
	vector<vector<int>> blobs(image.rows,vector<int>(image.cols,-1));
	/*for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			blobs[i].push_back(-1);
		}
	}*/
	printf("I am here\n");
	int id = 0;
	int k, l;
	vector<Blob> blobse;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			if (blobs[i][j] != -1)
				continue;
			if (image.at<uchar>(i, j) == 0)
			{
				blobs[i][j] = 0;
				continue;
			}
			queue<Point*> Q;
			Q.push(new Point(i, j));
			id++;
			Blob b = { 0 };
			b.id = id;
			int sumx = 0, sumy = 0;
			while (!Q.empty())
			{
				Point *p = Q.front();
				Q.pop();
				for (k = p->x - 1; k <= p->x + 1; k++)
				{
					for (l = p->y - 1; l <= p->y + 1; l++)
					{
						if (k < 0 || l < 0 || k >= image.rows || l >= image.cols || (k == p->x &&l == p->y))
						{
							continue;
						}
						if (blobs[k][l] == -1 && image.at<uchar>(k, l) == 255)
							Q.push(new Point(k, l));
					}
				}
				blobs[p->x][p->y] = id;
				b.cnt++;
				if (p->x > b.maxx)
					b.maxx = p->x;
				if (p->y > b.maxy)
					b.maxy = p->y;
				if (p->x < b.minx)
					b.minx = p->x;
				if (p->y < b.miny)
					b.miny = p->y;
				sumx += p->x;
				sumy += p->y;
			}
			b.cx = sumx / b.cnt;
			b.cy = sumy / b.cnt;
			blobse.push_back(b);
		}
	}
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			printf("%d ", blobs[i][j]);
		}
		printf("\n");

	}
}


typedef struct pt_{

	int x, y;

}pt;



typedef struct blob_{



	int min_x, max_x;

	int min_y, max_y;

	int cen_x, cen_y;

	int n_pixels;

	int ID;

}blob;



void GetBlobs(Mat img, vector<blob>& blobs){



	int i, j, k, l, r = img.rows, c = img.cols, id = 1;

	vector<vector<int> > pixel_ID(r, vector<int>(c, -1)); //Stores ID of a pixel; -1 means unvisited

	queue<pt> open_list; //Breadth-First-Search hence queue of points



	for (i = 1; i<r - 1; i++){

		for (j = 1; j<c - 1; j++){

			if (img.at<uchar>(i, j) == 0 || pixel_ID[i][j]>-1)

				continue;

			pt start = { j, i };



			open_list.push(start);

			int sum_x = 0, sum_y = 0, n_pixels = 0, max_x = 0, max_y = 0;

			int min_x = c + 1, min_y = r + 1;

			while (!open_list.empty()){

				//Dequeue the element at the head of the queue

				pt top = open_list.front();

				open_list.pop();

				pixel_ID[top.y][top.x] = id;

				n_pixels++;



				//To obtain the bounding box of the blob w.r.t the original image

				min_x = (top.x<min_x) ? top.x : min_x;

				min_y = (top.y<min_y) ? top.y : min_y;

				max_x = (top.x>max_x) ? top.x : max_x;

				max_y = (top.y>max_y) ? top.y : max_y;

				sum_y += top.y; sum_x += top.x;



				//Add the 8-connected neighbours that are yet to be visited, to the queue

				for (k = top.y - 1; k <= top.y + 1; k++){

					for (l = top.x - 1; l <= top.x + 1; l++){

						if (k < 0 || l<0 || k >= img.rows || l >= img.cols || img.at<uchar>(k, l) == 0 || pixel_ID[k][l]>-1)

							continue;

						pt next = { l, k };

						pixel_ID[k][l] = id;

						open_list.push(next);

					}

				}

			}

			if (n_pixels < 20) //At least 20 pixels

				continue;

			blob nextcentre = { min_x, max_x, min_y, max_y, sum_x / n_pixels, sum_y / n_pixels, id };

			blobs.push_back(nextcentre);

			id++;

		}

	}



	cout << blobs.size(); //To test correctness; can use the vector as desired

}

static double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/*int main()
{
	Mat image = imread("G:\\deepika.png", CV_LOAD_IMAGE_COLOR);
	Mat dst = rgbToBinary(image, 362);
	dst = dilation(dst);
	namedWindow("Test", CV_WINDOW_NORMAL);
	imshow("Test", dst);
	dst = erosion(dst);
	namedWindow("Test2", CV_WINDOW_NORMAL);
	imshow("Test2", dst);
	dst = dilation(dst);
	namedWindow("Test3", CV_WINDOW_NORMAL);
	imshow("Test3", dst);
	waitKey();
	return 0;
}*/



/*int main()
{
	Mat image = imread("G:\\sample2.jpg", CV_LOAD_IMAGE_COLOR);
	int color[] = { 0, 0, 255 };
	int thres[] = { 100, 100, 100 };
	Mat dst = rgbcolorDetection(image, color, thres);
	Mat dest = rgbToBinary(image, 362);
	namedWindow("Image", CV_WINDOW_NORMAL);
	imshow("Image", dest);
	vector<blob> blobs;

	GetBlobs(dest, blobs);
	int i,j,k;
	cout << image.rows;
	cout << "\n";
	cout << image.cols;
	for (i = 0; i < blobs.size(); i++)
	{
		cout << "\n\n\n\n\n\n i";
		Mat tmp(image.rows, image.cols, CV_8UC1, Scalar(0));
		for (j = blobs[i].min_x; j < blobs[i].max_x; j++)
		{
			
			for (k = blobs[i].min_y; k < blobs[i].max_y; k++)
			{
				if (dst.at<uchar>(k,j) == 255)
					tmp.at<uchar>(k,j) = 255;
			}
		}
		char winname[10] = "Blob";
		winname[4] = (char)(i + '0');
		winname[5] = '\0';
		namedWindow(winname, CV_WINDOW_NORMAL);
		imshow(winname, tmp);
		

	}

	

	waitKey(0);
	return 0;

}
*/

void HoughTransform(Mat image)
{
	int i;
	Mat edges(image.rows, image.cols, CV_8UC1,Scalar(0));
	Canny(image, edges, 50, 150);
	namedWindow("Edges", CV_WINDOW_NORMAL);
	imshow("Edges", edges);
	int rho = 4, theta = 4;
	namedWindow("Detected Lines", CV_WINDOW_NORMAL);
	createTrackbar("Rho (0.25*x)", "Detected Lines", &rho, 20);
	createTrackbar("\nTheta (.25*x)", "Detected Lines", &theta, 40);
	while (1)
	{
		vector<Vec2f> lines;
		HoughLines(edges, lines, 0.25*rho, .25*theta*(CV_PI / 180), 100);
		Mat linesimg(image.rows, image.cols, CV_8UC1, Scalar(0));
		for (i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0];
			float theta = lines[i][1];
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			Point pt1(cvRound(x0 + 1000 * (-b)),
				cvRound(y0 + 1000 * (a)));
			Point pt2(cvRound(x0 - 1000 * (-b)),
				cvRound(y0 - 1000 * (a)));
			line(linesimg, pt1, pt2, Scalar(255, 255, 255), 2, 6);

		}

		imshow("Detected Lines", linesimg);

		int key = waitKey(33);
		if (key == 27)
			break;
	}
}
/*
int main()
{
	Mat image = imread("G:\\deepika.jpg", CV_LOAD_IMAGE_COLOR);
	colorDetecthsv();
	colorDetecthsv();
	waitKey();
	return 0;

}*/
void setLabel(Mat& im, const string label, vector<Point>& contour)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(label, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(im, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

/*int main()
{
	Mat src = imread("G:\\basic-shapes.png",CV_LOAD_IMAGE_COLOR);
	if (src.empty())
		return -1;
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);

	Mat bw;
	Canny(gray, bw, 0, 50, 5);

	Mat dst = src.clone();

	vector<vector<Point> > contours;
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Point> approx;


	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]),approx,arcLength(Mat(contours[i]), true) * 0.02,true);
 
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;

		if (approx.size() == 3)
		{

			setLabel(dst, "TRI", contours[i]);    // Triangles
			cout << "TRIANGLE\n";
		}
		else if (approx.size() >= 4 && approx.size() <= 6)
		{

			int vtc = approx.size();

			vector<double> cos;
			for (int j = 2; j < vtc + 1; j++)
				cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));


			sort(cos.begin(), cos.end());


			double mincos = cos.front();
			double maxcos = cos.back();


			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
			{

				Rect r = boundingRect(contours[i]);
				double ratio = abs(1 - (double)r.width / r.height);

				setLabel(dst, ratio <= 0.02 ? "SQU" : "RECT", contours[i]);
				cout << (ratio <= 0.02 ? "SQUARE\n" : "RECTANGLE\n");
			}
			else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
			{
				setLabel(dst, "PENTA", contours[i]);
				cout << "PENTAGON\n";
			}
			else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
			{

				setLabel(dst, "HEXA", contours[i]);

				cout << "HEXAGON\n";
			}
		}
		else
		{
		
			double area = cv::contourArea(contours[i]);
			Rect r = cv::boundingRect(contours[i]);
			int radius = r.width / 2;

			if (abs(1 - ((double)r.width / r.height)) <= 0.2 && abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
			{
				setLabel(dst, "CIR", contours[i]);
				cout << "CIR\n";
			}
		}
	} 
	imshow("src", src);
	imshow("dst",dst);
	
	waitKey(0);
	return 0;
}

*/

int shapeDetect(Mat src)
{
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	//int color[] = { 0, 0, 255 };
	//int thres[] = { 50, 50, 100 };
	//gray = rgbcolorDetection(src, color, thres);
	//imshow("RED", gray);

	Mat bw;
	Canny(gray, bw, 0, 50, 5);
	//imshow("REDD", bw);

	Mat dst = src.clone();

	vector<vector<Point> > contours;
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Point> approx;

	float imarea = src.rows * src.cols;
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);

		if (fabs(contourArea(contours[i])) < 0.05*imarea || !isContourConvex(approx))
			continue;
		if (approx.size() == 4)
			return 1;
		else if (approx.size() >= 7)
		{
			double area = cv::contourArea(contours[i]);
			Rect r = cv::boundingRect(contours[i]);
			int radius = r.width / 2;

			if (abs(1 - ((double)r.width / r.height)) <= 0.5 && abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.5)
			{
				return 0;
			}
		}
	}
}






void lane(Mat src)
{
	Mat image = src.clone();
	cvtColor(image, image, CV_BGR2GRAY);
	GaussianBlur(image, image, Size(7,7), 0, 0);
	Canny(image, image, 90,100);
	//imshow("Canny", image);
	vector<Vec4i> lines;
	Mat hl(image.rows,image.cols,CV_8UC1,Scalar(0));
	HoughLinesP(image, lines, 1, CV_PI / 180, 50,50,15);
	for (int i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(hl, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 2, CV_AA);
	}
	vector<Vec2f> lines2;
	HoughLines(image, lines2, 1, (CV_PI / 180), 100);
	Mat linesimg(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < lines2.size(); i++)
	{
		float rho = lines2[i][0];
		float theta = lines2[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		Point pt1(cvRound(x0 + 1000 * (-b)),
			cvRound(y0 + 1000 * (a)));
		Point pt2(cvRound(x0 - 1000 * (-b)),
			cvRound(y0 - 1000 * (a)));
		line(linesimg, pt1, pt2, Scalar(255), 2, 6);

	}
	Mat dst(image.rows, image.cols, CV_8UC1);
	bitwise_and(linesimg, hl, dst);
	HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 15);
	int freq[40] = { 0 };
	int sum = 0;
	float max = -1, min = 360;
	for (int i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		double slope = atan2((-l[3] + l[1]), (l[2] - l[0]));
		slope = (slope * 180 / CV_PI ) ;
		if (slope < 0)
			slope += 180;
		if (slope > max)
			max = slope;
		if (slope < min)
			min = slope;
		freq[(int)slope / 5]++;
		//cout << slope << "\n";
		//line(hl, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 2, CV_AA);
	}
	int k = 0;
	//cout << max << "  " << min << "\n";
	for (int i = 0; i < 37; i++)
	{
		if (freq[i] >= 5)
		{
			sum = sum + (i)* 5;
			k++;
		}
	}
	if (k == 0)
		k = 1;
	/**cout << sum / k << "\n";
	if(sum/k >= 80 && sum/k <= 100)
		cout << "Forward";
	else if (sum/k > 100 && sum/k < 150)
		cout << "Right";
	else if (sum/k < 80 && sum/k >40)
		cout << "Left";
	else
	{
		if (max  < 90 && min < 90)
			cout << "Right";
		else if (max > 90 && min > 90)
			cout << "Left";
		else
			cout << "Forward";
	
	}*/
	float s = max + min;
	if (s <= 200 && s >= 160)
		cout << "FORWARD\n";
	else if (s < 140)
		cout << "RIGHT\n";
	else if (s > 210)
		cout << "LEFT\n";


	namedWindow("Detected Lines", CV_WINDOW_NORMAL);
	namedWindow("Check", CV_WINDOW_NORMAL);
	namedWindow("Lines", CV_WINDOW_NORMAL);
	namedWindow("Lines2", CV_WINDOW_NORMAL);
	imshow("Detected Lines", linesimg);
	imshow("Check", image);
	imshow("Lines", hl);
	imshow("Lines2", dst);


}
Mat halfImage(Mat image)
{
	int r = image.rows / 2;
	int  j;
	Mat dst(r, image.cols, CV_8UC3);
	for (int i = 0; i < r; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			dst.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i + r, j)[0];
			dst.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i + r, j)[1];
			dst.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i + r, j)[2];
		}

	}
	return dst;
}


int main()
{
	//Mat image = imread("G:\\left.png");
	VideoCapture vid(1);
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	while (true)
	{
		Mat tmp;
		vid.read(tmp);
		if (tmp.empty())
			break;
		imshow("Original", tmp);
		/*int flag = shapeDetect(tmp);
		if (flag == 1)
			cout << "STOP AND .RIGHT\n";
		else if (flag == 0)
			cout << "STOP\n";
		else 
		{*/
			tmp = halfImage(tmp);
			lane(tmp);
		//}
		if (waitKey(25) == 27)
			break;;
	}
	//lane(image);
	waitKey();
	return 0;
}