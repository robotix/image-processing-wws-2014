#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include<math.h>
#include<conio.h>
#include<malloc.h>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace cv;
#define pie 3.1414

/* ------------------------------------------------------------------------ --
--                                                                          --
--                        PC serial port connection object                  --
--                           for non-event-driven programs                  --
--                                                                          --
--                                                                          --
--                                                                          --
--  Copyright @ 2001          Thierry Schneider                             --
--                            thierry@tetraedre.com                         --
--                                                                          --
--                                                                          --
--                                                                          --
-- ------------------------------------------------------------------------ --
--                                                                          --
--  Filename : sertest2.cpp                                                 --
--  Author   : Thierry Schneider                                            --
--  Created  : April 4th 2000                                               --
--  Modified : April 8th 2001                                               --
--  Plateform: Windows 95, 98, NT, 2000 (Win32)                             --
-- ------------------------------------------------------------------------ --
--                                                                          --
--  This software is given without any warranty. It can be distributed      --
--  free of charge as long as this header remains, unchanged.               --
--                                                                          --
-- ------------------------------------------------------------------------ */




/* ---------------------------------------------------------------------- */
#ifndef TSERIAL_H
#define TSERIAL_H

#include <stdio.h>
#include <windows.h>


enum serial_parity  { spNONE,    spODD, spEVEN };


/* -------------------------------------------------------------------- */
/* -----------------------------  Tserial  ---------------------------- */
/* -------------------------------------------------------------------- */
class Tserial
{
    // -------------------------------------------------------- //
protected:
    char              port[10];                      // port name "com1",...
    int               rate;                          // baudrate
    serial_parity     parityMode;
    HANDLE            serial_handle;                 // ...

    // ++++++++++++++++++++++++++++++++++++++++++++++
    // .................. EXTERNAL VIEW .............
    // ++++++++++++++++++++++++++++++++++++++++++++++
public:
                  Tserial();
                 ~Tserial();
    int           connect          (char *port_arg, int rate_arg,
                                    serial_parity parity_arg);
    void          sendChar         (char c);
    void          sendArray        (char *buffer, int len);
    char          getChar          (void);
    int           getArray         (char *buffer, int len);
    int           getNbrOfBytes    (void);
    void          disconnect       (void);
};
/* -------------------------------------------------------------------- */

#endif TSERIAL_H



class serial{

  private:
        // private attributes
		Tserial *com;
  public:


	serial() {
			
		 }
	
	bool startDevice(char *port,int speed)
	{
		com = new Tserial();
		if (com!=0)
		{
			if(com->connect(port, speed, spNONE))
				printf("Not Connected...\n");
			else
				printf("Connected..\n");
			return TRUE;
		}
		else
			return FALSE; 
	}

	void stopDevice()
	{
		com->disconnect();
        // ------------------
        delete com;
        com = 0;
	}

	void send_data(unsigned char data)
	{
	//	unsigned char data = 0;
	
		
		com->sendChar(data);
		printf("%c",data);
		
	}
};





void copyGrayColored(Mat image,Mat greyImage){
	int i,j;
	for(i=0;i<greyImage.rows;i++){
		for(j=0;j<greyImage.cols;j++){
			greyImage.at<uchar>(i,j)= image.at<Vec3b>(i,j)[0]*0.56+image.at<Vec3b>(i,j)[1]*0.33+image.at<Vec3b>(i,j)[2]*0.11;
		}
	}
	return ;
}


int main(){
	//serial comm;
	//comm.startDevice("COM14", 9600);
	VideoCapture  V(1);
	int upper=200,lower=48;
	namedWindow("video",WINDOW_NORMAL);
	createTrackbar("controlLower","video",&lower,255);
	createTrackbar("controlUpper","video",&upper,255);
	while(1){
		Mat frame;
		V >> frame;
		Mat gray(frame.rows,frame.cols,CV_8UC1),edge(frame.rows,frame.cols,CV_8UC1,Scalar(0));
		copyGrayColored(frame,gray);
		Canny(frame,edge,upper,lower);
		Mat edgeHalf(edge.rows,edge.cols,CV_8UC1,Scalar(0));
		for(int i=0;i<edge.rows/2;i++){
			for(int j=0;j<edge.cols;j++){
				edgeHalf.at<uchar>(i,j)=0;
			}
		}
		for(int i=edge.rows/2;i<edge.rows;i++){
			for(int j=0;j<edge.cols;j++){
				edgeHalf.at<uchar>(i,j)=edge.at<uchar>(i,j);
			}
		}
		vector<Vec2f> lines;
		HoughLines(edgeHalf, lines, 2, CV_PI/180, 150, 0, 0 );
		Mat useImage(edge.rows,edge.cols,CV_8UC3,Scalar(0,0,0));
		int countLines=0;
		double thetaSum=0;
		for( size_t i = 0; i < lines.size(); i++ ){
			countLines++;
			thetaSum+=lines[i][1];
			float rho,theta; 
			rho = lines[i][0];
			theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000*(-b));
			pt1.y = cvRound(y0 + 1000*(a));
			pt2.x = cvRound(x0 - 1000*(-b));
			pt2.y = cvRound(y0 - 1000*(a));
			line( useImage, pt1, pt2, Scalar(255,255,255), 3, CV_AA);
		}

		if (countLines == 0){
			countLines = 1;
		}
		double value;
		value = thetaSum / countLines;
		if (value/CV_PI*180 > 100){
			cout << "a" << endl;
		}
		else if (value/CV_PI*180 < 80){
			cout << "d" << endl;
		}
		else cout << "w"<<endl;

		imshow("video",useImage);
		char a= waitKey(33);
		if(a==27) break;
		//char data;
		//data='w';
		//comm.send_data(data);
	}
	//comm.stopDevice();
	return 0;
}