#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	string fname;
	cout << "Enter File Name:";
	cin >> fname;
	Mat imgOriginal;
	namedWindow("Dashboard",WINDOW_NORMAL);
	int LowH = 0 , HighH = 179;
	int LowS = 0 , HighS = 255;
  int LowV = 0 , HighV = 255;

	createTrackbar("LowH", "Dashboard", &LowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Dashboard", &HighH, 179);
  createTrackbar("LowS", "Dashboard", &LowS, 255); //Saturation (0 - 255)
 	createTrackbar("HighS", "Dashboard", &HighS, 255);
  createTrackbar("LowV", "Dashboard", &LowV, 255); //Value (0 - 255)
 	createTrackbar("HighV", "Dashboard", &HighV, 255);

  while (true)
  {
    Mat imgHSV;
    imgOriginal = imread(fname,CV_LOAD_IMAGE_COLOR);
   	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
  	Mat imgThresholded;
   	inRange(imgHSV, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), imgThresholded); //Threshold the image
      
  	//morphological opening (remove small objects from the foreground)
  	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   	//morphological closing (fill small holes in the foreground)
  	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

   	imshow("Thresholded Image", imgThresholded); //show the thresholded image
  	imshow("Original", imgOriginal); //show the original image
 
    if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
  }
   return 0;
}