#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

Mat RedDetectBGR(Mat img, int min_thresh, int max_thresh){

    Mat result(img.rows,img.cols,CV_8UC1);          //the result image matrix is initialized
    int i,j,r = img.rows, c = img.cols;

    for(i=0;i<r;i++){                               //loop through all rows
        for(j=0;j<c;j++){                           //loop through all columns

            Vec3b colours = img.at<Vec3b>(i,j);     //extract 3 channel pixel information in a vector
            if(colours[2]>=min_thresh && colours[1]<max_thresh && colours[0]<max_thresh)
                                                    //enforce condition on uchar value of each channel 
                result.at<uchar>(i,j) = 255;        //particular pixel is made white
            else
                result.at<uchar>(i,j) = 0;          //particular pixel is made black
        }
    }

    return result;
}

int main(){

    string fname;
    cout<<"Enter name of file:";
    cin>>fname;

    Mat image = imread(fname);                      
    int minthresh = 0, maxthresh = 100;            

    string win_name = "Colour-extracted image";
    namedWindow(win_name,CV_WINDOW_NORMAL);
    imshow("Original image",image);
    createTrackbar("Low Threshold",win_name,&minthresh,255);
    createTrackbar("High Threshold",win_name,&maxthresh,255);

    while(1){
        Mat result = RedDetectBGR(image,minthresh,maxthresh);
        imshow(win_name,result);
        char ch = waitKey(33);
        if(ch==27)
            break;
    }
    
    image.release();
    destroyAllWindows();
    return 0;
}