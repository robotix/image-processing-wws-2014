Mat noiseless(image.rows, image.cols, CV_8UC1);
for (i = 0; i < image.rows; ++i)
	{
		for (j = 0; j < image.cols; ++j)
		{
			int k, l, black=0, white=0;
			for (k = i - 1; k <= i + 1; ++k)
			{
				for (l = j - 1; l <= j + 1; ++l)
				{
					if (k >= 0 && k < image.rows && l >= 0 && l < image.cols)
					{
						if (binary1.at<uchar>(k, l) == 0)
							black++;
						else
							white++;
					}
				}
			}
			if (white>black)
				noiseless.at<uchar>(i, j) = 255;
			else
				noiseless.at<uchar>(i, j) = 0;
		}
	}