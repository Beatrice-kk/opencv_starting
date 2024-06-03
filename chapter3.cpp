#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;


//////////     Resize & Crop    /////////////
void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResize;
	Mat imgCrop;

	Rect roi(100, 100, 300, 200);//rectangle(top_left,bottom_right)
	imgCrop = img(roi);
	resize(img, imgResize, Size(),0.5,0.5);



	//namedWindow("Image", WINDOW_NORMAL);
	imshow("Image", img);
	//imshow("Image", imgResize);
	imshow("Image_Crop", imgCrop);
	waitKey(0);
}
