void HoughTransform(Mat image)
{
int i;
Mat edges(image.rows, image.cols, CV_8UC1,Scalar(0));
Canny(image, edges, 50, 150);
namedWindow("Edges", CV_WINDOW_NORMAL);
imshow("Edges", edges);
int rho = 4, theta = 4;
namedWindow("Detected Lines", CV_WINDOW_NORMAL);
createTrackbar("Rho (0.25*x)", "Detected Lines", &rho, 20);
createTrackbar("\nTheta (.25*x)", "Detected Lines", &theta, 40);
while (1)
{
vector<Vec2f> lines;
HoughLines(edges, lines, 0.25*rho, .25*theta*(CV_PI / 180), 100);
Mat linesimg(image.rows, image.cols, CV_8UC1, Scalar(0));
for (i = 0; i < lines.size(); i++)
{
float rho = lines[i][0];
float theta = lines[i][1];
double a = cos(theta), b = sin(theta);
double x0 = a*rho, y0 = b*rho;
Point pt1(cvRound(x0 + 1000 * (-b)),
cvRound(y0 + 1000 * (a)));
Point pt2(cvRound(x0 - 1000 * (-b)),
cvRound(y0 - 1000 * (a)));
line(linesimg, pt1, pt2, Scalar(255, 255, 255), 2, 6);

}

imshow("Detected Lines", linesimg);

int key = waitKey(33);
if (key == 27)
break;
}
}