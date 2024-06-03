#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
///////////////////  color detection  //////////////////////

int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;
void main() {

    string path = "Resources/lambo.png";
    Mat img = imread(path);
    Mat imgHSV, mask;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    //set a trackbar to find the suitable value
    namedWindow("Trackbars", (700, 100));

    createTrackbar("Hue Min", "Trackbars", &hmin, 255);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Hue Max", "Trackbars", &hmax, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while (1) {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);//devide the image following a certain range
        //imshow("Image", img);
        //imshow("Image HSV", imgHSV);
        imshow("Image mask",mask);
        waitKey(1);//add a delay,'0'==infinity
    }
}