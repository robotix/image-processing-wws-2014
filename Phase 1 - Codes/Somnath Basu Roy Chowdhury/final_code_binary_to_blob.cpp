/*//Canny edge
	int freq[256];
	memset(freq, 0, sizeof(freq));
	for (i = 0; i < image.rows; i++)
	{
		for (j = 0; j < image.cols; j++)
		{
			freq[(int)image.at<uchar>(i, j)]++;
		}
	}
	int sum = 0, Sum = 0, median;
	for (i = 0; i < 256; i++)
	{
		sum += freq[i];
	}
	for (i = 0; i < 256; i++)
	{
		Sum += freq[i];
		if (Sum>sum / 2)
		{
			median = i;
			break;
		}
	}
	int lower = median / 3;
	int upper = 2 * median / 3;
	Canny(image2, Canny_image, lower, upper, 3);
	
	//Hough lines
	int thres = 150,max;
	Mat image_line(image.rows, image.cols, CV_8UC1);
	vector<Vec2f> lines;
	HoughLines(Canny_image, lines, 1, CV_PI / 180, thres);
	for (i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		
		double x0 = a*rho, y0 = b*rho;
		if (abs(a) < 0.05)
			max = y0;
		pt1.x = cvRound(x0 + 1500 * (-b));
		pt1.y = cvRound(y0 + 1500 * (a));
		pt2.x = cvRound(x0 - 1500 * (-b));
		pt2.y = cvRound(y0 - 1500 * (a));
		line(image_line, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}
	cout << max << endl;
	namedWindow("Hough_lines", CV_WINDOW_AUTOSIZE);
	imshow("Hough_lines", image_line);
	Canny improvement
	for (i = 0; i < Canny_image.rows; i++)
	{
		for (j = 0; j < Canny_image.cols; j++)
		{
			if (i <= max)
				Canny_image.at<uchar>(i, j) = 0;
			
		}
	}
	namedWindow("Canny_Output", CV_WINDOW_AUTOSIZE);
	imshow("Canny_Output", Canny_image);
	vector<Vec2f> lines1;
	int thres1=30;
	while (lines1.size() > 2)
	{

		HoughLines(Canny_image, lines1, 1, CV_PI / 180, thres1);
		thres1 += 5;
	}
	for (i = 0; i < lines1.size(); i++)
	{
		float rho = lines1[i][0], theta = lines1[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);

		double x0 = a*rho, y0 = b*rho;
		if (abs(a) < 0.05)
			max = y0;
		pt1.x = cvRound(x0 + 1500 * (-b));
		pt1.y = cvRound(y0 + 1500 * (a));
		pt2.x = cvRound(x0 - 1500 * (-b));
		pt2.y = cvRound(y0 - 1500 * (a));
		line(image_line, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}
	cout << max << endl;
	namedWindow("Hough_lines", CV_WINDOW_AUTOSIZE);
	imshow("Hough_lines", image_line);*/