#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
///////////////////  Images  //////////////////////
//
void main() {
    int pixelmax = 255;
    int pixelmin = 0;
    string path = "Resources/test.png";
    Mat img = imread(path);

    namedWindow("thresh",(400,500));
    createTrackbar("pixelmax", "thresh", &pixelmax, 255);
    createTrackbar("pixelmin", "thresh", &pixelmin, 255);

    while (true) {
        Mat thresholded_img;
        threshold(img, thresholded_img, pixelmin, pixelmax, THRESH_BINARY);
        imshow("Image", thresholded_img);

        char key = waitKey(10);
        if (key == 27) // ESC key
            break;
    }

}

///////  video/////////////////
//void main() {
//
//    string path = "Resources/test_video.mp4";
//    VideoCapture cap(path);
//    Mat img;
//    while (true) {
//        cap.read(img);
//        threshold(img, img, 128, 255, cv::THRESH_BINARY);
//
//        imshow("Image", img);
//        waitKey(1);//add a delay,'0'==infinity
//    }
//
//}

/// <summary>
/// //////////////////  webcam   ///////////
/// </summary>

//void main() {
//    VideoCapture cap(1);
//    Mat img;
//    while (true) {
//        cap.read(img);
//        imshow("Image", img);
//        waitKey(1);//add a delay,'0'==infinity
//    }
//
//}