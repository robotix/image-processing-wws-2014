#include"stdafx.h"
//#include<conio.h>
#include <iostream>
#include<queue>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void flag(int row,int col){
	int i, x, y;
	Mat flag, image2, image(row, col, CV_8UC3), image_red;
	for (y = 0; y < row / 3; y++){
		for (x = 0; x < col; x++){
			image.at<Vec3b>(y, x)[0] = 0;
			image.at<Vec3b>(y, x)[1] = 128;
			image.at<Vec3b>(y, x)[2] = 255;
		}
	}
	for (y = (row / 3); y < (row * 2 / 3); y++){
		for (x = 0; x < col; x++){
			for (i = 0; i < 3; i++){
				image.at<Vec3b>(y, x)[i] = 255;
			}
		}
	}
	for (y = (row * 2 / 3); y < row; y++){
		for (x = 0; x < col; x++){
			image.at<Vec3b>(y, x)[0] = 76;
			image.at<Vec3b>(y, x)[1] = 177;
			image.at<Vec3b>(y, x)[2] = 34;
		}
	}
	namedWindow("My Flag", WINDOW_AUTOSIZE);
	imshow("My Flag", image);
	waitKey(0);
	destroyWindow("My Flag");
}
void grscale_avg(Mat image){
	Mat gr_img(image.rows, image.cols, CV_8UC1);
	int a, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			gr_img.at<uchar>(y, x) = a;
		}
	}
	namedWindow("My Grey Window avg", WINDOW_AUTOSIZE);
	imshow("My Grey Window avg", gr_img);
	waitKey(0);
//	destroyWindow("My Grey Window avg");
}
void grscale(Mat image){
	Mat gr_img(image.rows, image.cols, CV_8UC3);
	int   x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			gr_img.at<Vec3b>(y, x)[0] = 0.56*image.at<Vec3b>(y, x)[0];
			gr_img.at<Vec3b>(y, x)[1] = 0.33*image.at<Vec3b>(y, x)[1];
			gr_img.at<Vec3b>(y, x)[2] = 0.11*image.at<Vec3b>(y, x)[2];

		}
	}
	imshow("My Grey Window", gr_img);
	waitKey(0);
	destroyWindow("My Grey Window");
}
void binary_img(Mat image){
	Mat bin_img(image.rows, image.cols, CV_8UC1);
	int a, i, x, y, t;
	cout << "Enter the thresh : " ;
	cin >> t;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y,x)[2]) / 3;
			if (a < t)
				i = 0;
			else
				i = 255;
			bin_img.at<uchar>(y, x) = i;
		}
	}
	namedWindow("My Binary Window",WINDOW_AUTOSIZE);
	imshow("My Binary Window", bin_img);
	waitKey(0);
	destroyWindow("My Binary Window");
}
void invert_h_img(Mat image){
	Mat inv_img(image.rows, image.cols, CV_8UC3);
	int a, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.rows - y -1);
			inv_img.at<Vec3b>(a, x)[0] = image.at<Vec3b>(y, x)[0];
			inv_img.at<Vec3b>(a, x)[1] = image.at<Vec3b>(y, x)[1];
			inv_img.at<Vec3b>(a, x)[2] = image.at<Vec3b>(y, x)[2];
		}
	}
	imshow("My Window", image);
	namedWindow("My Invert Window", WINDOW_AUTOSIZE);
	imshow("My Invert Window", inv_img);
	waitKey(0);
	destroyWindow("My Invert Window");
	destroyWindow("My Window");
}
void histogram_t_grscale(Mat image){
	Mat gr_img(image.rows, image.cols, CV_8UC1);
	Mat bin_img(image.rows, image.cols,CV_8UC1);
	Mat histogram(500, 256, CV_8UC1);
	int a, x, y, h[256], i, area, t = 0, cnt = 0, m, p;
	
	
	area = image.rows*image.cols;
	for (i = 0; i < 256; i++){
		h[i] = 0;
	}
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			gr_img.at<uchar>(y, x) = a;
			h[a]++;
		}
	}
	namedWindow("My Grey Window avg", WINDOW_AUTOSIZE);
	imshow("My Grey Window avg", gr_img);
	waitKey(0);

	m = area / 500;
	for (x = 0; x < 256; x++){
		p = h[x] / m;
		for (y = (499 - p); y < 500; y++){
			histogram.at<uchar>(y, x) = 0;
		}
	}
	imshow("My histogram", histogram);
	waitKey(0);
	
	for (t = 0; cnt <= (area / 2) && t < 256; t++){
		cnt += h[a];
	}
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = gr_img.at<uchar>(y,x);
			if (a < t)
				i = 0;
			else
				i = 255;
			bin_img.at<uchar>(y, x) = i;
		}
	}
	namedWindow("My Binary Window", WINDOW_AUTOSIZE);
	imshow("My Binary Window", bin_img);
	waitKey(0);
}
void track_bars_gr(Mat image);
Mat makebinary(Mat image, int t);

void track_bars_color(Mat image);
Mat makebinary_color(Mat image, int t1, int t2, int t3);

Mat edge(Mat image,int t);
Mat greyscale_avg(Mat image);

Mat delta_edge(Mat image);
Mat x_delta_edge(Mat image);

Mat dilation(Mat image);
Mat erosion(Mat image);
Mat edge_thick(Mat image,int t);

Mat avg_filter(Mat image);
Mat midian_filter(Mat image);
Mat gaussian_filter(Mat image);

Mat detect_color(Mat hsv_img, int h1, int s1, int v1, int t1,int t2, int t3);

void bfs(Mat image);
void bfs_rec(Mat bfs_img);

int main(){
	Mat image = imread("F:\\Facebook\\baby-girl-names-2014.jpg", CV_LOAD_IMAGE_COLOR);
	Mat edge_img(image.rows, image.cols, CV_8UC1);
	Mat delta_edge_img(image.rows, image.cols, CV_8UC1);
	Mat x_delta_edge_img(image.rows, image.cols, CV_8UC1);
	Mat edge_thick_img(image.rows, image.cols, CV_8UC1);
	Mat midian_filter_img(image.rows, image.cols, CV_8UC1);
	Mat avg_filter_img(image.rows, image.cols, CV_8UC1);
	Mat gaussian_filter_img(image.rows, image.cols, CV_8UC1);
	Mat temp_img(image.rows, image.cols, CV_8UC1);
	Mat temp_img2(image.rows, image.cols, CV_8UC1);
	Mat canny_img(image.rows, image.cols, CV_8UC1);
	int a,c, i, t, t1, t2, t3, bin;

//	flag(360, 640);
//	grscale_avg(image);
//	grscale(image);
//	binary_img(image);
//	invert_h_img(image);
//	histogram_t_grscale(image);
//	track_bars_gr(image);
//	track_bars_color(image);

/*	cout << "Enter the threshold : ";								//edge()-threshold
	cin >> t;
	namedWindow("Edge Image", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Edge Image", &t, 255);
	imshow("Edge Image", edge_img);
	while (1){
		Mat edge_img = edge(image, t);
		imshow("Edge Image", edge_img);
		c = waitKey(33);
		if (c == 27) break;
	}
	destroyWindow("Edge Image");*/

/*	delta_edge_img = delta_edge(image).clone();						//delta_edge()
//	Mat delta_edge_img2= delta_edge(delta_edge_img).clone();
	imshow("Edge Image", delta_edge_img);
	waitKey(0);
	destroyWindow("Edge Image");*/

/*	x_delta_edge_img = x_delta_edge(image);							//x_delta_edge()
	imshow("Edge Image x-", x_delta_edge_img);
	waitKey(0);
	destroyWindow("Edge Image x-");*/

/*	cout << "Enter the threshold : ";								//edge_thick()
	cin >> t;
	namedWindow("Edge Thick Image", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Edge Thick Image", &t, 255);
	imshow("Edge Thick Image", edge_thick_img);
	while (1){
		Mat edge_thick_img = edge_thick(image, t);
		imshow("Edge Thick Image", edge_thick_img);
		c = waitKey(33);
		if (c == 27) break;
	}
	destroyWindow("Edge Thick Image");*/

/*	temp_img = greyscale_avg(image);									//avg_filter()
	avg_filter_img = avg_filter(temp_img);
	imshow("Average Filter Image", avg_filter_img);
	waitKey(0);
	destroyWindow("Average Filter Image");
	midian_filter_img = midian_filter(temp_img);						//midian_filter()
	imshow("Midian Filter Image", midian_filter_img);
	waitKey(0);
	destroyWindow("Midian Filter Image");*/
/*	gaussian_filter_img = gaussian_filter(temp_img);					//gaussian_filter()
	imshow("Gaussian Filter Image", gaussian_filter_img);
	waitKey(0);*/

/*	cout << "Enter the Upper threshold : ";								//for Canny()
	cin >> t2;
	cout << "Enter the Lower threshold : ";
	cin >> t1;*/
/*	namedWindow("Canny Window", WINDOW_AUTOSIZE);						//Canny()
	createTrackbar("Upper", "Canny Window", &t2,255);
	createTrackbar("Lower", "Canny Window", &t1,255);
	Canny(temp_img, canny_img, t1, t2);
	imshow("Canny Window", canny_img);
	while (1){
		Canny(temp_img, canny_img, t1, t2, 3);
		imshow("Canny Window", canny_img);
		c = waitKey(33);
		if (c == 27) break;
	}*/

	namedWindow("Video Window", WINDOW_AUTOSIZE);						//VideoCapture()
	createTrackbar("Max Thresh", "Video Window", &t2, 255);
	createTrackbar("Min Thresh", "Video Window", &t1, 255);
//	Canny(temp_img, canny_img, t1, t2);
	VideoCapture v("G:\\Video Songs\\Linkin Park - Crawling.mp4");
	while (1){
		Mat frame;
		v >> frame;
//		frame = greyscale_avg(frame);
		frame = delta_edge(frame);
//		Canny(frame, frame, t2, t1,3);
		imshow("Video Window", frame);
		a = waitKey(3);
		if (a == 27) break;
	}

	Mat hsv_img = imread("F:\\Facebook\\best-friends1.jpg");
	int h1, s1, l1;
	cout << "H : ";
	cin >> h1;
	cout << "S : ";
	cin >> s1;
	cout << "L : ";
	cin >> l1;
	cout << "Threshold for H, S, L: ";
	cin >> t1;
	cin >> t2;
	cin >> t3;
	namedWindow("Color Detection", WINDOW_AUTOSIZE);
//	createTrackbar("H");
	Mat hsv_img2 = detect_color(hsv_img, h1, s1, l1, t1, t2, t3);
	
	imshow("Color Detecttion", hsv_img2);
	waitKey(0);
	destroyWindow("Color Detection");

Mat bfs_img = imread("F:\\Not Essential\\Robotix\\test_img.png");
	imshow("BFS Window", bfs_img);
	waitKey(0);
	bfs(bfs_img);
//	bfs_rec(bfs_img);

	return 0;
}


void track_bars_gr(Mat image){
	int t, c;
	cout << "ENTER AN INITIAL THRESH : ";
	cin >> t;
	namedWindow("Binary Window", WINDOW_AUTOSIZE);
	createTrackbar("Threshold", "Binary Window", &t, 255);
	while (1){
		Mat img = makebinary(image, t);
		imshow("Binary Window", img);
		c = waitKey(33);
		if (c == 27) break;
	}
//	destroyWindow("Binary Window");
}
Mat makebinary(Mat image, int t){
	Mat bin_img(image.rows, image.cols, CV_8UC1);
	int a, i, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			if (a < t)
				i = 0;
			else
				i = 255;
			bin_img.at<uchar>(y, x) = i;
		}
	}
	return bin_img;
}
void track_bars_color(Mat image){
	int t1, t2, t3, c;
	cin >> t1;
	cin >> t2;
	cin >> t3;
	namedWindow("Color Binary Window", WINDOW_AUTOSIZE);
	createTrackbar("Blue","Color Binary Window", &t1, 255);
	createTrackbar("Green","Color Binary Window", &t2, 255);
	createTrackbar("Red","Color Binary Window", &t3, 255);
	while (1){
		Mat img = makebinary_color(image, t1, t2, t3);
		imshow("Color Binary Window", img);
		c = waitKey(33);
		if (c == 27) break;
	}

}
Mat makebinary_color(Mat image, int t1, int t2, int t3){
	Mat bin_img(image.rows, image.cols, CV_8UC3);
	int a, i, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = image.at<Vec3b>(y, x)[0];
			if (a < t1) i = 0;
			else i = 255;
			bin_img.at<Vec3b>(y, x)[0] = i;
			
			a = image.at<Vec3b>(y, x)[1];
			if (a < t2) i = 0;
			else i = 255;
			bin_img.at<Vec3b>(y, x)[1] = i;
			
			a = image.at<Vec3b>(y, x)[2];
			if (a < t3) i = 0;
			else i = 255;
			bin_img.at<Vec3b>(y, x)[2] = i;
		}
	}
	return bin_img;
}
Mat greyscale_avg(Mat image){
	Mat gr_img(image.rows, image.cols, CV_8UC1);
	int a, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			gr_img.at<uchar>(y, x) = a;
		}
	}
	return gr_img;
}
Mat edge(Mat image,int t){
	Mat edge_img(image.rows, image.cols, CV_8UC1);
	Mat gr_img = greyscale_avg(image);
	int x, y, a,d,min,max,x1,y1;
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			min = 255;
			max = 0;
			for (x1 = x; x1 < (x + 3); x1++){
				for (y1 = y; y1 < (y + 3); y1++){
					if (gr_img.at<uchar>(y1, x1) < min) min = gr_img.at<uchar>(y1, x1);
					if (gr_img.at<uchar>(y1, x1) > max) max = gr_img.at<uchar>(y1, x1);
				}
			}
			d = max - min;
			if (d >= t) a = 255;
			else a = 0;
			edge_img.at<uchar>((y + 1), (x + 1)) = a;
		}
	}
	for (y = 0; y < image.rows; y++){
		edge_img.at<uchar>(y, 0) = 0;
		edge_img.at<uchar>(y, (image.cols - 1)) = 0;
	}
	for (x = 0; x < image.cols; x++){
		edge_img.at<uchar>(0, x) = 0;
		edge_img.at<uchar>((image.rows - 1), x) = 0;
	}
	return edge_img;
}
Mat delta_edge(Mat image){
	Mat edge_img(image.rows, image.cols, CV_8UC1);
	Mat gr_img = greyscale_avg(image);
	int a, x, y, dx, dy, m;
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			dx = ((gr_img.at<uchar>(y, x + 2) + gr_img.at<uchar>(y + 1, x + 2) + gr_img.at<uchar>(y + 2, x + 2)) - (gr_img.at<uchar>(y, x) + gr_img.at<uchar>(y + 1, x) + gr_img.at<uchar>(y + 2, x)));
			dy = ((gr_img.at<uchar>(y + 2, x) + gr_img.at<uchar>(y + 2, x + 1) + gr_img.at<uchar>(y + 2, x + 2)) - (gr_img.at<uchar>(y, x) + gr_img.at<uchar>(y, x + 1) + gr_img.at<uchar>(y, x + 2)));
			m = sqrt((dx*dx) + (dy*dy));
			if (m>255) m = 255;
			edge_img.at<uchar>(y + 1, x + 1) = m;
		}
	}
	for (y = 0; y < image.rows; y++){
		edge_img.at<uchar>(y, 0) = 0;
		edge_img.at<uchar>(y, (image.cols - 1)) = 0;
	}
	for (x = 0; x < image.cols; x++){
		edge_img.at<uchar>(0, x) = 0;
		edge_img.at<uchar>((image.rows - 1), x) = 0;
	}
	return edge_img;
}
Mat x_delta_edge(Mat image){
	Mat edge_img(image.rows, image.cols, CV_8UC1);
	Mat gr_img = greyscale_avg(image);
	int a, i, x, y, dx, m;
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			dx = ((gr_img.at<uchar>(y, x + 2) + gr_img.at<uchar>(y + 1, x + 2) + gr_img.at<uchar>(y + 2, x + 2)) - (gr_img.at<uchar>(y, x) + gr_img.at<uchar>(y + 1, x) + gr_img.at<uchar>(y + 2, x)));		
			m = sqrt(pow(dx, 2));
			if (m>255) m = 255;
			edge_img.at<uchar>(y + 1, x + 1) = m;
		}
	}
	for (y = 0; y < image.rows; y++){
		edge_img.at<uchar>(y, 0) = 0;
		edge_img.at<uchar>(y, (image.cols - 1)) = 0;
	}
	for (x = 0; x < image.cols; x++){
		edge_img.at<uchar>(0, x) = 0;
		edge_img.at<uchar>((image.rows - 1), x) = 0;
	}
	return edge_img;
}
Mat edge_thick(Mat image,int t){
	Mat edge_img = edge(image, t);
	Mat i1(image.rows, image.cols, CV_8UC1), i2(image.rows, image.cols, CV_8UC1);
	i1 = dilation(edge_img);
	i2 = erosion(i1);
	return i2;
}
Mat dilation(Mat image){
	Mat i1(image.rows, image.cols, CV_8UC1);
	int y, x, w, b,x1,y1,a;
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			w = 0;
			b = 0;
			for (x1 = x; x1 < (x + 3); x1++){
				for (y1 = y; y1 < (y + 3); y1++){
					if (image.at<uchar>(y1, x1) == 255) w++;
					else b++;
				}
			}
			if ((w<b)&&(w>0)&&(b>0)) a = 0;
			else a = 255;
			i1.at<uchar>((y + 1), (x + 1)) = a;
		}
	}
	for (y = 0; y < image.rows; y++){
		i1.at<uchar>(y, 0) = 0;
		i1.at<uchar>(y, (image.cols - 1)) = 0;
	}
	for (x = 0; x < image.cols; x++){
		i1.at<uchar>(0, x) = 0;
		i1.at<uchar>((image.rows - 1), x) = 0;
	}
	return i1;
}
Mat erosion(Mat image){
	Mat i2(image.rows, image.cols, CV_8UC1);
	int y, x, w, b, x1, y1, a;
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			w = 0;
			b = 0;
			for (x1 = x; x1 < (x + 3); x1++){
				for (y1 = y; y1 < (y + 3); y1++){
					if (image.at<uchar>(y1, x1) == 255) w++;
					else b++;
				}
			}
			if ((w<b) && (w>0) && (b>0)) a = 255;
			else a = 0;
			i2.at<uchar>((y + 1), (x + 1)) = a;
		}
	}
	for (y = 0; y < image.rows; y++){
		i2.at<uchar>(y, 0) = 0;
		i2.at<uchar>(y, (image.cols - 1)) = 0;
	}
	for (x = 0; x < image.cols; x++){
		i2.at<uchar>(0, x) = 0;
		i2.at<uchar>((image.rows - 1), x) = 0;
	}
	return i2;
}
Mat avg_filter(Mat image){
	Mat img(image.rows, image.cols, CV_8UC1);
	int x, y, a, t,x1,y1;
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			a = 0;;
			for (x1 = x; x1 < (x + 3); x1++){
				for (y1 = y; y1 < (y + 3); y1++){
					a += image.at<uchar>(y1, x1);
				}
			}
			img.at<uchar>((y + 1), (x + 1)) = (a / 9);
		}
	}
	for (y = 0; y < (image.rows - 1); y++){
		img.at<uchar>(y, 0) = image.at<uchar>(y, 0);
		img.at<uchar>(y, (image.cols-1)) = image.at<uchar>(y, (image.cols-1));
	}
	for (x = 0; x < (image.cols - 1); x++){
		img.at<uchar>(0, x) = image.at<uchar>(0, x);
		img.at<uchar>((image.rows-1), x) = image.at<uchar>((image.rows-1), x);
	}
	return img;
}
Mat midian_filter(Mat image){
	Mat img(image.rows, image.cols, CV_8UC1);
	int x, y, x1, y1, a[9], i, j, temp;
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			i = 0;
			for (x1 = x; x1 < (x + 3); x1++){
				for (y1 = y; y1 < (y + 3); y1++){
					a[i] = image.at<uchar>(y1, x1);
					i++;
				}
			}
			for (i = 0; i < 9; i++){
				for (j = 1; j < i; j++){
					if (a[i-1]>a[i]){
						temp = a[i-1];
						a[i-1] = a[i];
						a[i] = temp;
					}
				}
			}
			img.at<uchar>((y + 1), (x + 1)) = a[4];
		}
	}
	for (y = 0; y < (image.rows - 1); y++){
		img.at<uchar>(y, 0) = image.at<uchar>(y, 0);
		img.at<uchar>(y, (image.cols - 1)) = image.at<uchar>(y, (image.cols - 1));
	}
	for (x = 0; x < (image.cols - 1); x++){
		img.at<uchar>(0, x) = image.at<uchar>(0, x);
		img.at<uchar>((image.rows - 1), x) = image.at<uchar>((image.rows - 1), x);
	}
	return img;
}
Mat gaussian_filter(Mat image){
	Mat gr_img = greyscale_avg(image);
	Mat img(image.size(), CV_8UC1);
	return img;
}
Mat detect_color(Mat hsv_img, int h1, int s1, int v1, int t1,int t2,int t3){
	cvtColor(hsv_img, hsv_img, CV_BGR2HLS_FULL);
//	cvtColor(hsv_img, hsv_img, CV_BGR2HLS_FULL);
	Mat img(hsv_img.rows, hsv_img.cols, CV_8UC1);
	int x, y, z, a, b, c;
	for (y = 0; y < hsv_img.rows; y++){
		for (x = 0; x < hsv_img.cols; x++){
			a = hsv_img.at<Vec3b>(y, x)[0];
			b = hsv_img.at<Vec3b>(y, x)[1];
			c = hsv_img.at<Vec3b>(y, x)[2];
//			if ((a >= h1 - t) && (a <= h1 + t)) img.at<uchar>(y, x) = 255;
			if ((a >= (h1 - t1)) && (a <= (h1 + t1)) && (b >= (s1 - t2)) && (b <= (s1 + t2)) && (c >= (v1 - t3)) && (c <= (v1 + t3))) img.at<uchar>(y, x) = 255;
			else img.at<uchar>(y, x) = 0;
		}
	}
	return img;
}
void bfs(Mat image){
	Mat img(image.rows,image.cols, CV_8SC1);
	Mat img2(image.rows,image.cols, CV_8UC1);
	int x, y, x1, y1, i,j, a=1,b,c=0,waitKey_int;
//	imshow("temp window", image);
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++) img.at<schar>(y, x) = -1;
	}
	queue<Point> q;
	Point p;

	for (y = 1; y < (image.rows - 1); y++){
		for (x = 1; x < (image.cols - 1); x++){
			if (image.at<uchar>(y, x) == 255 && img.at<schar>(y, x) == -1){
				q.push(Point(x, y));
				img.at<schar>(y, x) = 0;
				x1 = x-1;
				y1 = y-1;
				c = 0;
				while (q.empty() == 0){
					b = 0;
					c++;
					for (i = x1-1; i < (x1 + 2); i++){
						for (j = y1-1; j < (y1 + 2); j++){
							if (image.at<uchar>(y1, x1) == 255 && img.at<schar>(y1, x1) == -1){
								q.push(Point(x1, y1));
								img.at<schar>(y1, x1) = 0;
								b++;
							}
						}
					}
					p = q.front();
					x1 = p.x;
					y1 = p.y;
					if (b == 0){
						img.at<schar>(y, x) = a;
						q.pop();
					}
				}
				if(c>0) a++;
			}
//			a++;
		}
	}
	for (c = 1; c < a; c++){
		for (y = 0; y < image.rows; y++){
			for (x = 0; x < image.cols; x++){
				if (img.at<schar>(y, x) == c) img2.at<uchar>(y, x) = 255;
				else img2.at<uchar>(y, x) = 0;
			}
		}
		imshow("Body Detected", img2);
		waitKey_int=waitKey(0);
		if (waitKey_int == 27) break;
	}
}
void bfs_rec(Mat bfs_img){

}