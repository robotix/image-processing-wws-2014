#include"stdafx.h"
//#include<conio.h>
#include <iostream>
#include<queue>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<math.h>
#include "tserial.h"
#include "bot_control.h"

using namespace std;
using namespace cv;

serial s;

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

int gotopoint(Mat input, int shape_p0, int shape_p1, int shape_p2);

int main(){
//	flag(360, 640);
//	grscale_avg(image);
//	grscale(image);
//	binary_img(image);
//	invert_h_img(image);
//	histogram_t_grscale(image);
//	track_bars_gr(image);
//	track_bars_color(image);
/*	int t1, t2;
	namedWindow("Output Video", WINDOW_AUTOSIZE);						//VideoCapture()
	t2 = 255;
	t1 = 255;
	createTrackbar("Max Thresh", "Output Video", &t2, 255);
	createTrackbar("Min Thresh", "Output Video", &t1, 255);
	VideoCapture v("F:\\Not Essential\\Robotix\\10811906_10205173582159672_926820929_n.mp4");
	while (1){
		Mat frame;
		v >> frame;
		frame = greyscale_avg(frame);
//		frame = delta_edge(frame);
//		Canny(frame, frame, t2, t1,3);
		imshow("Output Video", frame);
		int a = waitKey(1);
		if (a == 27) break;
	}*/

/*	int i=0;
	Mat input2 = imread("F:\\Not Essential\\Robotix\\input_video_img.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input Object", input2);
	waitKey(0);
	Mat temp_img(input2.rows, input2.cols, CV_8UC1, Scalar(0));
	for (int y = 0; y < input2.rows; y++){
		for (int x = 0; x < input2.cols; x++){
			if (input2.at<uchar>(y, x) >200) temp_img.at<uchar>(y, x) = 255;
		}
	}
	namedWindow("White Object", WINDOW_AUTOSIZE);
	imshow("White Object", temp_img);
	waitKey(0);
	
	vector<vector<Point>> c;
	findContours(temp_img, c, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	for (i = 0; i < 4; i++){
		vector<Point> app;
		approxPolyDP(c[i], app, arcLength(c[i], true)*0.02, true);
		cout << app.size()<<"\n";
		waitKey(0);
	}*/

	int temp_scale, temp_scale2;
	int color_p[2], shape_p[3];					//priority sequence
/*	cout << "Enter color priority.\n1 for red. 2 for blue.\nPriority 1 : ";
	cin >> color_p[0];
	cout << "Priority 2 : ";
	cin >> color_p[1];
	cout << "Enter shape priority.\n1 for circle. 2 for square or rectangle. 3 for triangle.\nPriority 1 : ";
	cin >> shape_p[0];
	cout << "Priority 2 : ";
	cin >> shape_p[1];
	cout << "Priority 3 : ";
	cin >> shape_p[2];*/

	VideoCapture go_position("F:\\Not Essential\\Robotix\\Falling_Shapes_Problem_Statement_WWS2014-2014-12-14_17.30.42-.mp4");
	Mat go_frame;
	namedWindow("Go Position", WINDOW_AUTOSIZE);

	VideoCapture my_position(0);
	Mat position_frame;
	namedWindow("My Position", WINDOW_AUTOSIZE);

	namedWindow("temp frame", WINDOW_AUTOSIZE);
	while (1){
		int go_x = 0, npixel = 0;     //target position

		go_position >> go_frame;
		imshow("Go Position", go_frame);
		temp_scale = go_frame.cols;
		Mat temp_frame(go_frame.rows, go_frame.cols, CV_8UC1, Scalar(0));
		//		Mat go_frame_hsl(go_frame.rows, go_frame.cols, CV_8UC3);
		//		cvtColor(go_frame, go_frame_hsl, CV_BGR2HLS);

		for (int y = 0; y < go_frame.rows * 2 / 3; y++){
			for (int x = 0; x < go_frame.cols; x++){
				if (go_frame.at<Vec3b>(y, x)[0]>200 && go_frame.at<Vec3b>(y, x)[1] < 40 && go_frame.at<Vec3b>(y, x)[2] < 40){
					npixel++;
					temp_frame.at<uchar>(y, x) = 255;
				}
				else temp_frame.at<uchar>(y, x) = 0;
			}
		}
		if (npixel < 20){
			npixel = 0;
			for (int y = 0; y < go_frame.rows * 2 / 3; y++){
				for (int x = 0; x < go_frame.cols; x++){
					if (go_frame.at<Vec3b>(y, x)[0] < 40 && go_frame.at<Vec3b>(y, x)[1] < 40 && go_frame.at<Vec3b>(y, x)[2] > 200){
						npixel++;
						temp_frame.at<uchar>(y, x) = 255;
					}
					else temp_frame.at<uchar>(y, x) = 0;
				}
			}
		}
		if (npixel < 20){
			npixel = 0;
			for (int y = 0; y < go_frame.rows * 2 / 3; y++){
				for (int x = 0; x < go_frame.cols; x++){
					if (go_frame.at<Vec3b>(y, x)[0]>200 && go_frame.at<Vec3b>(y, x)[1]>200 && go_frame.at<Vec3b>(y, x)[2] < 40){
						npixel++;
						temp_frame.at<uchar>(y, x) = 255;
					}
					else temp_frame.at<uchar>(y, x) = 0;
				}
			}
		}
		if (npixel < 20){
			npixel = 0;
			for (int y = 0; y < go_frame.rows * 2 / 3; y++){
				for (int x = 0; x < go_frame.cols; x++){
					if (go_frame.at<Vec3b>(y, x)[0]<40 && go_frame.at<Vec3b>(y, x)[1]>200 && go_frame.at<Vec3b>(y, x)[2] < 40){
						npixel++;
						temp_frame.at<uchar>(y, x) = 255;
					}
					else temp_frame.at<uchar>(y, x) = 0;
				}
			}
		}
		go_x = 0; npixel = 0;
		for (int y = 0; y < temp_frame.rows; y++){
			for (int x = 0; x < temp_frame.cols; x++){
				if (temp_frame.at<uchar>(y, x)>200){
					npixel++;
					go_x += x;
				}
			}
		}
		go_x = go_x / npixel;
//		go_x = gotopoint(temp_frame, shape_p[0], shape_p[1], shape_p[2]);
//		go_x = 300;

		my_position >> position_frame;				//My Position
		imshow("My Position", position_frame);
		temp_scale2 = position_frame.cols;
		Mat position_frame_hls(position_frame.rows, position_frame.cols, CV_8UC3);
		cvtColor(position_frame, position_frame_hls, CV_BGR2HLS_FULL);
		int my_x = 0, n = 0;
		for (int y = 0; y < position_frame_hls.rows; y++){
			for (int x = 0; x < position_frame_hls.cols; x++){
				if ((position_frame_hls.at<Vec3b>(y, x)[0]>220 || position_frame_hls.at<Vec3b>(y, x)[0] < 20) /*&& position_frame_hls.at<Vec3b>(y, x)[1] > 100 && position_frame_hls.at<Vec3b>(y, x)[2] < 180 && position_frame_hls.at<Vec3b>(y, x)[2] > 60*/){
					my_x += x;
					n++;
				}
			}
		}
		Mat display(go_frame.rows, go_frame.cols, CV_8UC1, Scalar(0));
		for (int y = 0; y < display.rows * 2 / 3; y++){
			for (int x = 0; x < display.cols; x++){
				if (go_frame.at<Vec3b>(y, x)[0]<40 || go_frame.at<Vec3b>(y, x)[1]<40 || go_frame.at<Vec3b>(y, x)[2]<40){
					display.at<uchar>(y, x) = 255;
				}
			}
		}
		my_x = my_x / n;    /*my_x is my position*/
		for (int y = display.rows - 100; y < display.rows; y++){
			int i, j;
			if (go_x < 40){
				i = 0;
				j = go_x + 40;
			}
			else if (go_x>(display.cols - 41)){
				i = go_x - 40;
				j = display.cols;
			}
			else{
				i = go_x - 40;
				j = go_x + 40;
			}
			for (int x = i; x < j; x++){
				display.at<uchar>(y, x) = 255;
			}
		}
		imshow("temp frame", display);
		cout << go_x << " " << my_x << " ";
		/*	while (1){
				Mat frame;
				position >> frame;

				Mat p2(frame.rows, frame.cols, CV_8UC1);
				p2 = makebinary(frame,150);
				namedWindow("Output Image");
				imshow("Output Image", p2);
				int a = waitKey(2);
				if (a == 27) break;
				}*/

		float scale = temp_scale2 / temp_scale;					//Go to point
		my_x = my_x / scale;
		if ((my_x - go_x) > 5) cout << "115\n";//s.send_data(115);//...go left-backward||s==115
		if ((my_x - go_x) < -5) cout << "119\n";//s.send_data(119);//...go right-forward||w==119
		int a = waitKey(1);
		if (a == 27) break;
	}
	
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
	Mat bin_img(image.rows, image.cols, CV_8UC1,Scalar(0));
	int a, i, x, y;
	for (y = 0; y < image.rows; y++){
		for (x = 0; x < image.cols; x++){
			a = (image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2]) / 3;
			if (a < t) bin_img.at<uchar>(y, x) = 255;
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
	for (y = 0; y < image.rows; y++){
		edge_img.at<uchar>(y, 0) = 0;
		edge_img.at<uchar>(y, (image.cols - 1)) = 0;
	}
	for (x = 0; x < image.cols; x++){
		edge_img.at<uchar>(0, x) = 0;
		edge_img.at<uchar>((image.rows - 1), x) = 0;
	}
	for (y = 0; y < (image.rows - 2); y++){
		for (x = 0; x < (image.cols - 2); x++){
			dx = (gr_img.at<uchar>(y, x + 2) + gr_img.at<uchar>(y + 1, x + 2) + gr_img.at<uchar>(y + 2, x + 2) - gr_img.at<uchar>(y, x) - gr_img.at<uchar>(y + 1, x) - gr_img.at<uchar>(y + 2, x));
			dy = (gr_img.at<uchar>(y + 2, x) + gr_img.at<uchar>(y + 2, x + 1) + gr_img.at<uchar>(y + 2, x + 2) - gr_img.at<uchar>(y, x) - gr_img.at<uchar>(y, x + 1) - gr_img.at<uchar>(y, x + 2));
			m = sqrt((dx*dx) + (dy*dy));
			if (m>255) m = 255;
			edge_img.at<uchar>(y + 1, x + 1) = m;
		}
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
	Mat img(hsv_img.rows, hsv_img.cols, CV_8UC1);
	int x, y, z, a, b, c;
	for (y = 0; y < hsv_img.rows; y++){
		for (x = 0; x < hsv_img.cols; x++){
			a = hsv_img.at<Vec3b>(y, x)[0];
			b = hsv_img.at<Vec3b>(y, x)[1];
			c = hsv_img.at<Vec3b>(y, x)[2];
			if ((a >= (h1 - t1)) && (a <= (h1 + t1)) && (b >= (s1 - t2)) && (b <= (s1 + t2)) && (c >= (v1 - t3)) && (c <= (v1 + t3))) img.at<uchar>(y, x) = 255;
			else img.at<uchar>(y, x) = 0;
		}
	}
	return img;
}

int gotopoint(Mat input, int shape_p0, int shape_p1, int shape_p2){
	Mat a(input.rows, input.cols, CV_8SC1, Scalar(-1));
	int m, n, count = 0;
	Point p; queue<Point> q;

	for (int y = 1; y < (input.rows - 1); y++){
		for (int x = 1; x < (input.cols - 1); x++){
			if ((input.at<uchar>(y, x)> 200) && (a.at<char>(y, x) == -1)){
				count++;
				p.x = x; p.y = y;
				q.push(p);
				a.at<char>(y, x) = 0;
				while (!q.empty()){
					p = q.front();
					m = p.y; n = p.x;
					for (int i = m - 1; i <= m + 1; i++){
						for (int j = n - 1; j <= n + 1; j++){
							if (input.at<uchar>(i, j) > 200 && a.at<schar>(i, j) == -1){
								a.at<char>(i, j) = 0;
								p.x = j; p.y = i;
								q.push(p);
							}
						}
					}
					q.pop();
					a.at<char>(m, n) = count;
				}
			}
		}
	}
	int check = 1, xmax = 0, xmin = input.cols, ymax = 0, ymin = input.rows;
	while (check <= count){
		int pixel = 0;
		for (int y = 1; y < (input.rows*2/3) - 1; y++){
			for (int x = 1; y < input.cols - 1; x++){
				if (a.at<char>(y, x) == check){
					pixel++;
					if (y > ymax) ymax = y;
					if (y < ymin) ymin = y;
					if (x > xmax) xmax = x;
					if (x < xmin) xmin = x;
				}
			}
		}
		int yaxis = ymax - ymin, xaxis = xmax - xmin;
		int area = yaxis*xaxis, priority;
		if (pixel>100){
			if (pixel > area*0.7 && pixel < area*0.9 && shape_p0 == 1) return (xmax - xmin) / 2;
			if (pixel > area*0.9 && shape_p0 == 2) return (xmax - xmin) / 2;
			if (pixel > area / 2 && pixel < area*0.6 && shape_p0 == 3) return (xmax - xmin) / 2;
		}
		check++;
	}
	check = 1;
	while (check <= count){
		int pixel = 0;
		for (int y = 1; y < (input.rows * 2 / 3) - 1; y++){
			for (int x = 1; y < input.cols - 1; x++){
				if (a.at<char>(y, x) == check){
					pixel++;
					if (y > ymax) ymax = y;
					if (y < ymin) ymin = y;
					if (x > xmax) xmax = x;
					if (x < xmin) xmin = x;
				}
			}
		}
		int yaxis = ymax - ymin, xaxis = xmax - xmin;
		int area = yaxis*xaxis, priority;
		if (pixel>100){
			if (pixel > area*0.7 && pixel < area*0.9 && shape_p1 == 1) return (xmax - xmin) / 2;
			if (pixel > area*0.9 && shape_p1 == 2) return (xmax - xmin) / 2;
			if (pixel > area / 2 && pixel < area*0.6 && shape_p1 == 3) return (xmax - xmin) / 2;
		}
		check++;
	}
	check = 1;
	while (check <= count){
		int pixel = 0;
		for (int y = 1; y < (input.rows * 2 / 3) - 1; y++){
			for (int x = 1; y < input.cols - 1; x++){
				if (a.at<char>(y, x) == check){
					pixel++;
					if (y > ymax) ymax = y;
					if (y < ymin) ymin = y;
					if (x > xmax) xmax = x;
					if (x < xmin) xmin = x;
				}
			}
		}
		int yaxis = ymax - ymin, xaxis = xmax - xmin;
		int area = yaxis*xaxis, priority;
		if (pixel>100){
			if (pixel > area*0.7 && pixel < area*0.9 && shape_p2 == 1) return (xmax - xmin) / 2;
			if (pixel > area*0.9 && shape_p2 == 2) return (xmax - xmin) / 2;
			if (pixel > area / 2 && pixel < area*0.6 && shape_p2 == 3) return (xmax - xmin) / 2;
		}
		check++;
	}

	return input.cols/2;
}