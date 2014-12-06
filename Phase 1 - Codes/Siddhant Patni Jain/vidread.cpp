#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	int ikey;
	VideoCapture vid(0);
	while (1)
	{
		Mat temp;
		vid.read(temp);
		namedWindow("Video", WINDOW_AUTOSIZE);
		imshow("Video", temp);
		ikey = waitKey(50);
		if (ikey == 27)
			break;
	}
}
#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	int ikey;
	VideoCapture vid(0);
	while (1)
	{
		Mat temp;
		vid.read(temp);
		namedWindow("Video", WINDOW_AUTOSIZE);
		imshow("Video", temp);
		ikey = waitKey(50);
		if (ikey == 27)
			break;
	}
}
