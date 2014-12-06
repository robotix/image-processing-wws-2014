#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture vid("G:\\images\\ClayCarUpdate2.mp4");
    int pos = 0;
	namedWindow("Output", CV_WND_PROP_FULLSCREEN);
	int fps = vid.get(CV_CAP_PROP_FPS);
	int maxtime = (vid.get(CV_CAP_PROP_FRAME_COUNT)) / fps;
	cvCreateTrackbar("Position", "Output", &pos, 1000*maxtime);
	while (1)
	{
		Mat image;
		vid.read(image);
		imshow("Output", image);
		setTrackbarPos("Position", "Output", pos);
		vid.set(CV_CAP_PROP_POS_MSEC, pos);
		pos += 1000 / fps;
		int ikey = waitKey(30);
		if (ikey == 27)
			break;
	}
	waitKey(0);
	return 0;
}