#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;
using namespace cv;


void load_image(char name[])
{
	Mat image;
	image = imread(name, CV_LOAD_IMAGE_COLOR);
	namedWindow("LOAD_IMAGE", CV_WINDOW_NORMAL);
	imshow("LOAD_IMAGE", image);
	waitKey(0);
}

void imageCreator()
{
	int i, j;
	Mat image(200, 300, CV_8UC3, Scalar(0, 0, 0));
	char winName[] = "imageCreator";
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
	waitKey(0);
}

Mat rgbToBinary(Mat image,int threshold)
{
	int i, j, avg = 0;;
	Mat image2(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			avg = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2])/3;
			if (avg<threshold)
			{
				image2.at<uchar>(i, j) = 0;
			}
			else
				image2.at<uchar>(i, j) = 255;
		}

	}
	/*char winName[] = "rgbToBinary";
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, image2);
	waitKey(0);*/
	return image2;
}


Mat RGB_to_Graysacle(Mat image)
{
	float A = 0.1140, B = 0.5870, C = 0.2989;
	Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0));
	int i, j, sum = 0;;
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			sum = A*image.at<Vec3b>(i, j)[0] + B*image.at<Vec3b>(i, j)[1] + C*image.at<Vec3b>(i, j)[2];
			gray.at<uchar>(i,j) = sum;
		}

	}
	/*char winName[] = "RGB To Graysacle";
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, image);
	waitKey();
	*/
	return gray;
}


void histogramThreshold(char imgName[])
{
	int i, j, sum = 0;
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
	waitKey();
	*/
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
	char winName[] = "histogramThreshold";
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, image);
	waitKey(0);
}


double getMean(Mat image, int i, int j)
{
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
	return ((double)sum / t);

}


void adaptiveThreshold(char image_name[])
{
	Mat image = imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
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
	namedWindow("adaptiveThreshold", CV_WINDOW_NORMAL);
	imshow("adaptiveThreshold", image2);
	waitKey(0);
}


Mat globalMean(char image_name[])
{
	Mat image = imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
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
	/*namedWindow("globalMean", CV_WINDOW_NORMAL);
	imshow("globalMean", image);
	waitKey(0);*/
	return image;
}


/*
void rgb_to_bin_with_trackbar(char image_name[])
{
	Mat image = imread(image_name, CV_LOAD_IMAGE_COLOR);
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
*/

int getDiff(Mat image, int i, int j)
{
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
	return (max - min);
}


Mat EdgeDetection(Mat image2,int threshold)
{
	Mat image3(image2.rows, image2.cols, CV_8UC1, Scalar(0));
	int i, j;
	for (i = 0; i < image2.rows; i++)
	{
		for (j = 0; j < image2.cols; j++)
		{
			int diff = getDiff(image2, i, j);
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


void CannyEdge(Mat image)
{
	int threshold = 20;
	namedWindow("CannyEdgeDetection", CV_WINDOW_AUTOSIZE);
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



/*
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
*/


int getBorW(Mat image, int i, int j)
{
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
	if (black > white)
		return 0;
	else
		return 255;
}


Mat NormalNoise(Mat src)
{
	int i, j;
	//Mat src2 = rgbToBinary(src, 127);
	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < src.rows; i++)
	{
		for (j = 0; j < src.cols; j++)
		{
			dst.at<uchar>(i, j) = getBorW(src, i, j);
		}
	}
	return dst;
}


Mat rgbcolorDetection(Mat image, int color[], int t[])
{
	int i, j;
	Mat dst(image.rows, image.cols, CV_8UC1, Scalar(0));
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


Mat hsvcolorDetection(Mat src, int color[], int t[])
{
	Mat image;
	int i, j;
	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));
	cvtColor(src, image, CV_BGR2HSV);
	//imshow("Color Detection", image);
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

Mat image_global;

void onMousergb(int event, int x, int y, int, void*)
{
if (event != CV_EVENT_LBUTTONDOWN)
return;
int color[] = { image_global.at<Vec3b>(y, x)[0], image_global.at<Vec3b>(y, x)[1], image_global.at<Vec3b>(y, x)[2] };
int thres[] = { 100, 100, 100 };
Mat dst = rgbcolorDetection(image_global, color, thres);
imshow("Mouse_CB_Color_Detection", dst);
}


/*
void onMousehsv(int event, int x, int y, int, void*)
{
if (event != CV_EVENT_LBUTTONDOWN)
return;
Mat ima;
cvtColor(image, ima, CV_BGR2HSV);
int color[] = { ima.at<Vec3b>(y, x)[0], ima.at<Vec3b>(y, x)[1], ima.at<Vec3b>(y, x)[2] };
int thres[] = { 10,100,200 };
Mat dst = hsvcolorDetection(image, color, thres);
imshow("Color Detection", dst);
}
*/


/*
void video()
{
	VideoCapture vid(0);
	int threshold = 127, position = 0;
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
*/


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


void GetBlobs(Mat img, vector<blob>& blobs)
{
	int i, j, k, l, r = img.rows, c = img.cols, id = 1;
	vector<vector<int> > pixel_ID(r, vector<int>(c, -1)); //Stores ID of a pixel; -1 means unvisited
	queue<pt> open_list; //Breadth-First-Search hence queue of points

	for (i = 1; i< r ; i++){
		for (j = 1; j< c ; j++){
			if (img.at<uchar>(i, j) == 255 || pixel_ID[i][j]>-1)
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
						if (k<0||l<0||k>=r||l>=c||img.at<uchar>(k, l) == 255 || pixel_ID[k][l]>-1)
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
	/*Mat blob_image(img.rows, img.cols, CV_8UC1, Scalar(0));
	for (i = 0; i < r; i++){
		for (j = 0; j < c; j++){
			if (pixel_ID[i][j]>-1) blob_image.at<uchar>(i, j) = 255;
		}
	}
	namedWindow("GetBlobs", CV_WINDOW_NORMAL);
	imshow("GetBlobs", blob_image);
	waitKey(0);*/
}


int maxi(float a, float b){
	return (a >= b) ? a : b;
}


int mini(float a, float b){
	return (a <= b) ? a : b;
}

double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void setLabel(Mat& im, const string label, vector<Point>& contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(label, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(im, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}


void video1()
{
	VideoCapture vid(1);
	if (!vid.isOpened()) return;
	Mat original_image;
	namedWindow("video", CV_WINDOW_NORMAL);
	while (1){
		vid >> original_image;
		namedWindow("ORIGINAL_FEED\n");
		imshow("ORIGINAL_FEED", original_image);

		/*Mat gray;
		cvtColor(original_image,gray, CV_BGR2GRAY);
		Mat edges_shape;
		Canny(gray, edges_shape, 0, 50, 5);
		vector<vector<Point> > contours;
		findContours(edges_shape.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		vector<Point> approx;
		Mat copy = original_image.clone();
		for (int i = 0; i < contours.size(); i++){
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		
		if (fabs(contourArea(contours[i])) < 2000 || !isContourConvex(approx))
		continue;
		if (approx.size() == 3)
		{
		//setLabel(copy, "TRI", contours[i]);
		//cout << "TRIANGLE\n";
		}
		if (approx.size() >= 4 && approx.size() <= 6)
		{
		int vtc = approx.size();
		vector<double> cos;
		for (int j = 2; j < vtc + 1; j++)
		cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));
		sort(cos.begin(), cos.end());
		double mincos = cos.front();
		double maxcos = cos.back();

		int threshold_area=2000;
		if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3 && fabs(contourArea(contours[i])) >=(threshold_area)){
		//setLabel(copy, "RECT", contours[i]);
		cout << "STOP & RIGHT\n";
		}
		else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27){
		//setLabel(copy, "PENT", contours[i]);
		//cout << "PENTAGON\n";
		}
		else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45){
		//setLabel(copy, "HEX", contours[i]);
		//cout << "HEXAGON\n";
		}
		}
		else
		{
		double area = contourArea(contours[i]);
		Rect r = boundingRect(contours[i]);
		int radius = r.width / 2;
		if (abs(1 - ((double)r.width / r.height)) <= 0.2 &&
		abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2){
		//setLabel(copy, "CIRC", contours[i]);
		//cout << "CIRCLE\n";
		}
		}
		}*/
	
		Mat grayscale_image1, grayscale_image;
		grayscale_image1 = RGB_to_Graysacle(original_image);
		GaussianBlur(grayscale_image1, grayscale_image, Size(9, 9), 0);
		Mat edges, color_final1(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0)), color_final2(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
		Canny(grayscale_image, edges, 15, 60, 3, false);
		/*namedWindow("EDGES", CV_WINDOW_NORMAL);
		imshow("EDGES", edges);
		waitKey(0);*/
		vector<Vec2f> lines1;
		HoughLines(edges, lines1, 1, CV_PI / 180, 100, 0, 0);
		for (size_t i = 0; i < lines1.size(); i++)
		{
			float rho = lines1[i][0], theta = lines1[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(color_final1, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
		}

		vector<Vec4i> lines;
		HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(color_final2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
			//cout << "Slope of line " << (l[3] - l[1]) / (l[2] - l[0]) << "\n";
		}
		//namedWindow("LINES", CV_WINDOW_NORMAL);
		Mat color_final(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
		bitwise_and(color_final1, color_final2, color_final);
		Mat black_white_final(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
		grayscale_image1 = RGB_to_Graysacle(color_final);
		GaussianBlur(grayscale_image1, grayscale_image, Size(9, 9), 0);
		Canny(grayscale_image, edges, 15, 60, 3, false);

		int max1 = -1, min1 = 100000;
		vector<Vec4i> lines2;
		HoughLinesP(edges, lines2, 1, CV_PI / 180, 50, 50, 10);
		for (size_t i = 0; i < lines2.size(); i++)
		{
			Vec4i l = lines2[i];
			line(black_white_final, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
			//cout << "Slope of line ";
			if (atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) >= 0) {
				//cout << atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) << "\n";
				max1 = maxi(max1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI));
				min1 = mini(min1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI));
			}
			else {
				//cout << (atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) + 180)) << "\n";
				max1 = maxi(max1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) + 180);
				min1 = mini(min1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) + 180);
			}
		}
		//cout << min1 << " " << max1 << " "<<(max1+min1)<<"\n";
		if (min1 <= 90 && max1 <= 90) cout << "RIGHT\n";
		else if (min1 >= 90 && max1 >= 90) cout << "LEFT\n";
		else{
			if ((max1 + min1) >= 160 && (max1 + min1) <= 200) cout << "FORWARD\n";
			else if ((max1 + min1) > 200) cout << "RIGHT\n";
			else if ((max1 + min1) < 160) cout << "LEFT\n";
		}
		namedWindow("FINAL", CV_WINDOW_NORMAL);
		imshow("FINAL", black_white_final);
		int key = waitKey(5);
		if (key == 27)
			break;
	}
}


int dilation(Mat image, int i, int j)
{
	int m, n;
	int b = 0, w = 0;
	for (m = i - 1; m <= i + 1; m++){
		for (n = j - 1; n <= j + 1; n++){
			if (m < 0 || n < 0 || m >= image.rows || n >= image.cols)
				continue;
			if (image.at<uchar>(i, j) == 0) b++;
			else if (image.at<uchar>(i, j) == 255) w++;
		}
	}
	return (b>w) ? 0 : 255;
}


int erosion(Mat image, int i, int j)
{
	int m, n;
	int b = 0, w = 0;
	for (m = i - 1; m <= i + 1; m++){
		for (n = j - 1; n <= j + 1; n++){
			if (m < 0 || n < 0 || m >= image.rows || n >= image.cols)
				continue;
			if (image.at<uchar>(i, j) == 0) b++;
			else if (image.at<uchar>(i, j)==255) w++;
		}
	}
	if (b == 9) return 0;
	else if (w == 9) return 255;
	else return (b<w) ? 0 : 255;
}


Mat noise_dil_ero(Mat image)
{
	//Mat img2 = rgbToBinary(image, 127);
	Mat result(image.rows, image.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.cols; j++){
			result.at<uchar>(i, j) = dilation(image, i, j);
		}
	}
	namedWindow("dilation", CV_WINDOW_NORMAL);
	imshow("dilation", result);
	waitKey(0);
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.cols; j++){
			result.at<uchar>(i, j) = erosion(image, i, j);
		}
	}
	namedWindow("erosion", CV_WINDOW_NORMAL);
	imshow("erosion", result);
	waitKey(0);
	return result;
}



int main()
{
	/*char image_name[] = "D:\image_right1.jpg";
	Mat original_image;
	original_image = imread(image_name, CV_LOAD_IMAGE_COLOR);
	namedWindow("ORIGINAL_IMAGE", CV_WINDOW_NORMAL);
	imshow("ORIGINAL_IMAGE", original_image);
	waitKey(0);*/
	//load_image(image_name);
	
	//imageCreator();
	
	/*Mat binary_image;
	binary_image = rgbToBinary(original_image, 127);
	namedWindow("BINARY_IMAGE", CV_WINDOW_NORMAL);
	imshow("BINARY_IMAGE", binary_image);
	waitKey(0);*/

	/*Mat grayscale_image;
	grayscale_image = RGB_to_Graysacle(original_image);
	namedWindow("GRAYSCALE_IMAGE", CV_WINDOW_NORMAL);
	imshow("GRAYSCALE_IMAGE", grayscale_image);
	waitKey(0);*/

	//histogramThreshold(image_name);
	//adaptiveThreshold(image_name);
	/*Mat global_mean_image;
	global_mean_image=globalMean(image_name);
	namedWindow("GLOBAL_MEAN", CV_WINDOW_NORMAL);
	imshow("GLOBAL_MEAN", global_mean_image);
	waitKey(0);*/

	/*Mat edge_image;
	edge_image=EdgeDetection(original_image,100);
	namedWindow("EDGE_IMAGE", CV_WINDOW_NORMAL);
	imshow("EDGE_IMAGE", edge_image);
	waitKey(0);*/

	//EdgeDetect(original_image,"EDGE_TRACKBAR_IMAGE");

	//CannyEdge(original_image);

	/*Mat noise_removal;
	noise_removal = NormalNoise(binary_image);
	namedWindow("NOISELESS_IMAGE", CV_WINDOW_NORMAL);
	imshow("NOISELESS_IMAGE", noise_removal);
	waitKey(0);*/

	/*Mat color_detection;
	int color[] = { 148, 27, 239 };
	int t[] = { 100, 100, 100 };
	color_detection = rgbcolorDetection(original_image,color,t);
	namedWindow("COLOR_DETECT_IMAGE", CV_WINDOW_NORMAL);
	imshow("COLOR_DETECT_IMAGE", color_detection);
	waitKey(0);*/

	/*Mat hsv_color_detection;
	int color[] = { 327, 90, 90 };
	int t[] = { 30, 100, 200 };
	hsv_color_detection = hsvcolorDetection(original_image, color,t);
	namedWindow("HSV_COLOR_DETECT_IMAGE", CV_WINDOW_NORMAL);
	imshow("HSV_COLOR_DETECT_IMAGE", hsv_color_detection);
	waitKey(0);*/

	/*vector<blob> blobs;
	GetBlobs(noise_removal, blobs);*/
	
	//video1();


	/*Mat dil_ero;
	dil_ero = noise_dil_ero(binary_image);
	namedWindow("dilation_erosion", CV_WINDOW_NORMAL);
	imshow("dilation_erosion", dil_ero);
	waitKey(0);*/


	/*image_global = original_image.clone();
	namedWindow("Mouse_CB_Color_Detection", CV_WINDOW_NORMAL);
	setMouseCallback("ORIGINAL_IMAGE",onMousergb, NULL);
	waitKey(0);*/

	/*Mat gray;
	cvtColor(original_image,gray, CV_BGR2GRAY);
	Mat edges;
	Canny(gray, edges, 0, 50, 5);
	vector<vector<Point> > contours;
	findContours(edges.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	vector<Point> approx;
	Mat copy = original_image.clone();
	for (int i = 0; i < contours.size(); i++){
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
		continue;
		if (approx.size() == 3)
		{
			setLabel(copy, "TRI", contours[i]);
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

			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3){
				setLabel(copy, "RECT", contours[i]);
				cout << "RECTANGLE\n";
			}
			else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27){
				setLabel(copy, "PENT", contours[i]);
				cout << "PENTAGON\n";
			}
			else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45){
				setLabel(copy, "HEX", contours[i]);
				cout << "HEXAGON\n";
			}
		}
		else
		{
			double area = contourArea(contours[i]);
			Rect r = boundingRect(contours[i]);
			int radius = r.width / 2;
			if (abs(1 - ((double)r.width / r.height)) <= 0.2 &&
				abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2){
				setLabel(copy, "CIRC", contours[i]);
				cout << "CIRCLE\n";
			}
		}
	}
	namedWindow("ORIGINAL_IMAGE", CV_WINDOW_NORMAL);
	namedWindow("SHAPE_DETECTION", CV_WINDOW_NORMAL);
	imshow("ORIGINAL_IMAGE", original_image);
	imshow("SHAPE_DETECTION", copy);
	waitKey(0);
	*/

	
	/*Mat edges,color_final;
	Canny(grayscale_image, edges,15, 45, 3);
	namedWindow("EDGES", CV_WINDOW_NORMAL);
	imshow("EDGES", edges);
	waitKey(0);
	cvtColor(edges, color_final, CV_GRAY2BGR);
	namedWindow("COLOR_INIT", CV_WINDOW_NORMAL);
	imshow("COLOR_INIT", color_final);
	waitKey(0);
	vector<Vec2f> lines;
	HoughLines(edges, lines, 1, CV_PI / 180, 150, 0, 0);
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(color_final, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(color_final, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}
	namedWindow("LINES", CV_WINDOW_NORMAL);
	imshow("LINES", color_final);
	waitKey(0);
	*/
	
	video1();

	/*Mat grayscale_image1, grayscale_image;
	grayscale_image1 = RGB_to_Graysacle(original_image);
	GaussianBlur(grayscale_image1, grayscale_image, Size(9, 9), 0);
	Mat edges, color_final1(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0)), color_final2(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
	Canny(grayscale_image, edges, 15, 60, 3, false);
	namedWindow("EDGES", CV_WINDOW_NORMAL);
	imshow("EDGES", edges);
	waitKey(0);
	//cvtColor(edges, color_final1, CV_GRAY2BGR);
	//cvtColor(edges, color_final2, CV_GRAY2BGR);
	/*namedWindow("COLOR_INIT", CV_WINDOW_NORMAL);
	imshow("COLOR_INIT", color_final);
	waitKey(0);
	vector<Vec2f> lines1;
	HoughLines(edges, lines1, 1, CV_PI / 180, 100, 0, 0);
	for (size_t i = 0; i < lines1.size(); i++)
	{
		float rho = lines1[i][0], theta = lines1[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(color_final1, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}

	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(color_final2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
		//cout << "Slope of line " << (l[3] - l[1]) / (l[2] - l[0]) << "\n";
	}
	//namedWindow("LINES", CV_WINDOW_NORMAL);
	Mat color_final(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
	bitwise_and(color_final1, color_final2, color_final);
	Mat black_white_final(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
	grayscale_image1 = RGB_to_Graysacle(color_final);
	GaussianBlur(grayscale_image1, grayscale_image, Size(9, 9), 0);
	Canny(grayscale_image, edges, 15, 60, 3, false);

	int max1=-1, min1= 100000;
	vector<Vec4i> lines2;
	HoughLinesP(edges, lines2, 1, CV_PI / 180, 50, 50, 10);
	for (size_t i = 0; i < lines2.size(); i++)
	{
		Vec4i l = lines2[i];
		line(black_white_final, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
		//cout << "Slope of line ";
		if (atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) >= 0) {
			//cout << atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) << "\n";
			max1 = maxi(max1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI));
			min1 = mini(min1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI));
		}
		else {
			//cout << (atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI) + 180)) << "\n";
			max1 = maxi(max1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI)+180);
			min1 = mini(min1, atan2f((-l[3] + l[1]), (l[2] - l[0]))*(180 / CV_PI)+180);
		}
	}
	//cout << min1 << " " << max1 << " "<<(max1+min1)<<"\n";
	if (min1 <= 90 && max1 <= 90) cout << "RIGHT\n";
	else if (min1 >= 90 && max1 >= 90) cout << "LEFT\n";
	else{
		if ((max1 + min1) >= 160 && (max1 + min1) <= 200) cout << "FORWARD\n";
		else if ((max1 + min1) > 200) cout << "RIGHT\n";
		else if ((max1 + min1) < 160) cout << "LEFT\n";
	}
	namedWindow("FINAL", CV_WINDOW_NORMAL);
	imshow("FINAL", black_white_final);
	waitKey(0);
	*/
	return 0;
}


