#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
///////////////////  5 basic function( cvtColor/ GussianBlur/ Canny /dilate /erode  )  //////////////////////
//
void main() {

    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat imggray, imgblur, imgcanny, imgdilate, imgerode;

    cvtColor(img, imggray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgblur, Size(3, 5), 3, 0);
    Canny(imgblur, imgcanny, 150, 50);

    Mat kernel =getStructuringElement(MORPH_RECT, Size(3, 3));

    dilate(imgcanny, imgdilate, kernel);
    erode(imgdilate, imgerode, kernel);


    //namedWindow("Image", WINDOW_NORMAL);//调整窗口，适应大小
    imshow("Image", img);
    imshow("Image_Gray", imggray);
    imshow("Image_Blur", imgblur);
    imshow("Image_Canny", imgcanny);
    imshow("Image_dilate", imgdilate);
    imshow("Image_erode", imgerode);
    waitKey(0);//add a delay,'0'==infinity

}