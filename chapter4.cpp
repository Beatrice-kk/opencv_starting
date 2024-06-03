#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;


//////////     Draw shapes and text     /////////////
void main() {
	//blank image
	Mat img(512, 512, CV_8UC3, Scalar(255, 0, 255));//BGR
	
	circle(img, Point(156, 150), 50, Scalar(45, 89, 77),FILLED);
	rectangle(img, Point(130, 250), Point(160, 300), Scalar(250, 230, 4), 10);
	line(img, Point(20, 50), Point(260, 75), Scalar(82, 79, 48), 5);
	putText(img, "wk-chen", Point(45, 89),FONT_HERSHEY_TRIPLEX, 1, Scalar(89, 255, 1), 2);
	//namedWindow("Image", WINDOW_NORMAL);
	imshow("Image", img);
	
	waitKey(0);
}
