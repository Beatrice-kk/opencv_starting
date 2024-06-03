#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

float w = 250, h = 350;

//////////     warp image      (bird eye view)/////////////
void main() {

    string path = "Resources/cards.jpg";
    Mat img = imread(path);
    Mat matrix, imgWarp;
    Point2f src[4] = { {776,107},{1018,84},{836,359},{1116,331} };
    Point2f dst[4] = { {0.0f,0.0f} ,{w,0.0f} ,{0.0f,h} ,{w,h} };

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    for (int i = 0; i < 4; i++) {
        circle(img, src[i], 10, Scalar(10, 10, 255), FILLED);//BGR
    }

    imshow("Image", img);
    imshow("Image_Warp", imgWarp);
    waitKey(0);//add a delay,'0'==infinity

}
	